// Render every session page in dist/ to PDF and bundle ZIPs per section, course and semester.
// Runs after `astro build`. Requires: pnpm exec playwright install chromium, and `zip` on PATH.
//
// Output layout (under dist/downloads/):
//   <section-key>/<section-key>-session-NN.pdf     e.g. mcs-216-section-1/mcs-216-section-1-session-03.pdf
//   <section-key>/<section-key>-questions.pdf      the manual's question sheet
//   <section-key>.zip                              one section
//   <course>.zip                                   all sections of a course
//   semester-N.zip                                 all courses of a semester
import { createServer } from "node:http";
import { readFileSync, existsSync, mkdirSync, readdirSync, statSync, copyFileSync, rmSync } from "node:fs";
import { join, extname, resolve } from "node:path";
import { execFileSync } from "node:child_process";
import { chromium } from "playwright";

const ROOT = resolve(import.meta.dirname, "..");
const DIST = join(ROOT, "dist");
const OUT = join(DIST, "downloads");
const DOCS = join(ROOT, "src/content/docs");
const PORT = 4444;
const CONCURRENCY = 4;

const SEMESTER = { "mcs-216": 1, "mcs-217": 1, "mcsl-222": 2, "mcsl-223": 2 };
const QUESTION_SHEET = {
  "mcs-216-section-1": "mcs-216.pdf",
  "mcs-216-section-2": "mcs-216.pdf",
  "mcs-217": "mcs-217.pdf",
  "mcsl-222-section-1": "mcsl-222-section-1-questions.pdf",
  "mcsl-222-section-2": "mcsl-222-section-2-questions.pdf",
  "mcsl-223-section-1": "mcsl-223-section-1-questions.pdf",
  "mcsl-223-section-2": "mcsl-223-section-2-questions.pdf",
};

// --- collect session pages -------------------------------------------------
function walk(dir) {
  return readdirSync(dir).flatMap((n) => {
    const p = join(dir, n);
    return statSync(p).isDirectory() ? walk(p) : [p];
  });
}
const pages = walk(DOCS)
  .filter((p) => /session-\d+\.mdx$/.test(p))
  .map((p) => {
    const rel = p.slice(DOCS.length + 1).replace(/\.mdx$/, "");
    const parts = rel.split("/");
    const course = parts[0];
    const section = parts.length === 3 ? parts[1] : null;
    const n = /session-(\d+)$/.exec(rel)[1].padStart(2, "0");
    const sectionKey = section ? `${course}-${section}` : course;
    return { url: `/${rel}/`, course, sectionKey, file: `${sectionKey}-session-${n}.pdf` };
  })
  .filter((p) => p.course in SEMESTER)
  .sort((a, b) => a.file.localeCompare(b.file));

// --- tiny static server for dist ------------------------------------------
const MIME = { ".html": "text/html", ".css": "text/css", ".js": "text/javascript", ".mjs": "text/javascript", ".png": "image/png", ".jpg": "image/jpeg", ".svg": "image/svg+xml", ".woff2": "font/woff2", ".ttf": "font/ttf", ".json": "application/json", ".pdf": "application/pdf" };
const server = createServer((req, res) => {
  let path = decodeURIComponent(new URL(req.url, "http://x").pathname);
  let file = join(DIST, path);
  if (existsSync(file) && statSync(file).isDirectory()) file = join(file, "index.html");
  if (!existsSync(file)) {
    res.writeHead(404);
    return res.end();
  }
  res.writeHead(200, { "content-type": MIME[extname(file)] ?? "application/octet-stream" });
  res.end(readFileSync(file));
});
await new Promise((r) => server.listen(PORT, r));

// --- render ------------------------------------------------------------------
rmSync(OUT, { recursive: true, force: true });
mkdirSync(OUT, { recursive: true });
const browser = await chromium.launch();
const t0 = Date.now();
let done = 0;
async function render(p) {
  const page = await browser.newPage();
  await page.goto(`http://localhost:${PORT}${p.url}`, { waitUntil: "networkidle" });
  await page.emulateMedia({ media: "print" });
  const dir = join(OUT, p.sectionKey);
  mkdirSync(dir, { recursive: true });
  await page.pdf({
    path: join(dir, p.file),
    format: "A4",
    printBackground: true,
    margin: { top: "16mm", bottom: "16mm", left: "14mm", right: "14mm" },
    displayHeaderFooter: true,
    headerTemplate: `<div style="font-size:8px;color:#888;width:100%;padding:0 14mm;display:flex;justify-content:space-between"><span>Syntax Lab · syntax.theether.in</span><span>${p.file}</span></div>`,
    footerTemplate: `<div style="font-size:8px;color:#888;width:100%;text-align:center"><span class="pageNumber"></span> / <span class="totalPages"></span></div>`,
  });
  await page.close();
  done++;
}
const queue = [...pages];
await Promise.all(Array.from({ length: CONCURRENCY }, async () => {
  while (queue.length) await render(queue.shift());
}));
await browser.close();
server.close();
console.log(`rendered ${done} PDFs in ${((Date.now() - t0) / 1000).toFixed(1)}s`);

// --- question sheets + zips --------------------------------------------------
const sections = [...new Set(pages.map((p) => p.sectionKey))];
for (const key of sections) {
  const sheet = QUESTION_SHEET[key];
  if (sheet && existsSync(join(ROOT, "public", sheet))) copyFileSync(join(ROOT, "public", sheet), join(OUT, key, `${key}-questions.pdf`));
}
const zip = (name, dirs) => execFileSync("zip", ["-q", "-r", `${name}.zip`, ...dirs], { cwd: OUT });
for (const key of sections) zip(key, [key]);
const courses = [...new Set(pages.map((p) => p.course))];
for (const c of courses) zip(c, sections.filter((s) => s === c || s.startsWith(`${c}-`)));
for (const sem of new Set(Object.values(SEMESTER))) {
  const dirs = sections.filter((s) => SEMESTER[s.split("-section")[0]] === sem);
  if (dirs.length) zip(`semester-${sem}`, dirs);
}
console.log(`zips: ${readdirSync(OUT).filter((f) => f.endsWith(".zip")).join(", ")}`);
