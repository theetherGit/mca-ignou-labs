---
title: Session 9
description: Floyd and Warshall's Algorithm for All Pair Shortest Path Algorithms
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is about finding shortest paths between every pair of vertices in a graph. Unlike Dijkstra's algorithm, which starts from one source, Floyd-Warshall works with a distance matrix and gradually improves every source-destination pair.

## Objectives

- Understand all-pairs shortest path computation.
- Apply Floyd-Warshall algorithm using distance matrices.
- Implement the algorithm for different graphs.

## Concept

Floyd-Warshall updates a distance matrix by allowing each vertex to become an intermediate vertex.

```text
D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j])
```

## Algorithm

```text
for k from 1 to n:
    for i from 1 to n:
        for j from 1 to n:
            D[i][j] = min(D[i][j], D[i][k] + D[k][j])
```

## Complexity

| Metric | Value |
| ------ | ----- |
| Time complexity | `O(n^3)` |
| Space complexity | `O(n^2)` |

## Question 1

### Problem Statement

Apply Floyd-Warshall's algorithm for the given graph. Show the matrix `D5` and find the shortest path.

### Explanation / Approach

Start with the initial distance matrix and update it once for each intermediate vertex. The final required matrix is `D5`.

## Question 2

### Problem Statement

Apply Floyd-Warshall's algorithm to compute the shortest path for the second graph. Compute the `D5` matrix.

### Explanation / Approach

Use the same matrix update rule and show every important intermediate matrix.

## Question 3

### Problem Statement

Implement the all-pair shortest path algorithm using different graphs.

## Submission Checklist

- Show initial adjacency/distance matrix.
- Show intermediate matrices `D1` through required final matrix.
- Mark infinity values clearly.
- Include final shortest paths.
