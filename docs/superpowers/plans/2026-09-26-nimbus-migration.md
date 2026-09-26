# Nimbus Migration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the SvelteKit/Velite/mdsx site with Nimbus (Astro 7) in place on branch `nimbus`, keeping all 45 pages, 28 Svelte demos, code imports, iframe previews, math, PWA, and PrintButton working.

**Architecture:** Nimbus scaffold (probed at `/tmp/nimbus-probe`) is merged into the repo; content is transformed `.md` → `.mdx` by a one-shot script; Svelte demos become Astro islands via `@astrojs/svelte`; solution files move to `public/code/` so iframes and `remark-code-import` both read them.

**Tech Stack:** Astro 7, `@cloudflare/nimbus-docs`, `@astrojs/svelte` 9, Svelte 5, Tailwind v4, remark-code-import, remark-math, @daiji256/rehype-mathml, pnpm, wrangler.

**Spec:** `docs/superpowers/specs/2026-09-26-nimbus-migration-design.md`

## Global Constraints

- Node ≥ 22.12; package manager pnpm.
- Branch: `nimbus`. Commit after each task.
- Site URL `https://syntax.theether.in`, title `Syntax Lab`, description `Explained guide for IGNOU MCA Labs`, GitHub `https://github.com/theetherGit/mca-ignou-labs`.
- Keep: `docs-plan/`, `worker-configuration.d.ts`, `.zed/`, PWA, PrintButton. Delete: `venv/`, `output/`, `egyankosh/`, `scripts/egyankosh.py`, `pyproject.toml`.
- Old `/docs/...` URLs redirect to new root URLs.
- Never edit files under `public/code/` content; they are student solutions.

---

### Task 1: Merge Nimbus scaffold, remove SvelteKit

**Files:**
- Create (copy from `/tmp/nimbus-probe`): `astro.config.ts`, `tsconfig.json`, `wrangler.jsonc`, `pnpm-workspace.yaml`, `AGENT.md`, `src/components.ts`, `src/content.config.ts`, `src/components/**`, `src/layouts/**`, `src/lib/cn.ts`, `src/pages/**`, `src/styles/**`, `public/favicon.ico`, `public/fonts/**`
- Modify: `package.json` (replace), `.gitignore` (replace + `**/__pycache__`)
- Delete: `src/routes`, `src/app.css`, `src/app.d.ts`, `src/app.html`, `src/service-worker.ts`, `src/lib/{utils,navigation,navigation-neighbors,site-config,index}.ts`, `src/lib/components/{blueprint,print-button}.svelte`, `svelte.config.js`, `velite.config.js`, `mdsx.config.js`, `vite.config.ts`, `wrangler.json`, `scripts/build-search-data.js`, `scripts/update-velite-output.js`, `scripts/egyankosh.py`, `pyproject.toml`, `.svelte-kit`, `.velite`, `.wrangler`, `venv`, `output`, `egyankosh`, `pnpm-lock.yaml`

**Interfaces:**
- Produces: working Astro build with starter content; `src/content/docs/` empty except starter pages (deleted in Task 3).

- [ ] **Step 1: Delete SvelteKit + Python tooling**

```bash
cd /Users/shivammeena/Projects/MCA-IGNOU
git rm -rq src/routes src/app.css src/app.d.ts src/app.html src/service-worker.ts \
  src/lib/utils.ts src/lib/navigation.ts src/lib/navigation-neighbors.ts src/lib/site-config.ts src/lib/index.ts \
  src/lib/components/blueprint.svelte src/lib/components/print-button.svelte \
  svelte.config.js velite.config.js mdsx.config.js vite.config.ts wrangler.json \
  scripts/build-search-data.js scripts/update-velite-output.js pyproject.toml pnpm-lock.yaml
rm -rf .svelte-kit .velite .wrangler venv output egyankosh scripts/egyankosh.py node_modules public/static
find src/lib/code -name __pycache__ -type d -exec rm -rf {} +
```

