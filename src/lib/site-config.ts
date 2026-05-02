import { defineSiteConfig } from "@ethercorps/kit";

export const siteConfig = defineSiteConfig({
  name: "Syntax Lab",
  url: "https://syntax.theether.in",
  ogImage: {
    url: "https://docs.sveco.dev/og.png",
    height: "630",
    width: "1200",
  },
  description: "Explained guide for IGNOU MCA Labs",
  author: "The Ether",
  keywords: ["MCA IGNOU", "IGNOU MCA", "Labs", "Guides", "Explanation"],
  license: {
    name: "MIT",
    url: "https://github.com/theetherGit/mca-ignou-labs/blob/main/LICENSE",
  },
  links: {
    x: "https://x.com/theether0",
    github: "https://github.com/theetherGit/mca-ignou-labs",
  },
});
