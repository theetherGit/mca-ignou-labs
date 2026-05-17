---
title: Session 5
description: Divide and Conquer Technique
section: MCS-216 Section 1
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

In Divide and conquer approach, the original problem is divided into two or more sub-problems recursively, till it is small enough to be solved easily. Each sub-problem is some fraction of the original problem. Next, the solutions of the sub-problems are combined together to generate the solution of the original problem.

## Objectives

- Understand how divide and conquer splits a problem into smaller independent subproblems.
- Implement recursive binary search, merge sort, quick sort, and Strassen's matrix multiplication.
- Show dry runs, recursive call trees, loop counts, comparisons, exchanges, and operation counts where the lab manual asks for them.

## Questions Covered

| Question | Requirement | Completion Notes |
| -------- | ----------- | ---------------- |
| Q1 | Recursive binary search for 100 in a sorted array | Add implementation, trace, and recursive call tree. |
| Q2 | Maximum searches among 512 million items using binary search | Add logarithmic calculation. |
| Q3 | Merge sort for `200 150 50 100 75 25 10 5` | Add split/merge steps and recursion tree. |
| Q4 | Quick sort for `12 20 22 16 25 18 8 10 6 15` | Add partition steps and output. |
| Q5 | Quick sort performance for sorted list `6 8 10 12 15 16 18 20 22 25` | Add comparisons, exchanges, and loop iterations. |
| Q6 | Strassen's multiplication for `n x n` matrices where `n` is power of 2 | Add multiple instances and compare multiplications/additions. |

## Question 1

### Problem Statement

Implement a recursive binary search algorithm on your system to search for number `100` in the following array of integers. Show the process step by step and draw recursive calls.

```text
10 35 40 45 50 55 60 65 70 100
```

### Approach

Binary search compares the target with the middle element. If the target is larger, the search continues in the right half; if smaller, it continues in the left half. Because the array is sorted, every recursive call reduces the search range by half.

### Step-by-Step Trace

| Call | Low | High | Mid | A[mid] | Decision |
| ---- | --- | ---- | --- | ------ | -------- |
| 1 | 0 | 9 | 4 | 50 | `100 > 50`, search right half |
| 2 | 5 | 9 | 7 | 65 | `100 > 65`, search right half |
| 3 | 8 | 9 | 8 | 70 | `100 > 70`, search right half |
| 4 | 9 | 9 | 9 | 100 | Found |

### Recursive Call Tree

```text
binarySearch(0, 9)
  -> binarySearch(5, 9)
      -> binarySearch(8, 9)
          -> binarySearch(9, 9)
              -> found at index 9
```

### Complexity

- Time complexity: `O(log n)`
- Space complexity: `O(log n)` due to recursive call stack

### Implementation

### Python
```python title="task-scheduling.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/1/1.py 

```

### C Language
```c title="task-scheduling.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/1/1.c 

```

### Rust
```rust title="task-scheduling.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/1/1.rs

```

## Question 2

### Problem Statement

Suppose we are required to search among 512 million items in a list using binary search. What is the maximum number of searches needed to find a given item or conclude that it is not present?

### Solution

Binary search needs at most `ceil(log2 n)` comparisons.

```js
n = 512,000,000
log2(512,000,000) is slightly less than 29
Maximum searches = 29
```

If the list is interpreted as exactly `512 * 2^20 = 536,870,912`, then:

```text
536,870,912 = 2^29
Maximum searches = 29
```

## Question 3

### Problem Statement

Implement Merge Sort algorithm to sort the following list and show the process step by step. Draw a tree of recursive calls.

```text
200 150 50 100 75 25 10 5
```

### Approach

Merge sort divides the list into two halves until each sublist has one element, then merges the sorted sublists.

### Recursive Split Tree

```text
[200,150,50,100,75,25,10,5]
├─ [200,150,50,100]
│  ├─ [200,150]
│  │  ├─ [200]
│  │  └─ [150]
│  └─ [50,100]
│     ├─ [50]
│     └─ [100]
└─ [75,25,10,5]
   ├─ [75,25]
   │  ├─ [75]
   │  └─ [25]
   └─ [10,5]
      ├─ [10]
      └─ [5]
```

### Implementation

### Python
```python title="task-scheduling.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/3/3.py 

```

### C Language
```c title="task-scheduling.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/3/3.c 

```

### Rust
```rust title="task-scheduling.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/3/3.rs

```

### Final Merge Result

```text
5 10 25 50 75 100 150 200
```

## Question 4

### Problem Statement

Implement Quick Sort's algorithm to sort the following list and show step-by-step processes.

```text
12 20 22 16 25 18 8 10 6 15
```

### Approach

Choose a pivot, partition the list so smaller elements move before the pivot and larger elements move after it, then recursively sort the two partitions.

### Recursive Split Tree

> Here, we are using array index for understanding how the loop will work for quicksort.

