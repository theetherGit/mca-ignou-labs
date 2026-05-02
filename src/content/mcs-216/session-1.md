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

## Euclid's Algorithm

Q1: Implement Euclid's Algorithm to find GCD(15265, 15) and calculate the number of times mod and assigment operations will be required.

### Python Implementation
```python
def gcd(a, b):
    while b:    
        a, b = b, a % b
    return a
```

### C Implementation
```c
#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### Rust Implementation
```rust
gcd(mut a: i32, mut b: i32) -> i32 {
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    return a
}
```
