---
title: Session 6
description: Single Source Shortest Path Algorithm
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session introduces shortest path problems in weighted graphs. The main idea is to start from one source vertex and compute the minimum distance to every other vertex. This is useful in routing, maps, network design, and any problem where we need the cheapest or shortest route from one point to many destinations.

## Objectives

- Understand single-source shortest path problems.
- Apply Dijkstra's algorithm when all edge weights are non-negative.
- Identify why negative edge weights require a different algorithm such as Bellman-Ford.

## Concept

A single-source shortest path algorithm finds the minimum distance from one starting vertex to every other vertex in a weighted graph.

| Algorithm | Suitable When |
| --------- | ------------- |
| Dijkstra | All edge weights are zero or positive |
| Bellman-Ford | Negative edge weights may exist |

## Standard Dijkstra Approach

1. Set the source distance to `0` and all other distances to infinity.
2. Pick the unvisited vertex with the smallest known distance.
3. Relax all outgoing edges from that vertex.
4. Repeat until all vertices are processed.

## Standard Bellman-Ford Approach

1. Set the source distance to `0` and all other distances to infinity.
2. Relax every edge `V - 1` times.
3. Run one more relaxation pass to detect a negative cycle.

## Question 1

### Problem Statement

Find the shortest path from `A` to the rest of vertices.

### Explanation / Approach

Use Dijkstra's algorithm if all edge weights in the graph are non-negative. Start with distance of `A = 0`, mark all other vertices as infinity, and repeatedly relax the nearest unvisited vertex.

### Completion Note

The graph in the PDF is image-based. Reproduce the graph in the lab record first, then prepare the Dijkstra table for each iteration.

## Question 2

### Problem Statement

Find the shortest path from `B` to the rest of nodes.

### Explanation / Approach

The method is the same as Question 1, but the source vertex changes to `B`. The initial distance table should therefore start with `B = 0` and all other vertices as infinity.

## Question 3

### Problem Statement

Find the shortest path from `A` to the rest of vertices when there are negative weights `-8` between `G` and `F` and `-3` between `F` and `A`.

### Explanation / Approach

Dijkstra's algorithm should not be used when negative edge weights exist. For this case, use Bellman-Ford reasoning because it can handle negative edges and can also detect negative cycles.

## Submission Checklist

- Draw or reproduce the graph from the lab manual.
- Show the distance table after each iteration.
- Show predecessor/parent information for reconstructing paths.
- State clearly whether Dijkstra or Bellman-Ford is used and why.

## Viva Questions

- Why does Dijkstra fail with negative edge weights?
- What is edge relaxation?
- How does Bellman-Ford detect a negative cycle?
