---
title: Session 11
description: Optimal Binary Search Tree
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session covers the optimal binary search tree problem. A normal binary search tree only depends on key order, but an optimal BST also considers how frequently each key is searched so that the expected search cost is minimized.

## Objectives

- Understand optimal binary search tree construction.
- Determine the minimum expected search cost.
- Show the final tree structure for the given key probabilities/frequencies.

## Concept

An optimal binary search tree minimizes the expected search cost when keys have different search probabilities. Frequently searched keys should appear closer to the root when that reduces total weighted path cost.

## Dynamic Programming Idea

For each key range, try each key as root and choose the root that gives minimum expected cost.

```text
cost[i][j] = min(cost[i][r-1] + cost[r+1][j] + sum(freq[i..j]))
```

where `r` ranges from `i` to `j`.

## Question 1

### Problem Statement

Determine the cost and structure of an optimal binary search tree for a set of `n = 7` keys with the given properties. Show the step-by-step process.

### Explanation / Approach

Use the frequency/probability table from the lab manual and construct the weight, cost, and root tables.

## Question 2

### Problem Statement

Determine the cost and structure of the optimal binary search tree for the second given instance.

## Question 3

### Problem Statement

Implement the optimal binary search tree algorithm and study its performance on different problem instances.

## Submission Checklist

- Copy the key/frequency table from the lab manual.
- Show weight table, cost table, and root table.
- Draw the final OBST.
- Explain why the chosen root gives minimum cost.
