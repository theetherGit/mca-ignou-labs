---
title: Session 12
description: Correct Program That Is Not Reliable
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session focuses on software reliability. A program can be correct for normal input but unreliable if it fails for edge cases, invalid input, repeated execution, or unexpected environments.

## Problem Statement

Write a program that is correct but still not reliable. Justify your answer. Make necessary assumptions.

## Expected Deliverable

Provide a program that works for normal input but fails or behaves unpredictably under edge cases, invalid inputs, environment issues, or repeated use.

## Reliability Problems

- No handling for invalid input.
- Division by zero risk.
- Buffer overflow risk.
- File handling without checking errors.
- Network or database assumptions without fallback.
- Random or timing-dependent behavior.

## Difference Between Quality and Reliability

| Quality | Reliability |
| ------- | ----------- |
| Focuses on readability, maintainability, design | Focuses on consistent correct behavior |
| Poor quality code can still run correctly | Unreliable code may fail under certain conditions |

## Submission Checklist

- Include the program.
- Show normal successful output.
- Show failing/unsafe condition.
- Explain why the program is not reliable.
- Suggest reliability improvements.
