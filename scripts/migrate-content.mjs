// One-shot: src/content/**/*.md (mdsx) -> src/content/docs/**/*.mdx (Nimbus). Delete after run.
import { readFileSync, writeFileSync, mkdirSync, readdirSync, statSync, rmSync } from "node:fs";
import { join, dirname, relative, basename } from "node:path";

const SRC = "src/content";
const DST = "src/content/docs";
const DEMO_DIR = "src/components/demo";

function walk(dir) {
  return readdirSync(dir).flatMap((n) => {
    const p = join(dir, n);
    if (p.startsWith(DST)) return [];
    return statSync(p).isDirectory() ? walk(p) : p.endsWith(".md") ? [p] : [];
  });
}

function migrate(src) {
  const rel = relative(SRC, src).replace(/\.md$/, ".mdx");
  const dst = join(DST, rel === "index.mdx" ? "introduction.mdx" : rel);
  const lines = readFileSync(src, "utf8").split("\n");

  // --- frontmatter ---
  const fmEnd = lines.indexOf("---", 1);
  const fm = lines.slice(1, fmEnd).filter((l) => !l.startsWith("section:"));
  const m = basename(src).match(/session-(\d+)/);
  const order = m ? Number(m[1]) : 0;
  fm.push("sidebar:", `  order: ${order}`);

  // --- first <script> block (mdsx imports) ---
  let body = lines.slice(fmEnd + 1);
  const s = body.findIndex((l) => l.trim() === "<script>");
  const e = body.findIndex((l, i) => i > s && l.trim() === "</script>");
  const script = s >= 0 && e > s ? body.slice(s + 1, e) : [];
  if (s >= 0 && e > s) body = [...body.slice(0, s), ...body.slice(e + 1)];

  const imports = [];
  const demoNames = new Set();
  for (const l of script) {
    const im = l.match(/import\s+(\w+)\s+from\s+["']\$lib\/components\/demo\/([^"']+)["']/);
    if (!im) continue; // PrintButton/Callout/icons are globals or dropped
    let p = relative(dirname(dst), join(DEMO_DIR, im[2])).replaceAll("\\", "/");
    if (!p.startsWith(".")) p = "./" + p;
    imports.push(`import ${im[1]} from "${p}";`);
    demoNames.add(im[1]);
  }

  // --- body transforms, skipping fenced code ---
  let inFence = false;
  const out = [];
  for (let l of body) {
    if (/^\s*```/.test(l)) {
      inFence = !inFence;
      if (inFence) l = l.replace(/file=(?:\.\.\/)+lib\/code\//, "file=<rootDir>/public/code/");
      out.push(l);
      continue;
    }
    if (inFence) {
      out.push(l);
      continue;
    }
    if (/^\s*<!--.*-->\s*$/.test(l)) continue; // spacer comments
    l = l
      .replace(/<Callout\b([^>]*?)\s*icon=\{[^}]*\}([^>]*)>/g, "<Callout$1$2>")
      .replace(/<Callout\b/g, "<Aside")
      .replace(/<\/Callout>/g, "</Aside>")
      .replace(/type="warning"/g, 'type="caution"')
      .replace(/<img\b([^>]*[^/])>/g, "<img$1 />")
      .replace(/src="\/preview\//g, 'src="/code/');
    for (const n of demoNames) l = l.replace(new RegExp(`<${n}\\s*/>`, "g"), `<${n} client:visible />`);
    out.push(l);
  }

  mkdirSync(dirname(dst), { recursive: true });
  writeFileSync(
    dst,
    ["---", ...fm, "---", "", ...imports, ...(imports.length ? [""] : []), ...out].join("\n"),
  );
  rmSync(src);
  return dst;
}

const files = walk(SRC);
const written = files.map(migrate);
console.log(`migrated ${written.length} pages`);
// self-check: no leftover mdsx syntax outside code fences
for (const f of written) {
  const t = readFileSync(f, "utf8").replace(/```[\s\S]*?```/g, "");
  if (/\$lib\/|<script>|<Callout|<!--|\/preview\//.test(t)) console.error("LEFTOVER:", f);
}