- [ ] **Step 2: Copy scaffold files**

```bash
P=/tmp/nimbus-probe
cp $P/astro.config.ts $P/tsconfig.json $P/wrangler.jsonc $P/pnpm-workspace.yaml $P/AGENT.md $P/.gitignore .
cp $P/package.json package.json
mkdir -p src public
cp -R $P/src/components $P/src/layouts $P/src/pages $P/src/styles src/
cp $P/src/components.ts $P/src/content.config.ts src/
mkdir -p src/lib && cp $P/src/lib/cn.ts src/lib/
cp -R $P/src/content/docs src/content/  # starter pages, removed in Task 3
mkdir -p src/content/partials && cp $P/src/content/partials/example.mdx src/content/partials/
cp -R $P/public/favicon.ico $P/public/fonts public/
echo '**/__pycache__' >> .gitignore
```

- [ ] **Step 3: Set package name and install latest Nimbus + plugins**

Edit `package.json`: `"name": "@ethercorps/docs"`. Then:

```bash
pnpm add @cloudflare/nimbus-docs@latest @astrojs/svelte@latest svelte@latest remark-code-import@^1.2.0 remark-math@^6.0.0 @daiji256/rehype-mathml@^1.2.2
pnpm install
```

- [ ] **Step 4: Build starter site**

Run: `pnpm build`
Expected: exits 0, `dist/welcome/index.html` exists. If `@cloudflare/nimbus-docs@latest` changed config API vs the 0.7.x probe, fix `astro.config.ts` per the printed error before continuing.

- [ ] **Step 5: Commit**

```bash
git add -A && git commit -m "chore: replace SvelteKit scaffold with Nimbus (Astro)"
```

---

### Task 2: Site config, assets, PrintButton, PWA

**Files:**
- Modify: `astro.config.ts`, `src/components.ts`, `src/styles/globals.css`, `src/styles/prose.css`, `src/pages/index.astro`, `wrangler.jsonc`
- Create: `src/components/PrintButton.astro`, `public/sw.js`
- Move: `static/*` → `public/`, `src/lib/code/**` → `public/code/**`

**Interfaces:**
- Produces: MDX globals `PrintButton`, `Aside`; remark `file=<rootDir>/public/code/...` resolves; `/code/<path>.html` served statically.

- [ ] **Step 1: Move static assets**

```bash
git mv static/* public/ && rmdir static
mkdir -p public/code && git mv src/lib/code/* public/code/ && rm -rf src/lib/code
```

- [ ] **Step 2: Write `astro.config.ts`**

```ts
import { defineConfig } from "astro/config";
import icon from "astro-icon";
import svelte from "@astrojs/svelte";
import tailwindcss from "@tailwindcss/vite";
import nimbus, { defineConfig as defineNimbusConfig } from "@cloudflare/nimbus-docs";
import { tableScroll } from "@cloudflare/nimbus-docs/markdown";
import codeImport from "remark-code-import";
import remarkMath from "remark-math";
import rehypeMathML from "@daiji256/rehype-mathml";

const nimbusConfig = defineNimbusConfig({
  site: "https://syntax.theether.in",
  title: "Syntax Lab",
  description: "Explained guide for IGNOU MCA Labs",
  locale: "en",
  github: "https://github.com/theetherGit/mca-ignou-labs",
  editPattern: "https://github.com/theetherGit/mca-ignou-labs/edit/main/{path}",
  socialImage: "/og.png",
  socialImageAlt: "Syntax Lab — IGNOU MCA lab companion",
  head: [
    { tag: "link", attrs: { rel: "manifest", href: "/manifest.json" } },
    {
      tag: "script",
      content:
        "if('serviceWorker' in navigator){addEventListener('load',()=>navigator.serviceWorker.register('/sw.js'))}",
    },
  ],
  sidebar: {
    items: [
      "introduction",
      "important-notice",
      "getting-started",
      { label: "MCS-216 Section 1", autogenerate: { directory: "mcs-216/section-1" } },
      { label: "MCS-216 Section 2", autogenerate: { directory: "mcs-216/section-2" } },
      { label: "MCS-217", autogenerate: { directory: "mcs-217" } },
    ],
  },
});

export default defineConfig({
  output: "static",
  redirects: {
    "/docs": "/introduction",
    "/docs/[...slug]": "/[...slug]",
  },
  vite: { plugins: [tailwindcss()] },
  prefetch: { prefetchAll: true, defaultStrategy: "hover" },
  integrations: [
    icon(),
    svelte(),
    nimbus(nimbusConfig, {
      rules: {
        "nimbus/frontmatter-shape": "error",
        "nimbus/internal-link": "error",
      },
      markdown: { hastPlugins: [tableScroll()] },
      mdx: {
        remarkPlugins: [[codeImport, { rootDir: process.cwd() }], remarkMath],
        rehypePlugins: [rehypeMathML],
      },
    }),
  ],
});
```

