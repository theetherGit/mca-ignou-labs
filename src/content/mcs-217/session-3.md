---
title: Session 3
description: Software Requirements Specification for the Railway Reservation System
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is about preparing the Software Requirements Specification for the Railway Reservation System. The SRS is the main bridge between user needs and system design, so the goal is to clearly write what the software must do, what limits it has, and how users will interact with it.

## Problem Statement

Develop SRS (Software Requirements Specification) for the Railway Reservation System (RRS).

## Expected Deliverable

Prepare a structured SRS document for the Railway Reservation System based on the scope defined in Session 1.

## SRS Structure

| Section | Content |
| ------- | ------- |
| Introduction | Purpose, scope, definitions, references, overview |
| Overall Description | Product perspective, users, assumptions, constraints |
| Functional Requirements | Booking, cancellation, train search, seat availability, payment, refund, notifications |
| Non-Functional Requirements | Security, performance, usability, reliability, availability |
| Interface Requirements | User interface, database interface, payment gateway, notification service |
| Data Requirements | Passenger, train, schedule, booking, payment, refund |
| Appendices | Input/output formats, fact-finding notes, data model, functional model |

## Core Functional Requirements

- The system shall allow users to search trains by source, destination, and date.
- The system shall show seat availability before booking.
- The system shall create reservations only when valid passenger and payment details are provided.
- The system shall allow reservation cancellation according to railway rules.
- The system shall send booking and cancellation notifications.
- The system shall allow administrators to update train schedules and seat information.

## Non-Functional Requirements

- Private user and payment information must be protected.
- The system should be available at all times except scheduled maintenance.
- The interface should be simple enough for first-time users.
- Booking confirmation should be generated immediately after successful payment.

## Submission Checklist

- Include assumptions and constraints.
- Use numbered requirements such as `FR-01`, `NFR-01`.
- Separate functional and non-functional requirements.
- Add input/output formats and basic data dictionary.
