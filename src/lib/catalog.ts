// Site catalogue derived from the content collection: real session and question counts.
import { getCollection } from "astro:content";

export interface SectionDef {
  key: string;
  dir: string;
  semester: 1 | 2;
  course: string;
  courseTitle: string;
  section: string | null;
  title: string;
  blurb: string;
  index: string;
  tools: string;
}

export const SECTIONS: SectionDef[] = [
  { key: "mcs-216-section-1", dir: "mcs-216/section-1", semester: 1, course: "MCS-216", courseTitle: "DAA and Web Design Lab", section: "Section 1", title: "Design and analysis of algorithms", blurb: "Greedy, divide and conquer, dynamic programming, graphs.", index: "/mcs-216/section-1/", tools: "C · Python · Rust" },
  { key: "mcs-216-section-2", dir: "mcs-216/section-2", semester: 1, course: "MCS-216", courseTitle: "DAA and Web Design Lab", section: "Section 2", title: "Web design", blurb: "HTML forms, CSS, DOM and JavaScript with live previews.", index: "/mcs-216/section-2/", tools: "HTML · CSS · JavaScript" },
  { key: "mcs-217", dir: "mcs-217", semester: 1, course: "MCS-217", courseTitle: "Software Engineering Lab", section: null, title: "Software engineering", blurb: "Scope, estimation, SRS, DFD and ERD, design, testing, change control. Railway Reservation System throughout.", index: "/mcs-217/introduction", tools: "Documents · C · Python" },
  { key: "mcsl-222-section-1", dir: "mcsl-222/section-1", semester: 2, course: "MCSL-222", courseTitle: "OOAD and Web Technologies Lab", section: "Section 1", title: "Object oriented analysis and design", blurb: "UML diagrams with PlantUML source, then the models in C++, Rust, Python, TypeScript and SQL.", index: "/mcsl-222/section-1/", tools: "UML · C++ · Rust · Python · TypeScript" },
  { key: "mcsl-222-section-2", dir: "mcsl-222/section-2", semester: 2, course: "MCSL-222", courseTitle: "OOAD and Web Technologies Lab", section: "Section 2", title: "Web technologies", blurb: "Servlets, JSP, Spring MVC, Hibernate, Spring Boot REST and Spring Security. Full project source.", index: "/mcsl-222/section-2/", tools: "Java · Spring · MySQL" },
  { key: "mcsl-223-section-1", dir: "mcsl-223/section-1", semester: 2, course: "MCSL-223", courseTitle: "Computer Networks and Data Mining Lab", section: "Section 1", title: "Computer networks", blurb: "NS-3 scripts: wired and wireless topologies, TCP and UDP, tracing, congestion window plots.", index: "/mcsl-223/section-1/", tools: "NS-3 · C++ · gnuplot" },
  { key: "mcsl-223-section-2", dir: "mcsl-223/section-2", semester: 2, course: "MCSL-223", courseTitle: "Computer Networks and Data Mining Lab", section: null, title: "Data mining", blurb: "WEKA walkthroughs with every number recomputed in Python.", index: "/mcsl-223/section-2/", tools: "WEKA · Python" },
];
// MCSL-223 section 2 has a section label too; keep it explicit.
SECTIONS[6].section = "Section 2";

export interface Session {
  n: number;
  title: string;
  href: string;
  questions: number;
}
export interface SectionData extends SectionDef {
  sessions: Session[];
  questions: number;
}

export async function loadCatalog(): Promise<SectionData[]> {
  const docs = await getCollection("docs");
  return SECTIONS.map((def) => {
    const sessions = docs
      .filter((d) => d.id.startsWith(`${def.dir}/session-`))
      .map((d) => {
        const n = Number(/session-(\d+)$/.exec(d.id)![1]);
        const questions = (d.body ?? "").match(/^## Question \d+/gm)?.length || 1; // pages with one problem statement count as one
        return { n, title: d.data.description ?? d.data.title, href: `/${d.id}`, questions };
      })
      .sort((a, b) => a.n - b.n);
    return { ...def, sessions, questions: sessions.reduce((s, x) => s + x.questions, 0) };
  });
}

export function totals(cat: SectionData[]) {
  return {
    sections: cat.length,
    sessions: cat.reduce((s, c) => s + c.sessions.length, 0),
    questions: cat.reduce((s, c) => s + c.questions, 0),
  };
}