- [ ] **Step 3: Create `src/components/PrintButton.astro` and register it**

```astro
---
// Print the current page. Hidden in print output via .no-print in globals.css.
---
<div class="py-2 no-print w-full">
  <button
    type="button"
    class="mt-2 w-full rounded-md border border-border bg-card px-4 py-2 text-sm font-medium text-foreground hover:bg-accent"
    onclick="window.print()"
  >
    Print Page
  </button>
</div>
```

In `src/components.ts` add `import PrintButton from "./components/PrintButton.astro";` and `PrintButton,` to the exported object.

- [ ] **Step 4: Styles — orange accent, print rule, MathML matrix CSS**

Append to `src/styles/globals.css`:

```css
@media print {
  .no-print { display: none !important; }
}
```

In the `:root` light block set `--nb-primary: oklch(0.70 0.19 45);` and `--nb-primary-foreground: oklch(0.99 0 0);`; in `[data-mode="dark"]` set `--nb-primary: oklch(0.75 0.18 50);`.

Append to `src/styles/prose.css` (content moved from `src/content/mcs-216/section-1/session-9.md` lines 407–446, `--theme-color-brand` → `--nb-primary`):

```css
/* MathML matrices (Floyd–Warshall session) */
.docs-content mrow > mtable {
  background-color: rgba(0, 0, 0, 0.02);
  border-radius: 6px;
  margin: 1rem auto;
  font-variant-numeric: tabular-nums;
}
.docs-content mrow > mtable mtd {
  padding: 0.5rem 0.8rem !important;
  text-align: center;
  vertical-align: middle;
}
.docs-content mrow > mo[fence="true"] {
  color: var(--nb-primary);
  font-weight: bold;
  padding: 0 0.2rem;
}
.docs-content mrow > mtable mtr:has(mtd[style*="font-size:1"]) { height: 10px; }
.docs-content mrow:has(mtable) {
  display: flex; align-items: center; justify-content: center;
  overflow-x: auto; overflow-y: hidden; max-width: 100%; padding: 0.5rem 0;
}
```

- [ ] **Step 5: Service worker `public/sw.js`**

```js
// ponytail: runtime stale-while-revalidate cache; precache manifest if offline-first ever matters.
const CACHE = "syntax-lab-v1";
self.addEventListener("install", () => self.skipWaiting());
self.addEventListener("activate", (e) =>
  e.waitUntil(caches.keys().then((ks) => Promise.all(ks.filter((k) => k !== CACHE).map((k) => caches.delete(k))))),
);
self.addEventListener("fetch", (e) => {
  if (e.request.method !== "GET" || new URL(e.request.url).origin !== location.origin) return;
  e.respondWith(
    caches.open(CACHE).then(async (c) => {
      const cached = await c.match(e.request);
      const net = fetch(e.request).then((r) => { if (r.ok) c.put(e.request, r.clone()); return r; }).catch(() => cached);
      return cached ?? net;
    }),
  );
});
```

