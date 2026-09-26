# Syntax Lab: MCA Lab Companion

Welcome to **Syntax Lab**, a digital handbook and deep-dive resource designed for IGNOU's **MCS-216** (DAA and Web Design) and **MCS-217** (Software Engineering) courses.

This project bridges the gap between academic requirements and modern software engineering practices by providing multi-language implementations and deep conceptual explanations.

## 🚀 Key Features

- **Polyglot Implementation**: Every logic-based problem is implemented in:
  - **Python**: For rapid prototyping and readability.
  - **C**: For low-level memory and hardware interaction (Primary for IGNOU).
  - **Rust**: For exploring modern memory safety and performance.
- **Deep Explanations**: We break down underlying logic, memory management, and algorithmic complexity.
- **Example-Driven Learning**: Real-world scenarios to help retain abstract concepts for exams and viva-voce.

## 🛠️ Local Environment Setup

To run the lab exercises locally, ensure you have the following installed:

| Language | Requirement | Recommended Version | Check Command |
| -------- | ----------- | ------------------- | ------------- |
| **C** | GCC or Clang | GCC 11+ | `gcc --version` | 
| **Python** | Python 3 | 3.10+ | `python3 --version` |
| **Rust** | Rust & Cargo | Stable (1.70+) | `rustc --version` |

### How to Run Code Directly

- **C**: `gcc filename.c -o solution && ./solution`
- **Python**: `python3 solution.py`
- **Rust**: `rustc solution.rs && ./solution` (or `cargo run`)

## 💻 Site Development

This site is built with [Nimbus](https://nimbus-docs.com) on Astro.

### Prerequisites

- [Node.js](https://nodejs.org/) 24 (see `.node-version`; `fnm use` picks it up)
- [pnpm](https://pnpm.io/)

### Commands

```bash
pnpm install
pnpm dev        # local server
pnpm build      # static site in dist/ plus PDFs and ZIPs in dist/downloads/ (needs Chromium: pnpm exec playwright install chromium)
pnpm build:site # site only, fast
pnpm lint:docs  # content lint (frontmatter, internal links)
pnpm deploy     # Cloudflare Workers via wrangler
```

### Layout

- `src/content/docs/` — lab pages (MDX). Folder tree drives URLs and sidebar.
- `public/code/` — solution files (C/Python/Rust, HTML/CSS/JS). Imported into pages with ` ```c file=<rootDir>/public/code/... ` and served as-is for iframe previews.
- `src/components/demo/` — interactive demos (Svelte islands).

### Authoring conventions

- Put `<Notebook />` under headings students copy into the lab record and `<Explain />` under headings that are for understanding only. Every section gets one.
- Multi-language solutions go in `<Tabs syncKey="lang">` with one `<TabItem label="C">` per language. Multi-file programs go in plain `<Tabs>` with one `<TabItem label="Student.java">` per file. Language tabs show a "write one language" hint with a "Your language" picker (stored in localStorage key `ui-synced-tabs__lang`, shared with the synced tabs; `<LanguagePicker />` on Getting Started sets the same key); file tabs need `record="all"` to show "write every file". Tab triggers get a file-type icon automatically from the label (language name or extension, via `@iconify-json/vscode-icons`); pass `icon=""` to suppress or `icon="file-type-xyz"` to override.
- HTML solutions get `<Preview src="/code/..." height="300px" />` above the code fence.
- `pnpm lint:docs` enforces frontmatter, internal links and heading hierarchy. MCS-217 pages follow `docs-plan/mcs-217-brief.md`.
- Question papers: `python3 scripts/gen-question-papers.py` regenerates `src/content/docs/question-papers/*.mdx` from the verbatim Problem Statements on the session pages; the PDF step renders them to `dist/downloads/<section>/<section>-questions.pdf`. Re-run after editing any problem statement.
- Home page: `src/pages/index.astro` + `src/styles/home.css`, Hallmark-stamped (Marquee Hero + bento). Design tokens in `tokens.css` alias the Nimbus `--nb-*` palette (Ledger: warm cream, burnt orange). Display face Bricolage Grotesque is loaded on the home page only.
- Downloads: `scripts/build-pdfs.mjs` prints every session page to A4 PDF and zips them. Names: `<course>-<section>-session-NN.pdf`, `<course>-<section>.zip`, `<course>.zip`, `semester-N.zip`; each ZIP holds one folder per section plus the manual's question sheet. Links are rendered by `src/components/PageTools.astro`.
- Math: plain `$x^2$` works for simple inline LaTeX. Anything with braces that is not a valid JS expression (`\text{...}`, `\frac{a}{b}`) must use `<Math tex="..." />` or `<Math display tex="..." />`, because Nimbus pre-parses MDX and rejects those braces. Formula sheets on the MCSL-223 pages are the reference.

## ⚠️ Important Notice for Students

1. **Academic Integrity**: Use these resources to understand logic. Do not copy-paste code directly into lab journals.
2. **Exam Focus**: Ensure proficiency in C and Python, as they are the primary languages required by IGNOU.
3. **Viva-Voce**: Pay attention to the "Deep Explanation" sections in the documentation to prepare for oral exams.

## 📚 Official References

- [C Reference](https://en.cppreference.com/c)
- [Python Docs](https://docs.python.org/3/)
- [Rust Book](https://doc.rust-lang.org/book/)
- [IGNOU eGyanKosh](https://egyankosh.ac.in/)

---
Built with ❤️ by [The Ether](https://theether.in)
