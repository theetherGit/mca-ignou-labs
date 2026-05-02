import { getDoc } from "$lib/utils";

export async function load() {
  console.log("Loading doc for /docs", await getDoc());
  return getDoc();
}
