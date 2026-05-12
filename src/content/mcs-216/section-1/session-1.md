---
title: Session 1
description: Implementation of Simple Algorithms
section: MCS-216 Section 1
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

This session is to implement small problems such as Euclid's Algorithm for GCD, polynomial expression evaluation through Horner's method, algorithms for evaluation of exponentiation and simple sorting algorithms. Selection sort begins by finding the least element in the array, which is moved to the first position. Then the second least element is searched for and moved to the second position in the array. This process continues until the entire array is sorted.

## Objective

- Implement Euclid's Algorithm to find GCD
- Implement Horner's method for polynomial expression
- Compare performance of Horner's method with brute-force method
- Implement simple sorting algorithms
- Implement multiplication of two matrices

## 1. Euclid's Algorithm

Q1: Implement Euclid's Algorithm to find GCD(15265, 15) and calculate the number of times mod and assignment operations will be required.

### What is Euclid's algorithm?

Euclid's algorithm is an efficient method for computing the Greatest Common Divisor (GCD) of two integers—the largest number that divides both of them without leaving a remainder.

It is based on the principle that the GCD of two numbers also divides their difference. Specifically, the GCD of `a` and `b` is the same as the GCD of `b` and `a mod(b)`.

### Algorithm

The algorithm follows a simple recursive process:

 - Given two numbers `a` and `b` (where `a > b`).
 - Divide `a` by `b` and find the remainder `r`.
 - Replace `a` with `b` and `b` with `r`.
 - Repeat the process until the remainder is 0.
 - The last non-zero remainder is the GCD.
 
 ### Example

 GCD of 48 and 18
 - 48/18 = 2 with a remainder of 12
 - 18/12 = 1 with a remainder of 6
 - 12/6 = 2 with a remainder of 0

The GCD is 6.

### Python Implementation
```python title="Euclid.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/1/1.py 

```

### C Implementation
```c title="Euclid.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/1/1.c 

```

### Rust Implementation
```rust title="Euclid.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/1/1.rs

```

## 2. (i) Horner's Rule

Q2 (i): Implement Horner's rule for evaluating polynomials P(x) = 6x^(6)+5x^(5)+4x^(4)-3x^(3)+2x^(2)+8x^(1)-7 at x=3. Calculate how may times
- (a) Multiplications and addition operations will take
- (b) How many times the loop will iterate

### What is Horner's Rule?

Horner’s Rule is an efficient algorithm for evaluating polynomials that reduces the number of multiplications required by nesting the terms. Instead of calculating each power of `x` individually, it rewrites the polynomial in a recursive format.


### Mathematical Logic

<Callout type="note" title="Note">
	<!-- Space here-->
	To learn more about horner's rule, watch: <br />
	- <a class="underline" href="https://www.youtube.com/watch?v=zEvfkSuPqWk" target="_blank">Horner's Method by Oscar Veliz</a> <br />
	- <a class="underline" href="https://github.com/osveliz/numerical-veliz" target="_blank">Source code</a>
	<!-- Space here-->
</Callout>

- For a polynomial `P(x) = a_n x^n + a_(n-1) x^(n-1) + ... + a_1 x + a_0`, Horner's Rule transforms it into:

```latex
P(x) = (...((a_n x + a_(n-1))x + a_(n-2))x + ... + a_1)x + a_0
```

- Given our polynomial:
```latex
P(x) = 6x^6 + 5x^5 + 4x^4 - 3x^3 + 2x^2 + 8x - 7
```

- The nested form at $x=3$ is:
```latex
P(3) = (((((6 * 3 + 5) * 3 + 4) * 3 - 3) * 3 + 2) * 3 + 8) * 3 - 7
```

### Algorithm

- Initialize result as the coefficient of the highest degree term `a_n`
- For each subsequent coefficient from `a_(n-1)` down to `a_0`:
  - Multiply the current `result` by `x`.
  - Add the next coefficient to the `result`.
- The final `result` is the value of the polynomial.

### Example

| Step | Operation | Current Result |
-------- | --------- | ------- |
| Start | Initial value (a​n) | 6 |
| 1 | (6×2)+2 | 14 |
| 2 | (14×2)+5 | 33 |
| 3 | (33×2)+(−7) | 59 |

### Python Implementation
```python title="horners-method.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-horner.py 

```

### C Implementation
```c title="horners-method.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-horner.c 

```

### Rust Implementation
```rust title="horners-method.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-horner.rs

```

## 2. (ii) Brute Force Method

Q2 (ii): Apply a brute force method to implement the above polynomial expression from 2(i) and compare it with Horner's method in terms of number of multiplication operations.

### What is Brute Force Method?

