/**
 * Rehype plugin for the MDX (unified) pipeline, run after Shiki and rehype-mathml.
 *
 * Nimbus's tableScroll() only runs in its own Sätteri Markdown processor, so MDX
 * output never got the scroll wrappers and wide content widened the whole page on
 * phones. This adds them:
 *  - every unclassed <table> goes in div.nb-table-scroll (scrolls inside the column)
 *  - block <math> goes in div.nb-math-block; long inline <math> in span.nb-math-scroll
 *    (MathML has no line breaking, so a long formula must scroll, not overflow)
 *  - plain-text code blocks narrow enough to print unwrapped (ASCII diagrams) get
 *    data-print-keep so print CSS keeps their columns aligned instead of wrapping
 */
interface HNode {
  type: string;
  tagName?: string;
  value?: string;
  properties?: Record<string, unknown>;
  children?: HNode[];
}

// ponytail: character-count heuristics; measure rendered width in a browser pass if these misfire.
const INLINE_MATH_SCROLL_CHARS = 24;
const PRINT_KEEP_COLUMNS = 120;

const textOf = (n: HNode): string =>
  n.type === "text" ? (n.value ?? "") : (n.children ?? []).map(textOf).join("");

const hasClass = (n: HNode): boolean => {
  const c = n.properties?.className;
  return Array.isArray(c) ? c.length > 0 : Boolean(c);
};

const wrap = (tagName: string, className: string, child: HNode): HNode => ({
  type: "element",
  tagName,
  properties: { className: [className] },
  children: [child],
});

function transform(node: HNode): void {
  const kids = node.children;
  if (!kids) return;
  for (let i = 0; i < kids.length; i++) {
    const c = kids[i];
    transform(c);
    if (c.type !== "element") continue;

    if (c.tagName === "table" && !hasClass(c)) {
      kids[i] = wrap("div", "nb-table-scroll", c);
    } else if (c.tagName === "math") {
      const block = c.properties?.display === "block";
      if (block) kids[i] = wrap("div", "nb-math-block", c);
      else if (textOf(c).length > INLINE_MATH_SCROLL_CHARS) kids[i] = wrap("span", "nb-math-scroll", c);
    } else if (c.tagName === "pre" && c.properties?.dataLanguage === "text") {
      const widest = Math.max(...textOf(c).split("\n").map((l) => l.length));
      if (widest <= PRINT_KEEP_COLUMNS) c.properties = { ...c.properties, dataPrintKeep: "" };
    }
  }
}

export default function rehypeResponsive() {
  return (tree: HNode) => transform(tree);
}
