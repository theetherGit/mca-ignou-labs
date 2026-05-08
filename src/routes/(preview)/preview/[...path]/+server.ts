import { error, type RequestHandler } from "@sveltejs/kit";

const contentModules = import.meta.glob(
  "$lib/code/**/*.{html,css,js,jpg,png}",
  {
    query: "?raw",
    eager: false,
  },
);

const webTypes = ["html", "css", "js"];

const supportedFileTypes = [...webTypes, "jpg", "png"];

type ContentTypes = (typeof supportedFileTypes)[number];

const fileTypeToContentTypeMap: Record<ContentTypes, string> = {
  jpg: "image/jpeg",
  jpeg: "image/jpeg",
  png: "image/png",
  html: "text/html; charset=utf-8",
  js: "text/js; charset=utf-8",
  css: "text/css; charset=utf-8",
};

export const GET: RequestHandler = async ({ params }) => {
  const slug = params.path;

  // Handle root path or missing slug
  if (!slug || slug.trim() === "") {
    throw error(404, "No path provided");
  }

  // 🛡️ SECURITY: Prevent directory traversal attacks
  if (slug.includes("..") || slug.includes("\\") || slug.startsWith("/")) {
    throw error(400, "Invalid path");
  }

  const fileExt: ContentTypes = slug.split(".").at(-1) as ContentTypes;

  if (!fileExt || !supportedFileTypes.includes(fileExt)) {
    throw error(404, "Unsupported file type");
  }

  const targetPath = `/src/lib/code/${slug}`;

  if (!contentModules[targetPath]) {
    throw error(404, "Content not found");
  }

  try {
    // Dynamically import the matched file
    const module = await contentModules[targetPath]();

    const contentType = fileTypeToContentTypeMap[fileExt];

    // Assuming each file has a `default` export containing HTML/string
    return new Response(module?.default, {
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
