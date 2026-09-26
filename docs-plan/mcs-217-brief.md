# MCS-217 authoring brief

Read this fully before writing any MCS-217 session page. Every page must follow it so the 20 sessions read as one coherent lab record.

## Sources of truth

- `/tmp/mcs-217.txt` is the extracted text of the official IGNOU MCS-217 lab manual (`public/mcs-217.pdf`). Section 1.7 (search "LIST OF PROBLEMS") has the exact wording of every session. Sections before it explain what IGNOU expects in a scope statement, estimation, SRS, DFD, ERD, data dictionary, design, test cases, coding standards. Quote the session problem statement verbatim.
- `docs-plan/mcs-217-checklist.md` lists the expected deliverable per session.
- `src/content/docs/mcs-216/section-1/session-3.mdx` is the tone reference: teaching note, direct, student-facing, no filler.

## The running case study: Railway Reservation System (RRS)

Sessions 1 to 6, 13 and 14 all describe the SAME system. Use exactly these names.

**Actors:** Passenger (books online), Reservation Clerk (books at counter, handles cancellations), Administrator (manages trains, schedules, fares, reports), Payment Gateway (external), Notification Service (external: SMS and email).

**Modules (use these eight, this order):**
1. User Management (register, login, roles)
2. Train and Schedule Management (admin adds trains, routes, stations, coaches, fares)
3. Search and Availability (search by source, destination, date; seat availability per class)
4. Booking (passenger details, seat allocation, PNR generation)
5. Cancellation and Refund (cancel by PNR, refund rules by time before departure)
6. Payment (initiate, confirm, fail; talks to the gateway)
7. Notification (booking confirmation, cancellation, schedule change)
8. Reports (occupancy, revenue, cancellations; admin only)

**Entities (data model):** User(user_id, name, email, mobile, password_hash, role), Passenger(passenger_id, booking_id, name, age, gender, berth_preference), Station(station_code, name, city), Train(train_no, name, type, total_coaches), Route(train_no, station_code, sequence, arrival_time, departure_time, distance_km), Schedule(schedule_id, train_no, run_date, status), Coach(coach_id, train_no, class, seat_count), Seat(seat_id, coach_id, seat_no, berth_type), Booking(pnr, user_id, schedule_id, from_station, to_station, class, booking_time, status, total_fare), Payment(payment_id, pnr, amount, mode, status, txn_ref, paid_at), Refund(refund_id, pnr, amount, reason, processed_at), Fare(train_no, class, rate_per_km).

**Business rules:** PNR is a 10-digit unique number. Booking statuses: CONFIRMED, WAITLISTED, CANCELLED. Refund: 100% minus a flat clerkage if cancelled more than 48 hours before departure, 50% between 48 and 12 hours, none under 12 hours. Waitlist gets promoted on cancellation in order. A schedule cannot be booked after departure. Max 6 passengers per PNR.

**Estimation baseline (Session 2, reused by 13):** Function point count for the eight modules totals 214 unadjusted function points; VAF 1.05; 225 adjusted FP; 60 LOC per FP in Python gives 13,500 LOC; COCOMO organic mode. Show the calculations in Session 2; later sessions may cite the results.

**Session 13 implementation:** a single Python 3 file, `public/code/mcs-217/session-13/rrs.py`, console menu, JSON file persistence (`rrs_data.json`), no third-party packages. Implements modules 2 to 5 for one user role each (admin adds train and schedule; passenger searches, books, cancels; PNR lookup). Around 300 lines, readable, function per menu action, docstrings. Session 14 shows a change request applied to that file (a second file `rrs_v2.py` with the change) and a diff summary.

## Page structure (every session)

```mdx
---
title: Session N
description: <one line, the deliverable>
sidebar:
  order: N
---

<intro paragraph: what this session produces and why the topic matters, 3 to 5 sentences>

## Objectives

<Explain />

- ...

## Problem Statement

<Notebook />

<verbatim wording from the manual, section 1.7>

## Concept

<Explain />

<what a student must understand to produce the deliverable; tied to this session, not a generic tutorial; 2 to 6 short subsections with ### headings>

## Deliverable
   (rename to the actual artefact: "Statement of Scope", "Estimation", "SRS", "Data Flow Diagrams", "Test Cases", "Program", etc. Use several ## sections when the session has parts (a), (b), (c).)

<Notebook />

<the complete artefact a student writes in the record: full document, tables, diagrams as text, program with output. This is the bulk of the page. Never a placeholder, never "add your own". Real values, real names from the RRS model.>

## Viva Questions

<Explain />

- 6 to 10 questions with one-line answers, format: **Q:** ... **A:** ...

## Common Mistakes

<Explain />

- 4 to 6 bullets

## Session Summary

<Notebook />

<what to submit: a checklist of 3 to 6 items>
```

Marks: `<Notebook />` means copy into the lab record; `<Explain />` means read for understanding. Put exactly one mark directly under each `##` heading (blank line before and after). Do not mark `###` headings.

## Diagrams

No image files. Draw DFDs, ERDs, structure charts, and screen layouts as plain text inside fenced code blocks with the language `text`, using boxes and arrows, e.g.

```text
 Passenger ----search criteria----> [1.0 Search Trains] ----train list----> Passenger
                                          |
                                     reads |
                                          v
                                   D1 | Train Schedule
```

Follow each diagram with a table that lists every process, data flow, and data store, because students redraw the diagram by hand from the table.

## Code

Programs go in files under `public/code/mcs-217/session-N/` and are pulled into the page with an empty fence:

````mdx
```c title="matrix_multiply.c" file=<rootDir>/public/code/mcs-217/session-7/matrix_multiply.c

```
````

HTML pages get a live preview: `<Preview src="/code/mcs-217/session-9/transpose.html" height="420px" />` placed before the code fence. Every program must actually run; include a "Sample Output" ### subsection with real output in a `text` fence. C code compiles with `gcc -Wall`, no warnings. JavaScript runs in a browser with no libraries.

## MDX rules (the build breaks otherwise)

- No `{` or `}` in prose. Write "curly braces" or put the text in backticks.
- No `<` followed by a letter in prose (e.g. "a<b"). Put it in backticks.
- No HTML comments. No `<br>`; use `<br />`. Self-close `<img />`.
- Headings increase one level at a time (`##` then `###`, never `##` then `####`).
- No bare URLs; use `[text](url)`. Internal links look like `/mcs-217/session-3`.
- Tables need a header row and a separator row. Keep cells free of `|`.
- Do not import anything. `Aside`, `Notebook`, `Explain`, `Preview`, `Tabs`, `TabItem` are globals. Use `<Aside type="tip" title="...">` sparingly for one important warning per page at most.
- Frontmatter has exactly: title, description, sidebar.order.

## Length and voice

150 to 350 lines per session. Write for a second-year MCA distance learner who will hand-copy the deliverable and defend it in a viva. Plain English, active voice, short sentences. No motivational filler, no "in this exciting session". Indian railway vocabulary is fine (PNR, berth, Tatkal, coach classes SL, 3A, 2A, 1A).
