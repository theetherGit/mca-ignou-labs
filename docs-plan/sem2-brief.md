# Semester 2 solutions brief (MCSL-222, MCSL-223)

Read this fully before editing any Semester 2 session page. The pages already exist as skeletons with every question copied verbatim from the manual; your job is to replace the placeholders with complete, verified solutions and keep everything else.

## What exists

- `src/content/docs/mcsl-222/section-1/` OOAD (UML), 10 sessions, questions 1 to 23.
- `src/content/docs/mcsl-222/section-2/` Web Technologies (Servlet, JSP, Spring, Hibernate, Spring Boot, Security), 10 sessions, questions 1 to 46.
- `src/content/docs/mcsl-223/section-1/` Computer Networks (NS-3), 10 sessions, questions 1 to 25.
- `src/content/docs/mcsl-223/section-2/` Data Mining (WEKA), 10 sessions, questions 1 to 23.
- Manual text: `/tmp/mcsl-222-section-1.txt`, `/tmp/mcsl-222-section-2.txt`, `/tmp/mcsl-223.txt` (the MCSL-223 file has the networks lab first, data mining from the line "SECTION 2 DATA MINING LAB"). The manuals' explanatory sections (NS-3 setup and examples, WEKA walkthroughs, Servlet and Spring project creation) are the primary source for tool names, menu paths and expected output shapes.
- Tone reference for a finished page: `src/content/docs/mcs-217/session-7.mdx` (program) and `src/content/docs/mcs-217/session-4.mdx` (diagrams and tables).

## What to change on each page

Keep the frontmatter, the intro, Objectives, Questions Covered, Preparation, every Problem Statement (verbatim, do not edit), the Formula Sheet (if present) and the Session Summary. Then:

1. Remove the `<Aside type="caution" title="Draft: questions final, solutions pending">...</Aside>` block.
2. In the Questions Covered table change every "Solution pending" to "Complete".
3. Replace each `### Solution` placeholder ("Solution pending. Prepare using the notes above...") with the full solution. Keep the `<Notebook />` mark under `### Solution`. Structure inside a solution, as `####` headings:
   - `#### Assumptions` (OOAD and design questions only; the manual requires a 300 to 500 word problem description plus assumptions for every diagram; write the description as prose under the heading and the assumptions as a bulleted list)
   - `#### Steps` (numbered, exact tool actions: menu names, dialog fields, commands)
   - `#### Program` / `#### Diagram` / `#### Configuration` as appropriate
   - `#### Output` (real captured output in a `text` fence, or for GUI tools the exact numbers WEKA or NS-3 prints, reproduced)
   - `#### Explanation` (why it works; tie to the formula sheet where one exists)
4. Add `## Viva Questions` (`<Explain />`, 6 to 8 `**Q:** ... **A:** ...` lines) and `## Common Mistakes` (`<Explain />`, 4 to 6 bullets) before Session Summary if the page lacks them.
5. Update the Session Summary checklist to name the actual artefacts produced.

Marks: exactly one `<Notebook />` or `<Explain />` directly under every `##` heading, none under `###` or `####`. Solutions are `<Notebook />`.

## Code files

Programs go under `public/code/<course>/<section>/session-N/` and are included with an empty fence:

````mdx
```cpp title="student_registration.cpp" file=<rootDir>/public/code/mcsl-222/section-1/session-8/student_registration.cpp

```
````

Supported fence languages here: `cpp`, `c`, `java`, `python`, `js`, `html`, `css`, `xml`, `sql`, `properties`, `yaml`, `bash`, `text`. Every file you write must be complete (imports, main, config) so a student can copy it and run it.

