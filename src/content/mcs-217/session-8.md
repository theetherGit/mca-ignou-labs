---
title: Session 8
description: Test Cases for Matrix Multiplication Program
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is about testing the matrix multiplication program from Session 7. Instead of only checking one sample input, the program should be tested at unit, module, and integration levels.

## Problem Statement

Develop a set of test cases that will completely test the program in Session 7. The test cases should be separately developed for unit testing, module testing, and integration testing.

## Expected Deliverable

Prepare test cases for the C matrix multiplication program.

## Unit Test Cases

| Test Case ID | Input | Expected Result |
| ------------ | ----- | --------------- |
| UT-01 | Access single matrix element using pointer | Correct value returned |
| UT-02 | Multiply one row by one column | Correct scalar result |
| UT-03 | Initialize result matrix | All values start at zero |

## Module Test Cases

| Test Case ID | Scenario | Expected Result |
| ------------ | -------- | --------------- |
| MT-01 | Compatible `2 x 2` matrices | Correct result matrix |
| MT-02 | Compatible rectangular matrices | Correct result matrix |
| MT-03 | Incompatible dimensions | Error message |

## Integration Test Cases

| Test Case ID | Scenario | Expected Result |
| ------------ | -------- | --------------- |
| IT-01 | Read input, multiply, print output | End-to-end success |
| IT-02 | Invalid dimensions from user | Program stops with validation message |

## Test Report Fields

- Test case id
- Test objective
- Input
- Expected output
- Actual output
- Pass/fail status
- Remarks
