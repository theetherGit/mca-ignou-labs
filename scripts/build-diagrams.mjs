// Render diagram sources under public/code to SVG next to them (committed, like the PDFs).
//   *.puml  -> PlantUML  (brew install plantuml; brings Java and Graphviz)
//   *.dot   -> Graphviz dot
// Style comes from scripts/plantuml.skin: black on white, no shadows, print-friendly.
// Output is post-processed so it is deterministic and self-contained:
//   - the <?plantuml version?> instruction and comments are stripped
//   - font-family gets web fallbacks (PlantUML measured text with Helvetica)
//   - the XML prolog/doctype and the inline style go; width/height stay so the picture keeps its natural size
// Run: pnpm run build:diagrams   (or just `node scripts/build-diagrams.mjs`)
import { execFileSync } from "node:child_process";
import { readFileSync, writeFileSync, readdirSync, statSync, existsSync, unlinkSync } from "node:fs";
import { join, resolve, dirname } from "node:path";

const ROOT = resolve(import.meta.dirname, "..");
const CODE = join(ROOT, "public/code");
const SKIN = join(ROOT, "scripts/plantuml.skin");

function walk(dir) {
  return readdirSync(dir).flatMap((n) => {
    const p = join(dir, n);
    return statSync(p).isDirectory() ? walk(p) : [p];
  });
}
const files = walk(CODE);
const puml = files.filter((f) => f.endsWith(".puml"));
const dots = files.filter((f) => f.endsWith(".dot"));
const only = process.argv.slice(2); // optional: restrict to these source paths
const pick = (list) => (only.length ? list.filter((f) => only.some((o) => f.endsWith(o))) : list);

function has(cmd) {
  try {
    execFileSync("which", [cmd], { stdio: "ignore" });
    return true;
  } catch {
    return false;
  }
}

const clean = (svg) =>
  svg
    .replace(/<\?plantuml[^>]*\?>/g, "")
    .replace(/<!--[\s\S]*?-->/g, "")
    .replace(/font-family="Helvetica"/g, 'font-family="Helvetica, Arial, sans-serif"')
    .replace(/font-family="sans-serif"/g, 'font-family="Helvetica, Arial, sans-serif"')
    .replace(/<\?xml[^>]*\?>\s*/, "")
    .replace(/<!DOCTYPE[^>]*>\s*/, "")
    .replace(/<svg([^>]*?) style="[^"]*"/, "<svg$1")
    .trimStart();

let rendered = 0;
const todoPuml = pick(puml);
if (todoPuml.length) {
  if (!has("plantuml")) {
    console.error("build-diagrams: plantuml not found. Install with: brew install plantuml");
    process.exit(1);
  }
  execFileSync("plantuml", ["-tsvg", "-config", SKIN, ...todoPuml], { stdio: "inherit" });
  for (const src of todoPuml) {
    const out = src.replace(/\.puml$/, ".svg");
    if (!existsSync(out)) throw new Error(`build-diagrams: PlantUML produced nothing for ${src}`);
    const svg = clean(readFileSync(out, "utf8"));
    if (/Syntax Error|Cannot find Graphviz/.test(svg)) throw new Error(`build-diagrams: error rendering ${src}`);
    writeFileSync(out, svg);
    rendered++;
  }
}
const todoDot = pick(dots);
if (todoDot.length) {
  if (!has("dot")) {
    console.error("build-diagrams: graphviz `dot` not found. Install with: brew install graphviz");
    process.exit(1);
  }
  for (const src of todoDot) {
    const svg = execFileSync("dot", ["-Tsvg", src], { encoding: "utf8" });
    writeFileSync(src.replace(/\.dot$/, ".svg"), clean(svg));
    rendered++;
  }
}

// Drop SVGs whose source is gone (only inside folders that hold diagram sources).
let removed = 0;
const sources = new Set([...puml, ...dots].map((f) => f.replace(/\.(puml|dot)$/, "")));
const sourceDirs = new Set([...puml, ...dots].map(dirname));
for (const f of files.filter((f) => f.endsWith(".svg") && sourceDirs.has(dirname(f)))) {
  if (!sources.has(f.replace(/\.svg$/, ""))) {
    unlinkSync(f);
    removed++;
  }
}
console.log(`build-diagrams: ${puml.length + dots.length} sources · ${rendered} rendered · ${removed} removed`);
