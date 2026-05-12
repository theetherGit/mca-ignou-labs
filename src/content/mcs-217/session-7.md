---
title: Session 7
description: Matrix Multiplication in C Using Pointers
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session moves from documentation to implementation. The task is to write a C program for matrix multiplication using pointers, which helps practice memory access and pointer notation in C.

## Problem Statement

Write a program in C language for multiplication of two matrices using pointers.

## Expected Deliverable

Submit a C program that accepts two compatible matrices, multiplies them using pointer-based access, and prints the result matrix.

## Algorithm

1. Read matrix dimensions.
2. Check whether columns of first matrix equal rows of second matrix.
3. Read matrix elements.
4. Use three nested loops to compute multiplication.
5. Access elements using pointer arithmetic.
6. Print the output matrix.

## Pointer Access Pattern

```c
*(*(matrix + i) + j)
```

## Complexity

| Metric | Value |
| ------ | ----- |
| Time complexity | `O(r1 * c2 * c1)` |
| Space complexity | `O(r1 * c2)` for result matrix |

## Submission Checklist

- Include source code.
- Include sample input and output.
- Explain pointer notation.
- Handle incompatible matrix dimensions.
