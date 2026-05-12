---
title: Session 5
description: Modular Design for the Railway Reservation System
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session focuses on dividing the Railway Reservation System into smaller modules. A good modular design makes the system easier to understand, implement, test, and modify because each part has a clear responsibility.

## Problem Statement

Develop a modular design for RRS.

## Expected Deliverable

Break the Railway Reservation System into modules and define each module's responsibility, inputs, outputs, and dependencies.

## Proposed Modules

| Module | Responsibility |
| ------ | -------------- |
| Authentication Module | User login, role validation, session handling |
| Train Search Module | Search train by route and date |
| Reservation Module | Seat selection, booking creation, PNR generation |
| Cancellation Module | Cancellation request and refund initiation |
| Payment Module | Payment request, response handling, transaction status |
| Schedule Management Module | Admin updates to train schedule and route |
| Notification Module | SMS/email alerts |
| Reporting Module | Booking, cancellation, revenue, and occupancy reports |

## Module Interface Example

| Module | Input | Output |
| ------ | ----- | ------ |
| Reservation | passenger details, schedule id, seat preference | PNR and booking status |
| Payment | PNR, amount, payment mode | transaction id and status |
| Cancellation | PNR, user id | cancellation status and refund status |

## Design Notes

- Keep payment logic separate from reservation logic.
- Keep admin functions separate from passenger functions.
- Use clear module boundaries so testing can be done independently.
