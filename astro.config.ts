import { defineConfig } from "astro/config";
import svelte from "@astrojs/svelte";
import tailwindcss from "@tailwindcss/vite";
import nimbus, { defineConfig as defineNimbusConfig } from "@cloudflare/nimbus-docs";
import { tableScroll } from "@cloudflare/nimbus-docs/markdown";
import { unified } from "@astrojs/markdown-remark";
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
  head: [{ tag: "link", attrs: { rel: "manifest", href: "/manifest.json" } }],
  sidebar: {
    // Three course groups collapsed by default; the group holding the current page opens.
    defaultCollapsed: true,
    items: [
      "introduction",
      "important-notice",
      "getting-started",
      {
        label: "Semester 1",
        items: [
          { label: "MCS-216 Section 1", autogenerate: { directory: "mcs-216/section-1" } },
          { label: "MCS-216 Section 2", autogenerate: { directory: "mcs-216/section-2" } },
          { label: "MCS-217", autogenerate: { directory: "mcs-217" } },
        ],
      },
      {
        label: "Semester 2",
        items: [
          { label: "MCSL-222 Section 1", badge: { text: "Draft", variant: "caution" }, autogenerate: { directory: "mcsl-222/section-1" } },
          { label: "MCSL-222 Section 2", badge: { text: "Draft", variant: "caution" }, autogenerate: { directory: "mcsl-222/section-2" } },
          { label: "MCSL-223 Section 1", badge: { text: "Draft", variant: "caution" }, autogenerate: { directory: "mcsl-223/section-1" } },
          { label: "MCSL-223 Section 2", badge: { text: "Draft", variant: "caution" }, autogenerate: { directory: "mcsl-223/section-2" } },
        ],
      },
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
    svelte(),
    nimbus(nimbusConfig, {
      rules: {
        "nimbus/frontmatter-shape": "error",
        "nimbus/internal-link": "error",
        "nimbus/heading-hierarchy": "error",
      },
      // `:::note` directives need the Sätteri processor; content uses <Aside> directly.
      admonitions: false,
      markdown: { hastPlugins: [tableScroll()] },
      // Nimbus installs its own Sätteri processor for .md output and MDX would inherit
      // it. Sätteri has no math syntax and lets the MDX parser swallow `{n}` inside
      // `$\binom{n}{k}$`, so .mdx runs through the unified pipeline where remark-math
      // wins before expression parsing and remark-code-import / rehype-mathml apply.
      mdx: {
        processor: unified({
          // @ts-expect-error remark-code-import's transformer type is looser than Astro's RemarkPlugin; runtime-compatible.
          remarkPlugins: [[codeImport, { rootDir: process.cwd() }], remarkMath],
          rehypePlugins: [rehypeMathML],
        }),
      },
    }),
  ],
});
