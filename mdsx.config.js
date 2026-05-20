import { defineConfig } from "mdsx";
import {
  baseRemarkPlugins,
  baseRehypePlugins,
} from "@ethercorps/kit/mdsxConfig";
import { resolve } from "node:path";
import { fileURLToPath } from "node:url";
import codeImport from "remark-code-import";
import remarkMath from "remark-math";
import rehypeMathML from "@daiji256/rehype-mathml";

const __dirname = fileURLToPath(new URL(".", import.meta.url));

export default defineConfig({
  remarkPlugins: [...baseRemarkPlugins, codeImport, remarkMath],
  // @ts-expect-error shh
  rehypePlugins: [...baseRehypePlugins, rehypeMathML],
  blueprints: {
    default: {
      path: resolve(__dirname, "./src/lib/components/blueprint.svelte"),
    },
  },
  extensions: [".md"],
});
