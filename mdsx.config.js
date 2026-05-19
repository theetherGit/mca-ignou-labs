import { defineConfig } from "mdsx";
import {
  baseRemarkPlugins,
  baseRehypePlugins,
} from "@ethercorps/kit/mdsxConfig";
import { resolve } from "node:path";
import { fileURLToPath } from "node:url";
import codeImport from "remark-code-import";
import rehypeMermaid from "rehype-mermaid";

const __dirname = fileURLToPath(new URL(".", import.meta.url));

export default defineConfig({
  remarkPlugins: [...baseRemarkPlugins, codeImport],
  // @ts-expect-error shh
  rehypePlugins: [...baseRehypePlugins, rehypeMermaid],
  blueprints: {
    default: {
      path: resolve(__dirname, "./src/lib/components/blueprint.svelte"),
    },
  },
  extensions: [".md"],
});
