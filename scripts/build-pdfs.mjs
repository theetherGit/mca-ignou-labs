// Render session pages and question papers to PDF into public/downloads/ (committed).
//
// Runs on a developer machine (pre-commit hook: .githooks/pre-commit) because it needs
// headless Chromium, which Cloudflare's build image cannot run. Cloudflare then only runs
// `astro build` (copies public/downloads into dist) and scripts/build-zips.mjs.
//
// Deterministic: Chromium stamps the render time into every PDF (its only non-determinism);
// those dates are pinned, so re-rendering an unchanged page gives byte-identical output.
// Incremental: each page is hashed on what actually prints
// (the <main> markup minus the "last updated" date, its stylesheets and images, and this
// script) and only re-rendered when that hash changes. Hashes live in scripts/pdf-manifest.json.
//
// Needs a fresh `astro build` first (dist/). Run via `pnpm run build:pdf`.
// Output: public/downloads/<section-key>/<section-key>-session-NN.pdf
//         public/downloads/<section-key>/<section-key>-questions.pdf   (typed question papers)
import { createServer } from "node:http";
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync, existsSync, mkdirSync, readdirSync, statSync, rmSync } from "node:fs";
import { join, extname, resolve, relative, dirname } from "node:path";
import { chromium } from "playwright";

const ROOT = resolve(import.meta.dirname, "..");
const DIST = join(ROOT, "dist");
const OUT = join(ROOT, "public/downloads");
const DOCS = join(ROOT, "src/content/docs");
const MANIFEST = join(ROOT, "scripts/pdf-manifest.json");
const PORT = 4444;
const CONCURRENCY = 4;
const COURSES = new Set(["mcs-216", "mcs-217", "mcsl-222", "mcsl-223"]);

if (!existsSync(join(DIST, "index.html"))) {
  console.error("build-pdfs: dist/ is missing. Run `astro build` first (or `pnpm run build:pdf`).");
  process.exit(1);
}

// --- pages to render ---------------------------------------------------------
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
    const section = parts.length === 3 ? parts[1] : null;
    const n = /session-(\d+)$/.exec(rel)[1].padStart(2, "0");
    const sectionKey = section ? `${parts[0]}-${section}` : parts[0];
    return { url: `/${rel}/`, course: parts[0], out: `${sectionKey}/${sectionKey}-session-${n}.pdf`, paper: false };
  })
  .filter((p) => COURSES.has(p.course));
for (const f of readdirSync(join(DOCS, "question-papers")).filter((f) => f.endsWith(".mdx"))) {
  const key = f.replace(/\.mdx$/, "");
  pages.push({ url: `/question-papers/${key}/`, course: key.split("-section")[0], out: `${key}/${key}-questions.pdf`, paper: true });
}
pages.sort((a, b) => a.out.localeCompare(b.out));

// --- print-relevant hash -----------------------------------------------------
const SCRIPT_HASH = createHash("sha256").update(readFileSync(import.meta.filename)).digest("hex");
const distFile = (url) => join(DIST, decodeURIComponent(url.split(/[?#]/)[0]));
function printHash(url) {
  const html = readFileSync(join(DIST, url, "index.html"), "utf8");
  const main = (html.match(/<main[\s\S]*<\/main>/) ?? [html])[0]
    .replace(/<time\b[^>]*>[\s\S]*?<\/time>/g, "") // git "last updated" date
    .replace(/ uid="[^"]*"/g, ""); // Astro island ids are random per build
  const h = createHash("sha256").update(SCRIPT_HASH).update(main);
  for (const s of html.match(/<style\b[\s\S]*?<\/style>/g) ?? []) h.update(s);
  for (const tag of html.match(/<link\b[^>]*>/g) ?? []) {
    const href = /href="([^"]+)"/.exec(tag)?.[1];
    if (/rel="stylesheet"/.test(tag) && href?.startsWith("/") && existsSync(distFile(href))) h.update(readFileSync(distFile(href)));
  }
  for (const m of main.matchAll(/<img\b[^>]*src="(\/[^"]+)"/g)) if (existsSync(distFile(m[1]))) h.update(readFileSync(distFile(m[1])));
  return h.digest("hex").slice(0, 16);
}

// Same-length replacement keeps the PDF's cross-reference offsets valid.
const PINNED = "20260101000000";
const pinDates = (buf) =>
  Buffer.from(buf.toString("latin1").replace(/(\/(?:CreationDate|ModDate) ?\(D:)\d{14}/g, `$1${PINNED}`), "latin1");

const manifest = existsSync(MANIFEST) ? JSON.parse(readFileSync(MANIFEST, "utf8")) : {};
const next = {};
const todo = [];
for (const p of pages) {
  next[p.out] = printHash(p.url);
  if (manifest[p.out] !== next[p.out] || !existsSync(join(OUT, p.out))) todo.push(p);
}

// Remove PDFs for pages that no longer exist.
const expected = new Set(pages.map((p) => p.out));
let removed = 0;
if (existsSync(OUT)) {
  for (const f of walk(OUT).filter((f) => f.endsWith(".pdf"))) {
    if (!expected.has(relative(OUT, f))) {
      rmSync(f);
      removed++;
    }
  }
}

// --- render changed pages ------------------------------------------------------
if (todo.length) {
  const MIME = { ".html": "text/html", ".css": "text/css", ".js": "text/javascript", ".mjs": "text/javascript", ".png": "image/png", ".jpg": "image/jpeg", ".svg": "image/svg+xml", ".woff2": "font/woff2", ".ttf": "font/ttf", ".json": "application/json" };
  const server = createServer((req, res) => {
    let file = distFile(new URL(req.url, "http://x").pathname);
    if (existsSync(file) && statSync(file).isDirectory()) file = join(file, "index.html");
    if (!existsSync(file)) {
      res.writeHead(404);
      return res.end();
    }
    res.writeHead(200, { "content-type": MIME[extname(file)] ?? "application/octet-stream" });
    res.end(readFileSync(file));
  });
  await new Promise((r) => server.listen(PORT, r));
  const browser = await chromium.launch();
  const queue = [...todo];
  await Promise.all(
    Array.from({ length: CONCURRENCY }, async () => {
      while (queue.length) {
        const p = queue.shift();
        const page = await browser.newPage();
        await page.goto(`http://localhost:${PORT}${p.url}`, { waitUntil: "networkidle" });
        await page.emulateMedia({ media: "print" });
        const file = join(OUT, p.out);
        mkdirSync(dirname(file), { recursive: true });
        const name = p.out.split("/").pop();
        const pdf = await page.pdf({
          format: "A4",
          printBackground: true,
          margin: { top: "16mm", bottom: "16mm", left: "14mm", right: "14mm" },
          displayHeaderFooter: true,
          headerTemplate: `<div style="font-size:8px;color:#888;width:100%;padding:0 14mm;display:flex;justify-content:space-between"><span>${p.paper ? "Question paper" : "Syntax Lab · syntax.theether.in"}</span><span>${name}</span></div>`,
          footerTemplate: `<div style="font-size:8px;color:#888;width:100%;text-align:center"><span class="pageNumber"></span> / <span class="totalPages"></span></div>`,
        });
        writeFileSync(file, pinDates(pdf));
        await page.close();
      }
    }),
  );
  await browser.close();
  server.close();
}

writeFileSync(MANIFEST, JSON.stringify(Object.fromEntries(Object.entries(next).sort()), null, 2) + "\n");
console.log(`build-pdfs: ${pages.length} pages · ${todo.length} rendered · ${pages.length - todo.length} unchanged · ${removed} removed`);
