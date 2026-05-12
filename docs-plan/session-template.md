# Universal Lab Session Template

Use this structure for every lab session. Keep the YAML frontmatter in the existing project format unless the content schema is intentionally changed later.

```md
<PrintButton />

Opening explanation:
Start with a short student-friendly introduction. Explain what the session is about, why the topic matters, and what the learner will be able to do after completing it. Do not start the page with administrative metadata.

## Objectives

- Objective 1
- Objective 2
- Objective 3

## Concept / Background

Explain the main topic before jumping into questions. Keep this tied to the lab session, not a generic tutorial.

For algorithm sessions, explain the technique, data structures, formulas, and common use cases.
For web sessions, explain the HTML/CSS/JavaScript concept used in the exercises.
For software engineering sessions, explain the document, diagram, testing activity, or process being practiced.

## Questions Covered

| Question | Requirement | Status |
| -------- | ----------- | ------ |
| Q1 | Exact requirement from lab manual | Draft / Complete |

## Question 1

### Problem Statement

Write the exact lab manual question.

### Explanation / Approach

Explain what the question is asking and how to solve it.

### Step-by-Step Solution

Show the manual steps needed for lab record submission.

### Implementation / Deliverable

For coding labs, include C, Python, Rust, JavaScript, or HTML/CSS as appropriate.
For software engineering labs, include the actual document, table, diagram description, test cases, or report.

### Output / Result

Show sample output, final table, final diagram summary, or final document result.

### Complexity / Evaluation

For algorithm sessions, include time complexity, space complexity, operation counts, loop counts, or comparisons.
For software engineering sessions, include assumptions, validation checklist, traceability, risks, and review notes.

### Viva Questions

- Question likely to be asked in viva

### Common Mistakes

- Mistake students commonly make

## Question 2

Repeat the same structure for every question.

## Session Summary

Summarize what was produced and what should be submitted in the lab record.

## Lab Manual Reference

Keep this near the end if the page needs source traceability.

| Field | Value |
| ----- | ----- |
| Course | MCS-216 / MCS-217 |
| Section | Section title from the lab manual |
| Session | Session number and title |
| Source | `static/mcs-216.pdf` or `static/mcs-217.pdf` |
```

## Notes

- The page should read like a teaching note, not an index card.
- Avoid leading with "Lab Manual Reference" in actual session pages.
- Use "Questions Covered" for long sessions, but the main flow should still solve questions one by one.
- If a session is incomplete, mark missing graph/table/image data in the relevant question instead of making the whole page feel like a placeholder.
