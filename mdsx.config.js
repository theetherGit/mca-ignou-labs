import { defineConfig } from "mdsx";
import {
  baseRemarkPlugins,
  baseRehypePlugins,
} from "@ethercorps/kit/mdsxConfig";
import { resolve } from "node:path";
import { fileURLToPath } from "node:url";
import codeImport from "remark-code-import";
import remarkMath from "remark-math";
import rehypeKatex from "rehype-katex";

const __dirname = fileURLToPath(new URL(".", import.meta.url));

export default defineConfig({
  remarkPlugins: [...baseRemarkPlugins],
  // @ts-expect-error shh
  rehypePlugins: [...baseRehypePlugins],
  blueprints: {
    default: {
      path: resolve(__dirname, "./src/lib/components/blueprint.svelte"),
    },
  },
  extensions: [".md"],
});
