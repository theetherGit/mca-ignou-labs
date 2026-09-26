// One-shot content cleanup. Delete after run.
import { readFileSync, writeFileSync } from "node:fs";
import { execSync } from "node:child_process";

const files = execSync("find src/content/docs -name '*.mdx'").toString().trim().split("\n");
const LANG = {
  Python: "Python",
  "Python Implementation": "Python",
  "C Language": "C",
  "C Implementation": "C",
  C: "C",
  Rust: "Rust",
  "Rust Implementation": "Rust",
};
let tabsMade = 0;
let previews = 0;

for (const f of files) {
  let t = readFileSync(f, "utf8");
  t = t.replace(/ showLineNumbers/g, "").replace(/floud-warshall/g, "floyd-warshall");
  t = t.replace(/^\s*<PrintButton\s*\/>\s*\n/gm, "");
  t = t.replace(/<iframe\b([^>]*?)>\s*<\/iframe>/g, (_, attrs) => {
    const src = /src="([^"]+)"/.exec(attrs)?.[1];
    const h = /height="([^"]+)"/.exec(attrs)?.[1] ?? "300px";
    previews++;
    return `<Preview src="${src}" height="${h}" />`;
  });

  // Group consecutive "### <Lang>" + fence blocks into <Tabs>.
  const lines = t.split("\n");
  const out = [];
  let i = 0;
  while (i < lines.length) {
    const groups = [];
    let j = i;
    for (;;) {
      let k = j;
      while (k < lines.length && lines[k].trim() === "") k++;
      const m = /^### (.+?)\s*$/.exec(lines[k] ?? "");
      if (!m || !LANG[m[1]]) break;
      let s = k + 1;
      while (s < lines.length && lines[s].trim() === "") s++;
      if (!/^```\w/.test(lines[s] ?? "")) break;
      let e = s + 1;
      while (e < lines.length && !/^```\s*$/.test(lines[e])) e++;
      if (e >= lines.length) break;
      groups.push({ label: LANG[m[1]], fence: lines.slice(s, e + 1) });
      j = e + 1;
    }
    if (groups.length >= 2) {
      if (out.length && out[out.length - 1].trim() !== "") out.push("");
      out.push('<Tabs syncKey="lang">');
      for (const g of groups) out.push(`<TabItem label="${g.label}">`, ...g.fence, "</TabItem>");
      out.push("</Tabs>", "");
      tabsMade++;
      i = j;
    } else {
      out.push(lines[i]);
      i++;
    }
  }
  t = out.join("\n").replace(/\n{3,}/g, "\n\n");
  writeFileSync(f, t);
}
console.log({ files: files.length, tabsMade, previews });