In Brute Force, for each term `a_k * x^k`, you calculate `x` multiplied by itself `k` times, then multiply by the coefficient `a_k`.

### Algorithm

- Initialize `total_sum = 0`.
- For each term `a_k x^k`:
  - Calculate `power_val = x^k` (using a loop or power function).
  - Calculate `term_val = a_k * power_val`.
  - Add `term_val` to `total_sum`.
- Return `total_sum`.

### Example

**Polynomial**: `3x^2 + 2x + 5` at `x=4`

- Term 1 `(3x^2): 4 * 4 = 16`; `16 * 3 = 48` (2 mults)
- Term 2 `(2x^1): 2 * 4 = 8` (1 mult)
- Term 3 `(5)`: 5 (0 mults)
- Sum: `48 + 8 + 5 = 61`.

Total Multiplications: `2 + 1 = 3`. (Horner would only use 2).

### Python Implementation
```python title="horners-method.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-brute.py 

```

### C Implementation
```c title="horners-method.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-brute.c 

```

### Rust Implementation
```rust title="horners-method.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/2/2-brute.rs

```

### Complexity Comparison

| Metric | Horner's Method | Brute Force Method |
| ------ | --------------- | ------------------ |
| Multiplications | n (6) | 2n(n+1)​+n (21) |
| Additions | n (6) | n (6) |
| Time Complexity | O(n) | O(n2) |

**Brute Force** method is significantly more expensive because the inner loop recalculates powers from scratch for every single term, whereas **Horner's Rule** reuses the result of the previous multiplication.

### Comparison (Honer vs Brute)

**Brute Force Multiplications**: 
- To calculate `x^6`, you do 5 multiplications. 
- Then 1 more to multiply by the coefficient 6. 
- Totaling `k` multiplications for a term of degree `k`.
- For degree 6: `6+5+4+3+2+1 = 21` multiplications.

**Horner's Method Multiplications**: 
- As shown previously, this only requires 6 multiplications.


## 3. Matrix Multiplication

Q3: Implement matrix multiplication of two matrices A[4,4] & B[4,4] and calculate: <br />
(i) how many times the inner-most and outer-most loops will run <br />
(ii) total number of multiplications and additions in computing the multiplication

### Explanation
Matrix multiplication computes a resultant matrix C from two input matrices A and B such that:
```latex
C[i][j] = Σ (A[i][k] × B[k][j])   for k = 0 to n-1
```

For `n×n` matrices, this requires **three nested loops**:

- **Outer loop (`i`)**: Iterates over rows of `A`
- **Middle loop (`j`)**: Iterates over columns of `B`
- **Inner-most loop (`k`)**: Computes the dot product between the `i`-th row of `A` and `j`-th column of `B`

Each inner iteration performs **one multiplication** `(A[i][k] * B[k][j])` and one addition (`+=` to accumulate into `C[i][j]`). The total **time complexity** is **O(n³)** and **space complexity** is **O(n²)** for the result matrix.

### Algorithm & Pseudocode

```py showLineNumbers
INPUT: A[4][4], B[4][4]
OUTPUT: C[4][4]

Initialize C[4][4] with zeros
For i from 0 to 3:
    For j from 0 to 3:
        For k from 0 to 3:
            C[i][j] += A[i][k] * B[k][j]
Return C
```

### Answer

#### (i) Loop Execution Count
| Loop Position | Iteration Count | Reason |
| ------------- | --------------- | ------ |
| Outer-most (`i`) | `4` times | Runs once per row of `A` | 
| Inner-most (`k`) | `64` times |Executes for every `(i, j)` pair: `4 × 4 × 4 = 64` |

#### (ii) Total Arithmetic Operations

| Operation | Count | Explanation |
| --------- | ----- | ----------- |
| Multiplications | `64` | `1` per inner iteration → `n³ = 4³ = 64` |
| Additions | `64` | Each `C[i][j] += ...` performs 1 accumulation addition per inner step |


### Execution Trace (Conceptual)

For `n=4`:

- `i=0`: `j` runs 0..3 → `k` runs 4 times each → 16 inner executions
- `i=1`: same → 16 inner executions
- `i=2`: same → 16 inner executions
- `i=3`: same → 16 inner executions
- **Total inner executions** = `16 × 4 = 64`
- Each inner step: `1 mul + 1 add` → `64 mul + 64 add`


### Python Implementation
```python title="matrix-multiplation.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/3/3.py 

```

### C Implementation
```c title="matrix-multiplation.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/3/3.c 

```

### Rust Implementation
```rust title="matrix-multiplation.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/3/3.rs

```

## 4. Binary Exponentiation