- C++: compile with `clang++ -std=c++17 -Wall -Wextra` and run; paste the real output. Use C++ for the OOAD implementation sessions (the manual allows C++ or Java; no JDK is installed here).
- Python: run with `python3`, standard library only; paste the real output.
- Java for Servlet, JSP, Spring: no JDK, Tomcat or Maven is available, so the code cannot be executed here. Write it against Jakarta EE 10 / Spring Boot 3 / Spring 6 APIs (`jakarta.servlet`, `jakarta.persistence`, Spring Security 6 `SecurityFilterChain`), double-check every import and annotation, include the `pom.xml` fragments and `application.properties` the code needs, and under `#### Output` describe the expected browser or console result. State in one sentence under `#### Output` that the listing was checked by reading, not executed. Do not fake console logs.
- NS-3: scripts in C++ for ns-3.36 or later, using the helper API (`NodeContainer`, `PointToPointHelper`, `InternetStackHelper`, `Ipv4AddressHelper`, `UdpEchoServerHelper`, `OnOffHelper`, `PacketSinkHelper`, `YansWifiHelper`, `OlsrHelper`, `MobilityHelper`, `FlowMonitorHelper`, `Config::ConnectWithoutContext` for cwnd). NS-3 cannot run here; model each script on the tutorial examples referenced in the manual, keep it complete and compilable in `scratch/`, and under `#### Output` give the output format NS-3 prints (echo client/server lines, FlowMonitor statistics) with plausible values clearly labelled as expected, plus the formula-based calculation the student must show. Plots: give the gnuplot or matplotlib script that reads the trace file.
- WEKA: no WEKA here. Give exact GUI paths (Explorer, Preprocess, Open file, Associate, Choose, Apriori, parameter names) and reproduce the output blocks WEKA prints. Where the numbers can be computed, compute them for real with a small Python script and paste those numbers: Apriori on contact-lenses (24 rows, the dataset is in the manual and in WEKA's data folder; the full data is reproduced below), entropy and information gain on the 14-row weather data, k-means on iris (the iris data is well known; a 30-row sample is acceptable if labelled), regression on a small numeric set. Write the Python you used as a code file so students can check.

### contact-lenses data (24 rows, 5 nominal attributes)

age in young, pre-presbyopic, presbyopic; spectacle-prescrip in myope, hypermetrope; astigmatism in no, yes; tear-prod-rate in reduced, normal; contact-lenses in soft, hard, none.

```text
young,myope,no,reduced,none
young,myope,no,normal,soft
young,myope,yes,reduced,none
young,myope,yes,normal,hard
young,hypermetrope,no,reduced,none
young,hypermetrope,no,normal,soft
young,hypermetrope,yes,reduced,none
young,hypermetrope,yes,normal,hard
pre-presbyopic,myope,no,reduced,none
pre-presbyopic,myope,no,normal,soft
pre-presbyopic,myope,yes,reduced,none
pre-presbyopic,myope,yes,normal,hard
pre-presbyopic,hypermetrope,no,reduced,none
pre-presbyopic,hypermetrope,no,normal,soft
pre-presbyopic,hypermetrope,yes,reduced,none
pre-presbyopic,hypermetrope,yes,normal,none
presbyopic,myope,no,reduced,none
presbyopic,myope,no,normal,none
presbyopic,myope,yes,reduced,none
presbyopic,myope,yes,normal,hard
presbyopic,hypermetrope,no,reduced,none
presbyopic,hypermetrope,no,normal,soft
presbyopic,hypermetrope,yes,reduced,none
presbyopic,hypermetrope,yes,normal,none
```

### weather.nominal data (14 rows)

```text
outlook,temperature,humidity,windy,play
sunny,hot,high,FALSE,no
sunny,hot,high,TRUE,no
overcast,hot,high,FALSE,yes
rainy,mild,high,FALSE,yes
rainy,cool,normal,FALSE,yes
rainy,cool,normal,TRUE,no
overcast,cool,normal,TRUE,yes
sunny,mild,high,FALSE,no
sunny,cool,normal,FALSE,yes
rainy,mild,normal,FALSE,yes
sunny,mild,normal,TRUE,yes
overcast,mild,high,TRUE,yes
overcast,hot,normal,FALSE,yes
rainy,mild,high,TRUE,no
```

## Diagrams (OOAD)

No image tools are installed. For every UML diagram give three things in this order:

1. A table of elements (classes with attributes and operations; actors and use cases; lifelines and messages; states and transitions; components and interfaces; nodes and artefacts).
2. A `text` fence with an ASCII sketch of the diagram (boxes and arrows), small enough to redraw by hand.
3. A `text` fence titled `title="<name>.puml"` holding PlantUML source that renders the same diagram at plantuml.com or in VS Code. Use standard PlantUML syntax (`class`, `actor`, `usecase`, `participant`, `state`, `component`, `node`, `-->`, `--|>`, `o--`, `*--`, `..>`), and keep it correct: a student will paste it.

For C++ implementations of the figures (Sessions 8 to 10), model the diagram exactly: every class, attribute, operation and association end, with multiplicity `*` as `std::vector`. Session 10 produces `CREATE TABLE` statements in a `sql` fence plus a mapping-rule table.

## Math

Simple inline LaTeX without braces works as `$x^2$`. Anything with `\text{}`, `\frac{}{}`, subscripts in braces or other braces MUST use the global component: `<Math tex="\frac{a}{b}" />` inline or `<Math display tex="..." />` for a block. The build fails otherwise. Backslashes need no escaping inside the attribute; avoid double quotes inside `tex`.

## MDX rules (the build breaks otherwise)

- No `{` or `}` in prose. No `<` followed by a letter in prose (write "a is less than b" or use backticks).
- No HTML comments. Self-close `<img />` and `<br />`.
- Headings increase one level at a time. Do not add `#` headings.
- Tables: header row, separator row, no `|` inside cells.
- No bare URLs: `[text](url)`.
- Do not import anything; `Aside`, `Notebook`, `Explain`, `Preview`, `Tabs`, `TabItem`, `Math` are globals.

## Length and voice

Each session page should end at 250 to 500 lines. Plain English, active voice, short sentences, second-year MCA distance learner who will hand-copy the deliverable and face a viva. No motivational filler.

## Finish

Run from the repo root: `eval "$(fnm env)" && fnm use 24.15.0 >/dev/null && pnpm lint:docs 2>&1 | tail -15` and fix every error in your files. Do not run `pnpm build` (another process owns the build). Report: files written with line counts, what was executed for real and what was checked by reading, lint result.
