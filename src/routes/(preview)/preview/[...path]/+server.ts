import { error, type RequestHandler } from "@sveltejs/kit";

const textModules = import.meta.glob("$lib/code/**/*.{html,css,js}", {
  query: "?raw",
  eager: false,
});

const imageModules = import.meta.glob("$lib/code/**/*.{jpg,jpeg,png}", {
  query: "?url",
  eager: false,
});

const webTypes = ["html", "css", "js"];
const imageTypes = ["jpg", "jpeg", "png"];
const supportedFileTypes = [...webTypes, ...imageTypes];

type ContentTypes = (typeof supportedFileTypes)[number];

const fileTypeToContentTypeMap: Record<ContentTypes, string> = {
  jpg: "image/jpeg",
  jpeg: "image/jpeg",
  png: "image/png",
  html: "text/html; charset=utf-8",
  js: "application/javascript; charset=utf-8", // ✅ Fixed: was "text/js"
  css: "text/css; charset=utf-8",
};

export const GET: RequestHandler = async ({ params }) => {
  const rawSlug = params.path;

  if (!rawSlug || rawSlug.trim() === "") {
    throw error(404, "No path provided");
  }

  const slug = decodeURIComponent(rawSlug);
  if (slug.includes("..") || slug.includes("\\") || slug.startsWith("/")) {
    throw error(400, "Invalid path");
  }

  const fileExt = slug.split(".").at(-1) as ContentTypes;
  if (!fileExt || !supportedFileTypes.includes(fileExt)) {
    throw error(404, "Unsupported file type");
  }

  const targetPath = `/src/lib/code/${slug}`;

  const modules = imageTypes.includes(fileExt) ? imageModules : textModules;

  if (!modules[targetPath]) {
    throw error(404, "Content not found");
  }

  try {
    const contentType = fileTypeToContentTypeMap[fileExt];

    if (imageTypes.includes(fileExt)) {
      const module = await imageModules[targetPath]();
      const publicUrl = module.default as string;
      return new Response(null, {
        status: 302,
        headers: { Location: publicUrl },
      });
    }

    const module = await modules[targetPath]();

    return new Response(module.default, {
      headers: {
        "Content-Type": contentType,
        "Cache-Control": "public, max-age=3600",
      },
    });
  } catch (err) {
    console.error("Failed to load dynamic content:", err);
    throw error(500, "Failed to load content");
  }
};
