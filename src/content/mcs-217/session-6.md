---
title: Session 6
description: User Interface Design for the Railway Reservation System
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is about designing the screens and user interaction flow for the Railway Reservation System. The aim is to decide what users see, what data they enter, what validations are required, and how the system responds.

## Problem Statement

Develop user interface design for RRS.

## Expected Deliverable

Design the main screens, navigation flow, form fields, validation rules, and output messages for the Railway Reservation System.

## Screens Required

| Screen | Purpose |
| ------ | ------- |
| Login / Register | User authentication |
| Train Search | Source, destination, date, class |
| Train Results | Available trains and seat availability |
| Passenger Details | Passenger information entry |
| Payment | Payment mode and transaction confirmation |
| Booking Confirmation | PNR, train, seat, journey details |
| Cancellation | PNR lookup and cancellation request |
| Admin Dashboard | Train, schedule, and report management |

## Validation Rules

- Required fields must not be empty.
- Email and phone number must follow valid formats.
- Journey date must not be in the past.
- Number of passengers must stay within allowed limit.
- Payment confirmation must be received before confirmed booking.

## Submission Checklist

- Include rough sketches or wireframes.
- Include input fields and buttons for every screen.
- Mention error messages.
- Mention success messages.
