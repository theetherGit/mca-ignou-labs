#!/usr/bin/env python3
"""Generate typed question papers (MDX) from the verbatim problem statements on the session pages.

Re-run whenever a session's Problem Statement changes:
    python3 scripts/gen-question-papers.py

Output: src/content/docs/question-papers/<section-key>.mdx (custom-mode pages, not in the sidebar).
scripts/build-pdfs.mjs prints each one to dist/downloads/<section-key>/<section-key>-questions.pdf.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "src/content/docs"
OUT = DOCS / "question-papers"

PAPERS = [
    {
        "key": "mcsl-222-section-1", "dir": "mcsl-222/section-1", "semester": "II",
        "course": "MCSL-222", "course_title": "Object Oriented Analysis and Design and Web Technologies Lab",
        "section": "Section 1", "section_title": "Object Oriented Analysis and Design",
        "instructions": [
            "Prepare a draft solution for every exercise before the session and implement it during the designated lab session.",
            "For each exercise, write the problem description in about 300 to 500 words and list the basic assumptions. This limits the scope of your solution and helps the evaluator.",
            "Draw diagrams with a UML tool (StarUML, ArgoUML or equivalent). Name every class, actor, message and state.",
            "Sessions 8 to 10 may be implemented in C++, Java, Rust, Python or JavaScript; the class diagrams in the figures are the specification.",
        ],
    },
    {
        "key": "mcsl-222-section-2", "dir": "mcsl-222/section-2", "semester": "II",
        "course": "MCSL-222", "course_title": "Object Oriented Analysis and Design and Web Technologies Lab",
        "section": "Section 2", "section_title": "Web Technologies",
        "instructions": [
            "Use Apache NetBeans IDE or Eclipse IDE with JDK 17 or later and Apache Tomcat 10.",
            "The database named IGNOU with a Student table created in Session 1, Exercise 5 is reused in later sessions; keep its schema in your record.",
            "Sessions 3 onward extend one Maven project. Keep the project after every session.",
            "Make and state any assumptions the exercise leaves open.",
        ],
    },
    {
        "key": "mcsl-223-section-1", "dir": "mcsl-223/section-1", "semester": "II",
        "course": "MCSL-223", "course_title": "Computer Networks and Data Mining Lab",
        "section": "Section 1", "section_title": "Computer Networks",
        "instructions": [
            "Implement every exercise with the NS-3 network simulator (version 3.36 or later).",
            "Submit the simulation script, the console output, the trace or pcap summary and the plot for every exercise that asks for one.",
            "Show the throughput, delay and window calculations alongside the simulated values.",
        ],
    },
    {
        "key": "mcsl-223-section-2", "dir": "mcsl-223/section-2", "semester": "II",
        "course": "MCSL-223", "course_title": "Computer Networks and Data Mining Lab",
        "section": "Section 2", "section_title": "Data Mining",
        "instructions": [
            "Use the open source WEKA toolkit (version 3.8 or later). The sample datasets are in the data folder of the installation.",
            "For every run, record the exact parameter values, the run information block and the numbers you can verify by hand (support, confidence, entropy, accuracy, kappa, sum of squared errors).",
            "Interpret every output; a screenshot alone does not answer an exercise.",
        ],
    },
]

Q_RE = re.compile(r"## Question (\d+)\n\n### Problem Statement\n\n<Notebook />\n\n([\s\S]*?)\n\n### Solution")


def sessions(paper):
    out = []
    files = sorted((DOCS / paper["dir"]).glob("session-*.mdx"), key=lambda p: int(re.search(r"session-(\d+)", p.name).group(1)))
    for f in files:
        s = f.read_text()
        n = int(re.search(r"session-(\d+)", f.name).group(1))
        topic = re.search(r'^description: "?(.*?)"?$', s, re.M).group(1)
        qs = Q_RE.findall(s)
        if not qs:
            raise SystemExit(f"no questions found in {f}")
        out.append((n, topic, qs))
    return out


def render(paper):
    secs = sessions(paper)
    total = sum(len(q) for _, _, q in secs)
    L = [
        "---",
        f'title: "{paper["course"]} {paper["section"]} Question Paper"',
        f'description: "Typed question paper for {paper["course"]} {paper["section"]}, {paper["section_title"]}: all {total} lab exercises, session by session."',
        "mode: custom",
        "sidebar: false",
        "searchable: false",
        "noindex: true",
        "tableOfContents: false",
        "---",
        "",
        '<article class="qp docs-content">',
        "",
        '<header class="qp-head">',
        '  <p class="qp-uni">Indira Gandhi National Open University</p>',
        '  <p class="qp-prog">Master of Computer Applications (MCA)</p>',
        f'  <h1 class="qp-title">{paper["course"]}: {paper["course_title"]}</h1>',
        f'  <p class="qp-sec">{paper["section"]}: {paper["section_title"]}</p>',
        '  <dl class="qp-meta">',
        f'    <div><dt>Semester</dt><dd>{paper["semester"]}</dd></div>',
        f'    <div><dt>Sessions</dt><dd>{len(secs)}</dd></div>',
        f'    <div><dt>Exercises</dt><dd>{total}</dd></div>',
        "    <div><dt>Source</dt><dd>IGNOU lab manual, list of lab exercises</dd></div>",
        "  </dl>",
        "</header>",
        "",
        "## Instructions",
        "",
    ]
    L += [f"{i}. {t}" for i, t in enumerate(paper["instructions"], 1)]
    L.append("")
    for n, topic, qs in secs:
        L += [f'<section class="qp-session">', "", f"## Session {n}: {topic}", ""]
        for num, body in qs:
            body = body.strip()
            first, _, rest = body.partition("\n")
            L.append(f'<p class="qp-q"><strong>Q{num}.</strong> {first}</p>')
            if rest.strip():
                L += ["", rest.strip()]
            L.append("")
        L += ["</section>", ""]
    L += [
        '<footer class="qp-foot">',
        f'  <p>End of question paper. Worked solutions for every exercise: syntax.theether.in/{paper["dir"]}/</p>',
        "</footer>",
        "",
        "</article>",
        "",
    ]
    return "\n".join(L)


OUT.mkdir(exist_ok=True)
for paper in PAPERS:
    (OUT / f'{paper["key"]}.mdx').write_text(render(paper))
    print(paper["key"], "written")
