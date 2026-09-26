# Nimbus migration design

Date: 2026-09-26. Branch: `nimbus`. Status: approved.

## Goal

Replace the SvelteKit + Velite + mdsx + `@ethercorps/kit` site with
[Nimbus](https://nimbus-docs.com) (Astro 7). Content-heavy site, 45 lab pages,
28 Svelte demo components, ~120 solution files. Keep every page, demo,
code import, iframe preview, math block, and PWA behaviour working.

## Decisions (user-approved)

- Migrate in place on branch `nimbus`; git history preserved.
- Svelte demos stay as Svelte islands via `@astrojs/svelte`; no rewrite.
- Remove Python PDF-download tooling: `venv/`, `output/`, `egyankosh/`,
  `scripts/egyankosh.py`, `pyproject.toml`.
- Keep `worker-configuration.d.ts`, `.zed/`, `docs-plan/`, PWA service
  worker + manifest, PrintButton.
- Keep old `/docs/...` URLs working via Astro redirect.

## Target layout

```
astro.config.ts · src/content.config.ts · src/components.ts   (from scaffold)
src/content/docs/
  index.mdx, important-notice.mdx, getting-started.mdx
  mcs-216/section-1/session-{1..11}.mdx
  mcs-216/section-2/session-{1..10}.mdx
  mcs-217/introduction.mdx, session-{1..20}.mdx
src/components/demo/**           <- src/lib/components/demo (unchanged .svelte)
src/components/PrintButton.astro  <- global via components.ts
public/code/**                    <- src/lib/code/** (iframes + code fence source)
public/*.png *.pdf manifest.json  <- static/
public/sw.js                      <- runtime-cache service worker
docs-plan/, README.md             <- kept; README build section updated
```

## Content transform

One throwaway node script (`scripts/migrate-content.mjs`), run once, deleted
after. Per page:

1. `.md` -> `.mdx`.
2. Remove `<script>...</script>`. Demo component imports become top-level MDX
   imports pointing at `../../../components/demo/...`; each usage gets
   `client:visible`. PrintButton, Callout, phosphor icon imports dropped
   (PrintButton and Aside are globals).
3. `<Callout type="X" icon={...} title="Y">` -> `<Aside type="X" title="Y">`.
   Map `type` to Nimbus Aside types where names differ.
4. Frontmatter: drop `section`; add `sidebar: { order: N }` where N is the
   session number; `introduction` gets 0.
5. Code fences: `file=../../../lib/code/<X>` -> path resolving to
   `public/code/<X>` (via remark-code-import `rootDir`).
6. `src="/preview/<X>"` -> `src="/code/<X>"`.
7. MDX strictness errors (bare `{`, `<`) fixed by hand after first build.

## Config

- `astro.config.ts`: `site: https://syntax.theether.in`, title "Syntax Lab",
  description, github link, `editPattern`, `socialImage: /og.png`, `head`
  with manifest link + SW registration script.
- `sidebar.items`: `index`, `important-notice`, `getting-started`, then
  groups "MCS-216 Section 1", "MCS-216 Section 2", "MCS-217" each
  `autogenerate: { directory }`.
- `redirects: { "/docs/[...slug]": "/[...slug]", "/docs": "/" }`.
- Integration `mdx` option: `remarkPlugins: [remark-code-import, remark-math]`,
  `rehypePlugins: [@daiji256/rehype-mathml]`.
- `integrations`: add `svelte()`.
- `globals.css`: `--nb-primary` set to orange to match old theme.

## Dependencies

Add: `@astrojs/svelte`, `svelte`, `remark-code-import`, `remark-math`,
`@daiji256/rehype-mathml`.
Remove: `@sveltejs/*`, `svelte-check`, `velite`, `mdsx`, `@ethercorps/kit`,
`phosphor-svelte`, `vite` (Astro owns it), `@types/node`.

## Deploy

Scaffold `wrangler.jsonc` (Workers static assets from `dist/`), `name:
mca-ignou-labs`. Previous config targeted Cloudflare Pages; if Pages git
integration is used, set build command `pnpm build`, output dir `dist`.

## Verification

- `pnpm build` exits 0; `pnpm lint:docs` clean or only pre-existing content
  warnings.
- `astro preview` spot checks: sec2/session-2 (Svelte island renders and is
  interactive), sec2/session-7 (iframe loads), sec1/session-9 (MathML
  renders), sec1/session-2 (C/Python/Rust code imported), 217/session-3,
  `/docs/mcs-216/section-1/session-1` redirects.
- Page count in `dist/` equals 45.
