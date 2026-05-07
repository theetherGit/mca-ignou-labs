/// <reference types="@sveltejs/kit" />
import { build, files, version } from "$service-worker";

// Create a unique cache name for this deployment
const CACHE = `cache-${version}`;

const ASSETS = [
  ...build, // the app itself
  ...files, // everything in `static`
];

self.addEventListener("install", (event) => {
  async function addFilesToCache() {
    const cache = await caches.open(CACHE);
    try {
      await cache.addAll(ASSETS);
      console.log("Cached assets:", ASSETS);
    } catch (err) {
      console.error("Cache population failed:", err);
      throw err;
    }
  }

  event.waitUntil(
    addFilesToCache().then(() => {
      console.log("Service worker installed for version", version);
      self.skipWaiting();
    }),
  );
});

// ACTIVATE EVENT - Chain promises
self.addEventListener("activate", (event) => {
  async function deleteOldCaches() {
    for (const key of await caches.keys()) {
      if (key !== CACHE) {
        console.log("Deleting old cache:", key);
        await caches.delete(key);
      }
    }
  }

  event.waitUntil(deleteOldCaches());
});

// FETCH EVENT - Fixed cache.match() usage
self.addEventListener("fetch", (event) => {
  if (event.request.method !== "GET") return;

  async function respond() {
    const url = new URL(event.request.url);
    const cache = await caches.open(CACHE);

    // ✅ Use full request object for cache.match
    if (ASSETS.includes(url.pathname)) {
      const cached = await cache.match(event.request);
      console.log("Cache Exist:", url.pathname);
      if (cached) return cached;
    }

    try {
      const response = await fetch(event.request);

      if (!(response instanceof Response)) {
        throw new Error("invalid response from fetch");
      }

      // ✅ Add caching filters
      const shouldCache =
        response.status === 200 &&
        !response.headers.get("cache-control")?.includes("no-store") &&
        !url.pathname.startsWith("/api");

      if (shouldCache) {
        cache.put(event.request, response.clone());
        console.log("Cache Created:", url.pathname);
      }

      return response;
    } catch (err) {
      // ✅ Use event.request for fallback lookup too
      const cached = await cache.match(event.request);
      if (cached) {
        console.log(`Returning from cache: ${event.request.url}`);
        return cached;
      }
      throw err;
    }
  }

  event.respondWith(respond());
});
