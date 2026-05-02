---
title: Session 1
description: Implementation of Simple Algorithms
section: MCS-216
---

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
