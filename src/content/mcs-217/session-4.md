---
title: Session 4
description: DFD, ERD, and Data Dictionary for the Railway Reservation System
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session turns the Railway Reservation System requirements into analysis models. DFDs show how data moves through the system, ERDs show how data entities are related, and the data dictionary gives precise meaning to the terms used in those diagrams.

## Problem Statement

(a) Draw DFDs up to appropriate levels for the RRS.  
(b) Draw ERDs for the RRS and describe the relationships between different entities.  
(c) Design Data Dictionary for RRS.

## Expected Deliverables

- Context-level DFD
- Level-1 DFD
- ER diagram
- Relationship description
- Data dictionary

## DFD Scope

### External Entities

- Passenger
- Reservation Clerk
- Administrator
- Payment Gateway
- Notification Service

### Major Processes

- Search Train
- Book Ticket
- Cancel Ticket
- Manage Schedule
- Process Payment
- Generate Reports

### Data Stores

- Passenger Data
- Train Data
- Schedule Data
- Reservation Data
- Payment Data

## ERD Entities

| Entity | Important Attributes |
| ------ | -------------------- |
| Passenger | passenger_id, name, age, gender, contact |
| Train | train_id, train_name, source, destination |
| Schedule | schedule_id, train_id, date, departure_time, arrival_time |
| Reservation | pnr, passenger_id, schedule_id, seat_no, status |
| Payment | payment_id, pnr, amount, mode, payment_status |

## Data Dictionary Sample

| Name | Type | Description |
| ---- | ---- | ----------- |
| `pnr` | Identifier | Unique reservation number |
| `train_id` | Identifier | Unique train record |
| `seat_no` | String | Allocated seat number |
| `payment_status` | Enum | Pending, successful, failed, refunded |

## Submission Checklist

- Keep DFD processes as verbs.
- Keep data stores as nouns.
- Show cardinality in ERD relationships.
- Ensure all data dictionary entries are used in DFD/ERD.
