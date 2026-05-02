import { defineNavigation } from "@ethercorps/kit";
import ChalkboardTeacher from "phosphor-svelte/lib/ChalkboardTeacherIcon";
import RocketLaunch from "phosphor-svelte/lib/RocketLaunchIcon";
import Warning from "phosphor-svelte/lib/WarningIcon";
import { getAllDocs } from "./utils.js";
import type { Doc } from "$content/index";
import { preCalculateNavigationNeighbors } from "$lib/navigation-neighbors";

const allDocs = getAllDocs();

export function getSectionDocs(section: Doc["section"], pathPrefix = "/docs/") {
  return allDocs
    .filter((doc) => doc.section === section)
    .map((doc) => ({
      title: doc.title,
      href: `${pathPrefix}${doc.slug}`,
      description: doc.description,
    }));
}

const mcs216Section1 = getSectionDocs("MCS-216 Section 1");
const mcs216Section2 = getSectionDocs("MCS-216 Section 2");
const mcs217 = getSectionDocs("MCS-217");

export const navigation = defineNavigation({
  anchors: [
    {
      title: "Introduction",
      href: "/docs",
      description: "What is Syntax Lab?",
      icon: ChalkboardTeacher,
    },
    {
      title: "Important Notice",
      href: "/docs/important-notice",
      description: "Guidelines for using the content in this repository.",
      icon: Warning,
    },
    {
      title: "Getting Started",
      href: "/docs/getting-started",
      description: "A quick guide to get started using Syntax Lab",
      icon: RocketLaunch,
    },
  ],
  sections: [
    {
      title: "MCS-216 - Section 1",
      items: mcs216Section1,
    },
    {
      title: "MCS-216 - Section 2",
      items: mcs216Section2,
    },
    {
      title: "MCS-217",
      items: mcs217,
    },
  ],
});

export const neighborLookup = preCalculateNavigationNeighbors(navigation);

export function getNavigationNeighbors(pathname: string) {
  return neighborLookup.get(pathname);
}
