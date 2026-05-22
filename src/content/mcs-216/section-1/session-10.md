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

```math
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

For a fixed sequence of matrices $A × B × C × D × E$, the order of evaluation refers to how you place parentheses. Due to the associative property of matrix multiplication, all valid parenthesizations yield the same final matrix, but they require vastly different amounts of computational work.

For `5` matrices, there are exactly **14 valid parenthesization orders** (given by the 4th Catalan number, $C_4 = 14$). Below is the complete list, along with the **scalar multiplication cost** for each, which highlights why evaluation order matters in practice.

| # |  Evaluation Order (Parenthesization) | Scalar Multiplication Cost |
|---|--------------------------------------|----------------------------|
| 1 | ((((A·B)·C)·D)·E) | "2,600"|
| 2 | (((A·(B·C))·D)·E) | "2,600"|
| 3 | ((A·((B·C)·D))·E) | "1,640"|
| 4 | ((A·(B·(C·D)))·E) | "1,320"|
| 5 | (((A·B)·(C·D))·E) | "1,500"|
| 6 | ((A·B)·((C·D)·E)) | "3,400"|
| 7 | ((A·B)·(C·(D·E))) | "9,700"|
| 8 | ((A·(B·C))·(D·E)) | "13,200"|
| 9 | (A·(((B·C)·D)·E)) | "2,960"|
| 10 | (A·((B·(C·D))·E)) | "2,640"|
| 11 | (A·((B·C)·(D·E))) | "8,400"|
| 12 | (A·(B·((C·D)·E))) | "3,700"|
| 13 | (A·(B·(C·(D·E)))) | "10,000"|
| 14 | (((A·B)·C)·(D·E)) | "13,200"|

- **Cost Calculation**: Multiplying an $m×n$ matrix by an $n×p$ matrix requires $m⋅n⋅p$ scalar multiplications. The total cost is the sum of costs at each multiplication step.
- **Performance Gap**: The worst valid orders (`#8` and `#14`) require **10×** more operations than the optimal order (`#4`).
- **Why `#4` is optimal**: It computes the narrowest intermediate matrices first (`C·D` → `5×2`, then `B·(C·D)` → `4×2`, then `A·...` → `10×2`), keeping the inner dimension small before multiplying by the large `50` column of `E`.

## Question 2

### Problem Statement

Find the optimal order for evaluating `A * B * C * D * E` using the given dimensions.

### Explanation / Approach

The optimal parenthesization is:
$((A · (B · (C · D))) · E)$

Minimum scalar multiplication cost: 1,320

| Step | Operation | Input Dimensions | Output Dimensions | Cost (m×n×p) |
|------|-----------|------------------|-------------------|--------------|
| 1 | C · D | 5×20 × 20×2 | 5×2 | 5×20×2 = 200 |
| 2 | B · (CD) | 4×5 × 5×2 | 4×2 | 4×5×2 = 40 |
| 3 | A · (B(CD)) | 10×4 × 4×2 | 10×2 | 10×4×2 = 80 |
| 4 | (A(B(CD))) · E | 10×2 × 2×50 | 10×50 | 10×2×50 = 1,000 |
| Total |  | |  | 1,320 |

### Why This Order is Optimal

- Matrix chain multiplication is all about controlling the size of intermediate matrices. $C·D$ collapses the large `20` inner dimension early, producing a skinny $5×2$ matrix.
- Subsequent multiplications with `B` and `A` keep the intermediate column dimension at `2`, avoiding expensive operations with the `50` columns of `E` until the very last step.
- Multiplying the final $10×2$ intermediate by `E` ($2×50$) is cheap because the shared dimension is only `2`.

Any other parenthesization forces a larger inner dimension to be multiplied earlier, drastically increasing the total operation count (the worst valid order requires **13,200** operations, exactly `10×` more).


## Question 3

### Problem Statement

Implement chained matrix multiplication and print the optimal parentheses. Study the performance on different problem instances.

### Answer
| Aspect | Complexity / Behavior |
|--------|-----------------------|
| Time Complexity | O(n³) due to 3 nested loops (chain_len, i, k) |
| Space Complexity | O(n²) for DP tables m and s |
| Empirical Scaling | Matches O(n³): doubling n roughly increases runtime by 8× (e.g., 50→100: ~1.3ms → ~9.8ms) |
| Pattern Impact on Cost | Dimension distribution drastically changes optimal cost, but not DP runtime. Increasing/Decreasing chains have highly structured optimal splits, while random chains require full DP evaluation. |
| Practical Limit | Python's pure loops cap out around n ≈ 300-400 (~1-2 sec). For n > 1000, use C/C++ extensions or iterative reconstruction to avoid recursion limits. |

### Implementation

### Python
```python title="floud-warshall-algorithm.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-10/3/3.py 

```

#### Practical Limits
- Overhead of list-of-lists and interpreter slows n > 300. Use numpy arrays or lru_cache for memoization if recursion is preferred.

### C Language
```c title="floud-warshall-algorithm.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-10/3/3.c 

```

#### Practical Limits
- Manual allocation is fastest. For n > 1000, consider 1D flattened arrays m[i*n + j] to improve cache locality.

### Rust
```rust title="floud-warshall-algorithm.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-10/3/3.rs

```

#### Practical Limits
- Zero-cost abstractions make it ~2-5× faster than Python. For extreme n, replace Vec<Vec<>> with vec![0u64; n*n] and compute index i*n + j.

#### Sample Output

```sh
N     | Pattern      | Cost       | Time(ms)
---------------------------------------------
5     | Fixed        | 1320       | 0.012

🔍 Verified: ((M1 · (M2 · (M3 · M4))) · M5) (Cost: 1320)

20    | Uniform      | 241405     | 0.176
50    | Uniform      | 929424     | 2.231
100   | Uniform      | 1535972    | 16.081
```

#### Optimizations

**Knuth Optimization**: If the split table satisfies monotonicity ($s[i][j-1] ≤ s[i][j] ≤ s[i+1][j]$), time can be reduced to O(n²). This holds for many real-world dimension sequences but requires proof per instance.
