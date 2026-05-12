---
title: Session 9
description: Matrix Transpose Web Page
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session applies web programming to a matrix problem. The page should accept matrix dimensions, dynamically create input boxes, read the matrix values, and display the transpose.

## Problem Statement

Design a web page that accepts a matrix as input and computes its transpose.

## Expected Deliverable

Create an HTML, CSS, and JavaScript page with two text boxes for rows and columns and a submit button labelled `Input Elements`. After entering dimensions, generate input boxes for matrix elements and a second button labelled `Compute Transpose`.

## UI Flow

1. User enters number of rows.
2. User enters number of columns.
3. User clicks `Input Elements`.
4. Page generates matrix input boxes.
5. User enters matrix values.
6. User clicks `Compute Transpose`.
7. Page displays transposed matrix.

## Transpose Logic

For matrix `A` with `r` rows and `c` columns:

```text
transpose[j][i] = A[i][j]
```

The transpose has `c` rows and `r` columns.

## Submission Checklist

- Include HTML structure.
- Include JavaScript for dynamic input generation.
- Include validation for positive dimensions.
- Include sample input and output.
