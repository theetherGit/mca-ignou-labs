---
title: Session 7
description: Minimum Cost Spanning Tree
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is about building a minimum cost spanning tree from a connected, undirected weighted graph. A spanning tree connects all vertices without forming a cycle, and the minimum cost spanning tree chooses the set of edges whose total weight is as small as possible.

## Objectives

- Understand the minimum cost spanning tree problem.
- Implement Prim's algorithm and Kruskal's algorithm.
- Compare both algorithms on different graph instances.

## Concept

A spanning tree connects all vertices of a connected, undirected graph without cycles. A minimum cost spanning tree chooses the set of edges with the lowest possible total weight.

## Prim's Algorithm

Prim's algorithm grows one tree. It starts from any vertex and repeatedly adds the minimum-weight edge that connects a visited vertex to an unvisited vertex.

## Kruskal's Algorithm

Kruskal's algorithm sorts all edges by weight and repeatedly picks the smallest edge that does not form a cycle.

## Question 1

### Problem Statement

Implement Prim's algorithm to find a minimum cost spanning tree in the given graph. Show all the processes.

### Explanation / Approach

Start from any vertex and repeatedly choose the minimum-weight edge that connects the current tree to an unvisited vertex. Keep a table of selected edges and running total cost.

## Question 2

### Problem Statement

Implement Kruskal's algorithm to find a minimum cost spanning tree for the given graph. Show all the processes.

### Explanation / Approach

Sort all edges by weight. Pick the smallest edge if it does not form a cycle. Continue until `V - 1` edges have been selected.

## Question 3

### Problem Statement

Analyze the performance of both algorithms on different problem instances and write a brief report.

### Explanation / Approach

Compare both algorithms using graph density, sorting cost, cycle detection, and ease of implementation.

## Comparison

| Point | Prim | Kruskal |
| ----- | ---- | ------- |
| Strategy | Grows one connected tree | Builds a forest and merges components |
| Edge sorting | Not always required | Required |
| Cycle handling | Avoided by visited set | Requires disjoint set / union-find |
| Good for | Dense graphs | Sparse graphs |

## Submission Checklist

- Include the graph from the lab manual.
- Show selected edges in order.
- Show rejected edges where cycles occur.
- Show final tree and total cost.
