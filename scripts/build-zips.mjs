// Bundle the committed session PDFs into ZIPs. Runs after `astro build` (on Cloudflare
// Workers Builds and locally); needs nothing beyond Node, so no Chromium in CI.
//
// Input:  dist/downloads/<section-key>/*.pdf   (copied from public/downloads by astro build)
//         dist/mcs-216.pdf, dist/mcs-217.pdf   (hand-made question sheets for Semester 1)
// Output: dist/downloads/<section-key>.zip · <course>.zip · semester-N.zip
//         Each ZIP holds one folder per section. Entries are deflated (each PDF once, reused
//         across ZIPs) with a fixed timestamp, so the same PDFs always give identical bytes.
import { readFileSync, writeFileSync, readdirSync, existsSync, statSync } from "node:fs";
import { join, resolve } from "node:path";
import { crc32, deflateRawSync } from "node:zlib";

const DIST = resolve(import.meta.dirname, "../dist");
const OUT = join(DIST, "downloads");
const SEMESTER = { "mcs-216": 1, "mcs-217": 1, "mcsl-222": 2, "mcsl-223": 2 };
const HAND_SHEETS = { "mcs-216-section-1": "mcs-216.pdf", "mcs-216-section-2": "mcs-216.pdf", "mcs-217": "mcs-217.pdf" };
const MAX_ASSET = 25 * 1024 * 1024; // Cloudflare static asset limit per file

if (!existsSync(OUT)) {
  console.error("build-zips: dist/downloads is missing. Commit PDFs with `pnpm run build:pdf` first.");
  process.exit(1);
}

// Minimal ZIP writer: deflate method, UTF-8 names, one fixed DOS timestamp (2026-01-01 00:00).
const DOS_DATE = ((2026 - 1980) << 9) | (1 << 5) | 1;
function zip(entries) {
  const parts = [];
  const central = [];
  let offset = 0;
  for (const { name, data, crc, packed } of entries) {
    const n = Buffer.from(name, "utf8");
    const local = Buffer.alloc(30);
    local.writeUInt32LE(0x04034b50, 0);
    local.writeUInt16LE(20, 4);
    local.writeUInt16LE(0x0800, 6);
    local.writeUInt16LE(8, 8);
    local.writeUInt16LE(0, 10);
    local.writeUInt16LE(DOS_DATE, 12);
    local.writeUInt32LE(crc, 14);
    local.writeUInt32LE(packed.length, 18);
    local.writeUInt32LE(data.length, 22);
    local.writeUInt16LE(n.length, 26);
    local.writeUInt16LE(0, 28);
    const cd = Buffer.alloc(46);
    cd.writeUInt32LE(0x02014b50, 0);
    cd.writeUInt16LE(20, 4);
    cd.writeUInt16LE(20, 6);
    cd.writeUInt16LE(0x0800, 8);
    cd.writeUInt16LE(8, 10);
    cd.writeUInt16LE(0, 12);
    cd.writeUInt16LE(DOS_DATE, 14);
    cd.writeUInt32LE(crc, 16);
    cd.writeUInt32LE(packed.length, 20);
    cd.writeUInt32LE(data.length, 24);
    cd.writeUInt16LE(n.length, 28);
    cd.writeUInt32LE(offset, 42);
    parts.push(local, n, packed);
    central.push(cd, n);
    offset += local.length + n.length + packed.length;
  }
  const cdBuf = Buffer.concat(central);
  const end = Buffer.alloc(22);
  end.writeUInt32LE(0x06054b50, 0);
  end.writeUInt16LE(entries.length, 8);
  end.writeUInt16LE(entries.length, 10);
  end.writeUInt32LE(cdBuf.length, 12);
  end.writeUInt32LE(offset, 16);
  const out = Buffer.concat([...parts, cdBuf, end]);
  // Self-check: the end record must point at a central directory holding every entry.
  const eocd = out.subarray(out.length - 22);
  if (eocd.readUInt32LE(0) !== 0x06054b50 || eocd.readUInt16LE(10) !== entries.length || out.readUInt32LE(eocd.readUInt32LE(16)) !== 0x02014b50) {
    throw new Error("build-zips: ZIP self-check failed");
  }
  return out;
}

// Each PDF appears in up to four ZIPs; read and compress it once.
const cache = new Map();
const entry = (name, path) => {
  if (!cache.has(path)) {
    const data = readFileSync(path);
    cache.set(path, { data, crc: crc32(data), packed: deflateRawSync(data, { level: 9 }) });
  }
  return { name, ...cache.get(path) };
};

const sections = readdirSync(OUT)
  .filter((d) => statSync(join(OUT, d)).isDirectory() && d.split("-section")[0] in SEMESTER)
  .sort();
const filesOf = (section) => {
  const files = readdirSync(join(OUT, section))
    .filter((f) => f.endsWith(".pdf"))
    .sort()
    .map((f) => entry(`${section}/${f}`, join(OUT, section, f)));
  const sheet = HAND_SHEETS[section];
  if (sheet && existsSync(join(DIST, sheet)) && !files.some((f) => f.name.endsWith("-questions.pdf"))) {
    files.push(entry(`${section}/${section}-questions.pdf`, join(DIST, sheet)));
  }
  return files;
};

const write = (name, secs) => {
  const buf = zip(secs.flatMap(filesOf));
  if (buf.length > MAX_ASSET) throw new Error(`build-zips: ${name}.zip is ${(buf.length / 1048576).toFixed(1)} MB, over Cloudflare's 25 MB asset limit. Split it.`);
  writeFileSync(join(OUT, `${name}.zip`), buf);
  return `${name}.zip ${(buf.length / 1048576).toFixed(1)} MB`;
};

const made = [];
for (const s of sections) made.push(write(s, [s]));
for (const course of Object.keys(SEMESTER)) {
  const secs = sections.filter((s) => s === course || s.startsWith(`${course}-`));
  if (secs.length > 1) made.push(write(course, secs)); // a single-section course's section ZIP already is its course ZIP
}
for (const sem of [...new Set(Object.values(SEMESTER))]) {
  const secs = sections.filter((s) => SEMESTER[s.split("-section")[0]] === sem);
  if (secs.length) made.push(write(`semester-${sem}`, secs));
}
console.log(`build-zips: ${made.join(" · ")}`);