```sh
quickSort(0,9) pivot=15
│
├─ quickSort(0,3) pivot=6
│  ├─ quickSort(0,-1) → base case
│  └─ quickSort(1,3) pivot=12
│     ├─ quickSort(1,2) pivot=10
│     │  ├─ quickSort(1,1) → base case
│     │  └─ quickSort(3,2) → base case
│     └─ quickSort(4,3) → base case
│
└─ quickSort(5,9) pivot=25
   ├─ quickSort(5,8) pivot=16
   │  ├─ quickSort(5,4) → base case
   │  └─ quickSort(6,8) pivot=18
   │     ├─ quickSort(6,5) → base case
   │     └─ quickSort(7,8) pivot=20
   │        ├─ quickSort(7,6) → base case
   │        └─ quickSort(8,7) → base case
   └─ quickSort(10,9) → base case
```

### Python
```python title="task-scheduling.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/4/4.py 

```

### C Language
```c title="task-scheduling.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/4/4.c 

```

### Rust
```rust title="task-scheduling.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/4/4.rs

```

### Final Sorted Output

```text
6 8 10 12 15 16 18 20 22 25
```

### Complexity
| Metric | Value | Explanation |
|--------|-------|-------------|
| Best Case Time | O(n log n) | Pivot divides array evenly every time |
| Average Case Time | O(n log n) | Random/pivot selection yields balanced partitions |
| Worst Case Time | O(n²) | Already sorted/reverse sorted + last/first pivot |
| Space Complexity | O(log n) | Recursion stack depth (average) |
| Stable Sort | No | Relative order of equal elements may change |
| In-Place | Yes | Sorts within original array (no extra arrays) |

## Question 5

### Problem Statement

Examine the performance of Quick Sort for the following list in terms of comparisons, exchange operations, and loop iterations.

```text
6 8 10 12 15 16 18 20 22 25
```

### Note

This input is already sorted. If the implementation always chooses the first or last element as pivot, this becomes the worst-case pattern for Quick Sort.

| Metric | Worst-Case Pattern |
| ------ | ------------------ |
| Time complexity | `O(n^2)` |
| Recursion depth | `n` |
| Comparisons | Approximately `n(n-1)/2` |

For `n = 10`, the worst-case comparison count is:

```text
10 * 9 / 2 = 45
```

### Performance Summary

| Metric | Count Formula/Explanation | 
|--------|---------------------------|
| Total Comparisons | 45 | Σ(k) for k=1 to 9 = 9+8+7+...+1 = n(n-1)/2 |
| Meaningful Swaps (i≠j) | 0 | All elements ≤ pivot → no cross-partition swaps |
| Self-Swaps (i=j) | 45 Each comparison where arr[j]≤pivot triggers swap with itself |
| Final Pivot Placements | 9 | One per partition call (all self-swaps) |
| Total Loop Iterations | 45 | Sum of j-loop iterations across all partitions |
| Recursive Calls | 10 | n calls for sorted input (worst-case depth) |
| Recursion Depth | 10 | Linear depth instead of log n |


### Mathematical Verification

```rs
For n = 10, sorted array, Lomuto partition:

Comparisons = (n-1) + (n-2) + ... + 1 + 0
            = Σ(k) for k=0 to n-1
            = n(n-1)/2
            = 10×9/2 = 45 ✓

Swaps (meaningful) = 0  (since array is already partitioned)

Time Complexity = O(n²) ← Worst Case
Space Complexity = O(n) ← Recursion stack depth
```

## Question 6

### Problem Statement

Implement Strassen's multiplication algorithm for two `n x n` matrices, where `n` is a power of 2, on different problem instances and compare all instances in terms of number of multiplications and additions required.

### Strassen’s Algorithm

Traditional matrix multiplication performs `8` multiplications for two `2 x 2` matrices. Strassen's method reduces this to `7` multiplications by using additional additions and subtractions.

```rs
M1 = (A11 + A22) × (B11 + B22)
M2 = (A21 + A22) × B11
M3 = A11 × (B12 - B22)
M4 = A22 × (B21 - B11)
M5 = (A11 + A12) × B22
M6 = (A21 - A11) × (B11 + B12)
M7 = (A12 - A22) × (B21 + B22)
```

#### Comparison

| Method | Multiplications | Additions/Subtractions | Time Complexity |
| ------ | --------------- | ---------------------- | --------------- |
| Classical multiplication | 8 subproblems | Fewer additions | `O(n^3)` |
| Strassen multiplication | 7 subproblems | More additions/subtractions | `O(n^2.807)` |

### Python
```python title="task-scheduling.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/6/6.py 

```

### C Language
```c title="task-scheduling.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/6/6.c 

```

### Rust
```rust title="task-scheduling.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-5/6/6.rs

```


## Viva Questions

- Why must the input array be sorted for binary search?
- Why is merge sort stable?
- What causes Quick Sort's worst case?
- Why does Strassen's method reduce multiplication count?