- [ ] **Step 6: Home page cards + wrangler name**

In `src/pages/index.astro` replace the three `<a>` cards with links to `/introduction` ("Introduction", "What is Syntax Lab?"), `/mcs-216/section-1/session-1` ("MCS-216", "DAA and Web Design labs"), `/mcs-217/introduction` ("MCS-217", "Software Engineering labs"). In `wrangler.jsonc` set `"name": "mca-ignou-labs"`.

- [ ] **Step 7: Build**

Run: `pnpm build`
Expected: exits 0 (starter pages still present; sidebar items pointing at missing pages may warn — acceptable until Task 3).

- [ ] **Step 8: Commit**

```bash
git add -A && git commit -m "feat: nimbus site config, assets, PrintButton, PWA"
```

---

### Task 3: Migrate content and demos

**Files:**
- Create: `scripts/migrate-content.mjs` (deleted in Task 4)
- Move: `src/lib/components/demo/**` → `src/components/demo/**`; `src/content/*.md`, `src/content/**/*.md` → `src/content/docs/**/*.mdx`
- Modify: `src/components/demo/mcs-216/section-2/session-5/2.svelte`, `src/components/demo/mcs-216/section-2/session-10/3.svelte`
- Delete: `src/content/docs/{welcome,getting-started,components}.mdx` (starter), `src/content/partials/example.mdx`, `src/lib`

**Interfaces:**
- Consumes: globals `PrintButton`, `Aside`; `file=<rootDir>/public/code/...`.
- Produces: 45 `.mdx` pages under `src/content/docs/`.

- [ ] **Step 1: Move demos, fix the two with external imports**

```bash
rm -rf src/content/docs src/content/partials
mkdir -p src/components/demo && git mv src/lib/components/demo/* src/components/demo/ && rm -rf src/lib/components
```

`session-5/2.svelte`: delete line `import { browser } from "$app/environment";`.
`session-10/3.svelte`: delete `import { NativeSelect } from "@ethercorps/kit";`; replace `<NativeSelect ... >…</NativeSelect>` with:

```svelte
<select
    class="rounded-md border border-gray-300 bg-white px-3 py-2"
    bind:value={selectedColor}
    onchange={() => applyColor(selectedColor)}
>
    <option value="white">White</option>
    <option value="#fef08a">Yellow</option>
    <option value="#86efac">Green</option>
    <option value="#93c5fd">Blue</option>
    <option value="#d8b4fe">Purple</option>
</select>
```

- [ ] **Step 2: Write `scripts/migrate-content.mjs`**

```js
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
    if (inFence) { out.push(l); continue; }
    if (/^\s*<!--.*-->\s*$/.test(l)) continue; // spacer comments
    l = l.replace(/<Callout\b([^>]*?)\s*icon=\{[^}]*\}([^>]*)>/g, "<Callout$1$2>")
         .replace(/<Callout\b/g, "<Aside").replace(/<\/Callout>/g, "</Aside>")
         .replace(/type="warning"/g, 'type="caution"')
         .replace(/<img\b([^>]*[^/])>/g, "<img$1 />")
         .replace(/src="\/preview\//g, 'src="/code/');
    for (const n of demoNames) l = l.replace(new RegExp(`<${n}\\s*/>`, "g"), `<${n} client:visible />`);
    out.push(l);
  }

  mkdirSync(dirname(dst), { recursive: true });
  writeFileSync(dst, ["---", ...fm, "---", "", ...imports, ...(imports.length ? [""] : []), ...out].join("\n"));
  rmSync(src);
  return dst;
}

const files = walk(SRC);
const written = files.map(migrate);
console.log(`migrated ${written.length} pages`);
// self-check: no leftover mdsx syntax
for (const f of written) {
  const t = readFileSync(f, "utf8");
  if (/\$lib\/|<script>|<Callout|<!--|\/preview\//.test(t.replace(/```[\s\S]*?```/g, ""))) console.error("LEFTOVER:", f);
}
```

