---
title: Session 10
description: Test Cases and Test Report for Matrix Transpose Web Page
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session continues the matrix transpose web page from Session 9 and focuses on testing it. The goal is to check valid inputs, invalid inputs, browser behavior, and whether the displayed transpose is correct.

## Problem Statement

Develop test cases for the web page of Session 9. Then, develop a test report after testing using the test cases developed.

## Expected Deliverable

Prepare functional, validation, and browser-level test cases for the matrix transpose web page.

## Test Cases

| Test Case ID | Scenario | Input | Expected Result |
| ------------ | -------- | ----- | --------------- |
| WT-01 | Valid square matrix | `2 x 2` | Correct transpose displayed |
| WT-02 | Valid rectangular matrix | `2 x 3` | Output shown as `3 x 2` |
| WT-03 | Empty row/column | Blank | Validation message |
| WT-04 | Zero dimension | `0 x 3` | Validation message |
| WT-05 | Non-numeric matrix value | Text input | Validation message or handled output |

## Test Report Format

| Test Case ID | Expected Result | Actual Result | Status | Remarks |
| ------------ | --------------- | ------------- | ------ | ------- |
| WT-01 | Correct transpose | To be filled after execution | Pass/Fail | Notes |

## Submission Checklist

- Include test cases before execution.
- Include test report after execution.
- Mention browser used for testing.
- Attach screenshots if required by the lab record.
