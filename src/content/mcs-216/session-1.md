---
title: Session 1
description: Implementation of Simple Algorithms
section: MCS-216
---

<script>
  import { Callout } from "@ethercorps/kit";
</script>

This session is to implement small problems such as Euclid's Algorithm for GCD, polynomial expression evaluation through Horner's method, algorithms for evaluation of exponentiation and simple sorting algorithms. Selection sort bengs by finding the least element in the arrat which is moved to first position. Then the second least element is searched for and moved to the second position in the array. This process continues until the entire array is sorted.

## Objective

- Implement Euclid's Algorithm to find GCD
- Implement Horner's method for polynomial expression
- Compare performance of Horner's method with brute-force method
- Implement simple sorting algorithms
- Implement multiplication of two matrices

## 1. Euclid's Algorithm

Q1: Implement Euclid's Algorithm to find GCD(15265, 15) and calculate the number of times mod and assigment operations will be required.

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
```python title="Euclid.py" showLineNumbers file=../../lib/code/mcs-216/session-1/1/1.py 

```

### C Implementation
```c title="Euclid.c" showLineNumbers file=../../lib/code/mcs-216/session-1/1/1.c 

```

### Rust Implementation
```rust title="Euclid.rs" showLineNumbers file=../../lib/code/mcs-216/session-1/1/1.rs

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
```python title="horners-method.py" showLineNumbers file=../../lib/code/mcs-216/session-1/2/2.py 

```

### C Implementation
```c title="horners-method.c" showLineNumbers file=../../lib/code/mcs-216/session-1/2/2.c 

```

### Rust Implementation
```rust title="horners-method.rs" showLineNumbers file=../../lib/code/mcs-216/session-1/2/2.rs

```

## 2. (ii) Brute Force