- [ ] **Step 3: Run migration**

Run: `node scripts/migrate-content.mjs && find src/content -type d -empty -delete`
Expected: `migrated 45 pages`, no `LEFTOVER:` lines. `src/content/docs/` has 45 `.mdx`, `src/content/mcs-216` etc. gone.

- [ ] **Step 4: Remove the inline `<style>` block from session-9**

In `src/content/docs/mcs-216/section-1/session-9.mdx` delete from the line `<style>` through `</style>` (CSS already moved to `prose.css` in Task 2).

- [ ] **Step 5: Build, fix MDX errors by hand**

Run: `pnpm build 2>&1 | tail -40`
Fix each reported file/line. Known candidates: stray `{`/`<` in prose (wrap in backticks), `showLineNumbers` meta if Nimbus rejects it (strip with `sed -i '' 's/ showLineNumbers//' src/content/docs/**/*.mdx`), `class=` on raw HTML (Astro accepts; if not, `className=`). Repeat until exit 0.

- [ ] **Step 6: Page count check**

Run: `find dist -name index.html | grep -vE 'dist/(index|404|og)' | wc -l`
Expected: ≥ 45.

- [ ] **Step 7: Commit**

```bash
git add -A && git commit -m "feat: migrate content to Nimbus MDX, demos to Svelte islands"
```

---

### Task 4: Verify, lint, README, cleanup

**Files:**
- Modify: `README.md` (Site Development section)
- Delete: `scripts/migrate-content.mjs`, `AGENT.md` (scaffold boilerplate; optional keep)

- [ ] **Step 1: Lint docs**

Run: `pnpm lint:docs 2>&1 | tail -30`
Expected: no `error` level findings. Fix frontmatter/link errors; ignore style warnings.

- [ ] **Step 2: Spot-check built HTML**

```bash
d=dist
grep -c 'astro-island' $d/mcs-216/section-2/session-2/index.html        # ≥3 Svelte islands
grep -o 'src="/code/[^"]*"' $d/mcs-216/section-2/session-7/index.html    # 4 iframes
grep -c '<math' $d/mcs-216/section-1/session-9/index.html                 # ≥1
grep -c 'int main' $d/mcs-216/section-1/session-2/index.html              # ≥1 (C code imported)
grep -c 'Print Page' $d/mcs-217/session-3/index.html                      # 1
test -f public/code/mcs-216/section-2/session-7/1.html && echo iframe-target-ok
grep -rl 'refresh\|/introduction' $d/docs/index.html                       # redirect page
grep -o '<aside[^>]*' $d/mcs-216/section-2/session-2/index.html | head -1  # Aside rendered
```

- [ ] **Step 3: Preview in browser (interactive check)**

Run: `pnpm preview` and open `http://localhost:4321/mcs-216/section-2/session-2` — type in an expression input, result updates. Open `/mcs-216/section-2/session-10` — colour select persists via cookie. Stop server.

- [ ] **Step 4: README**

Replace the "Site Development" section body with:

```md
This site is built with [Nimbus](https://nimbus-docs.com) on Astro.

- `pnpm install`
- `pnpm dev` — local server
- `pnpm build` — static output in `dist/`
- `pnpm deploy` — Cloudflare Workers via wrangler

Content lives in `src/content/docs/` (MDX). Solution files in `public/code/`. Interactive demos in `src/components/demo/` (Svelte).
```

- [ ] **Step 5: Cleanup and commit**

```bash
rm scripts/migrate-content.mjs && rmdir scripts 2>/dev/null
git add -A && git commit -m "chore: verify nimbus migration, update README"
```
