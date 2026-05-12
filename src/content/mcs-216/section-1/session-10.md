---
title: Session 10
description: Chained Matrix Multiplication
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session explains why the order of multiplying matrices matters. Matrix multiplication is associative, so the final result is the same for any valid parenthesization, but the number of scalar multiplications can change drastically.

## Objectives

- Understand why matrix-chain order affects multiplication cost.
- Find all possible orders for multiplying five matrices.
- Use dynamic programming to find optimal parenthesization.

## Given Dimensions

| Matrix | Dimension |
| ------ | --------- |
| A | `10 x 4` |
| B | `4 x 5` |
| C | `5 x 20` |
| D | `20 x 2` |
| E | `2 x 50` |

Dimension array:

```text
p = [10, 4, 5, 20, 2, 50]
```

## Concept

Matrix multiplication is associative:

```text
(A * B) * C = A * (B * C)
```

The result is the same, but the number of scalar multiplications can be very different.

## Dynamic Programming Recurrence

```text
m[i][j] = min(m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j])
```

where `i <= k < j`.

## Question 1

### Problem Statement

List different orders for evaluating the product of `A, B, C, D, E` matrices.

### Explanation / Approach

Write valid parenthesizations such as `((((A B) C) D) E)`, `((A B) (C (D E)))`, and other legal groupings.

## Question 2

### Problem Statement

Find the optimal order for evaluating `A * B * C * D * E` using the given dimensions.

### Explanation / Approach

Use the dynamic programming cost table to compute the minimum scalar multiplication count.

## Question 3

### Problem Statement

Implement chained matrix multiplication and print the optimal parentheses. Study the performance on different problem instances.

## Submission Checklist

- List multiple valid parenthesizations.
- Build the cost table `m`.
- Build the split table `s`.
- Print the optimal parenthesization.
- Show final minimum multiplication cost.