Q4: Implement left to right and right to left binary exponentiation methods for the following problems: <br />
(i) 4^512 <br />(ii) 3^31 <br />
Calculate the followings for problems (i) and(ii) <br />
- How many times the loops will be executed? 
- How many times the multiplication and additions operations will be executed?

### Explanation

Binary exponentiation, also known as exponentiation by squaring, is an efficient algorithm for computing large powers of a number. It reduces the number of multiplications needed by using the properties of exponents.

The algorithm can be implemented in two ways: left-to-right and right-to-left.
- **Left-to-Right**: Start from the highest bit of the exponent and work downwards.
- **Right-to-Left**: Start from the lowest bit of the exponent and work upwards.
- Both methods have a time complexity of O(log n) and require O(1) space.
- The number of multiplications depends on the number of bits in the exponent and the number of 1s in the binary representation of the exponent.
- For example, for `4^512`, the exponent `512` in binary is `1000000000`, which has 1 bit set to 1. For `3^31`, the exponent `31` in binary is `11111`, which has 5 bits set to 1.

### Python Implementation
```python title="binary-exponentiation.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/4/4.py 

```
### C Implementation
```c title="binary-exponentiation.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/4/4.c 

```
### Rust Implementation
```rust title="binary-exponentiation.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/4/4.rs
```

## 5. Bubble Sort

Q5: Implement Bubble Sort algorithm for the following list of numbers: <br />
<strong>55 25 15 40 60 35 17 65 75 10</strong> <br />
Calculate <br />
(i) a number of exchange operations <br />
(ii) a number oftimes comparison operations <br /> 
(iii) a number of times the inner and outer loops will iterate?

### Explanation
Bubble Sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order. The process is repeated until the list is sorted. The algorithm gets its name because smaller elements "bubble" to the top of the list.
- The outer loop runs `n-1` times, where `n` is the number of elements in the list.
- The inner loop runs `n-i-1` times for each iteration of the outer loop, where `i` is the current iteration of the outer loop.
- The number of comparisons is the sum of the inner loop iterations, which is `n(n-1)/2` in the worst case.
- The number of exchanges depends on the initial order of the elements. In the worst case (when the list is in reverse order), the number of exchanges is also `n(n-1)/2`.

### Python Implementation
```python title="bubble-sort.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/5/5.py 

```

### C Implementation
```c title="bubble-sort.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/5/5.c
```

### Rust Implementation
```rust title="bubble-sort.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/5/5.rs

```

## 6. Selection Sort

Q6: Implement Selection Sort algorithm on a similar set of data as in Q5 and <br />
(i)perform similar operations on the above example <br />
(ii) make a comparison between the two algorithms in terms of best case and worst case complexities.

### Explanation
Selection Sort is a simple comparison-based sorting algorithm. It divides the input list into two parts: the sorted part at the left end and the unsorted part at the right end. Initially, the sorted part is empty and the unsorted part is the entire list. The algorithm repeatedly selects the smallest (or largest, depending on sorting order) element from the unsorted part and moves it to the end of the sorted part.
- The outer loop runs `n-1` times, where `n` is the number of elements in the list.
- The inner loop runs `n-i-1` times for each iteration of the outer loop, where `i` is the current iteration of the outer loop.
- The number of comparisons is the same as Bubble Sort, which is `n(n-1)/2` in the worst case.
- The number of exchanges is `n-1` in the worst case, as each element is moved at most once.

### Python Implementation
```python title="selection-sort.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/6/6.py 

```

### C Implementation
```c title="selection-sort.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/6/6.c

```

### Rust Implementation
```rust title="selection-sort.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-1/6/6.rs

```

### Comparison of Bubble Sort and Selection Sort
| Metric | Bubble Sort | Selection Sort |
| ------ | ----------- | -------------- |
| Best Case Time Complexity | O(n) | O(n^2) |
| Worst Case Time Complexity | O(n^2) | O(n^2) |
| Number of Comparisons | O(n^2) | O(n^2) |
| Number of Exchanges | O(n^2) | O(n) |

- Bubble Sort can be optimized to stop if no swaps are made, which gives it a best case time complexity of O(n) when the list is already sorted. Selection Sort, on the other hand, always requires O(n^2) comparisons regardless of the initial order of the elements. However, Selection Sort performs fewer exchanges than Bubble Sort, making it more efficient in terms of the number of swaps, especially for large lists.
- In summary, Bubble Sort is generally more efficient for small or nearly sorted lists, while Selection Sort can be more efficient for larger lists where the cost of swapping is high.
- For the given list of numbers, both algorithms will perform the same number of comparisons, but Bubble Sort may perform more exchanges than Selection Sort depending on the initial order of the elements.
