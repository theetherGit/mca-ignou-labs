---
title: Session 8
description: Implementation of Binomial Coefficient Algorithm
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session compares two ways of computing binomial coefficients. The divide-and-conquer solution follows the mathematical recurrence directly, while the dynamic programming solution stores repeated subproblem results and is much faster for larger inputs.

## Objectives

- Implement binomial coefficient using divide and conquer.
- Implement binomial coefficient using dynamic programming.
- Compare both approaches for small and large values of `n` and `k`.

## Concept

The binomial coefficient `C(n, k)` counts the number of ways to choose `k` items from `n` items.

It also follows Pascal's recurrence:

```text
C(n, k) = C(n-1, k-1) + C(n-1, k)
C(n, 0) = C(n, n) = 1
```

## Divide and Conquer Approach

The recursive approach directly follows Pascal's recurrence. It is simple, but it recomputes many subproblems.

| Metric | Value |
| ------ | ----- |
| Time complexity | Exponential without memoization |
| Space complexity | `O(n)` recursion depth |

## Dynamic Programming Approach

The DP approach stores intermediate values in a table and avoids repeated computation.

| Metric | Value |
| ------ | ----- |
| Time complexity | `O(nk)` |
| Space complexity | `O(nk)` or `O(k)` when optimized |

## Question 1

### Problem Statement

Implement a binomial coefficient problem using divide and conquer technique.

### Explanation

The binomial coefficient, denoted as $\binom{n}{k}$ or $C(n, k)$, represents the number of ways to choose $k$ elements from a set of $n$ elements without regard to order.To implement this using the Divide and Conquer technique, we break the larger problem into smaller subproblems using Pascal's Identity.

To implement this using the Divide and Conquer technique, we break the larger problem into smaller subproblems using Pascal's Identity.

### Mathematical Formulation

Pascal's Identity states that:

```math
\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}
```

#### Base Cases:
- If $k = 0$, there is exactly $1$ way to choose $0$ items: $\binom{n}{0} = 1$
- If $k = n$, there is exactly $1$ way to choose all $n$ items: $\binom{n}{n} = 1$
- If $k > n$, it's impossible to choose more items than available: $\binom{n}{k} = 0$

## Question 2

### Problem Statement

Implement a binomial coefficient problem using dynamic programming technique.

### Explanation / Approach

Build a table where each cell stores one binomial coefficient. This avoids recalculating the same values again and again.

## Question 3

### Problem Statement

Study the performance of both implementations using five problem instances in terms of efficiency for large and small values of `n` and `k`.

## Suggested Problem Instances

| Instance | n | k |
| -------- | - | - |
| 1 | 5 | 2 |
| 2 | 10 | 5 |
| 3 | 20 | 10 |
| 4 | 30 | 15 |
| 5 | 50 | 25 |

## Submission Checklist

- Include both implementations.
- Show output for five instances.
- Compare runtime growth.
- Explain why DP is more efficient.
