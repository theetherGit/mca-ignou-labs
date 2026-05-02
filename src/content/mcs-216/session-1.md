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
```python
def get_gcd(a, b):
    """
    Computes the GCD using the iterative Euclidean Algorithm.
    Works for any integer size in Python 3.
    """
    # Ensure we work with absolute values to handle negative inputs
    a, b = abs(a), abs(b)
    
    # Loop until the remainder (b) becomes 0
    while b != 0:
        # a % b calculates the remainder of a divided by b
        # We update a to be the previous b, and b to be the remainder
        a, b = b, a % b
        
    # When b is 0, a contains the GCD
    return a

# Example usage:
num1, num2 = 270, 192
print(f"GCD of {num1} and {num2} is: {get_gcd(num1, num2)}")
```

### C Implementation
```c
#include <stdio.h>
#include <stdlib.h>

/**
 * Calculates GCD using the Euclidean Algorithm.
 * Returns the result as a long long to prevent overflow for large inputs.
 */
long long get_gcd(long long a, long long b) {
    // Use absolute values to ensure the result is positive
    a = llabs(a);
    b = llabs(b);
    
    while (b != 0) {
        // Temp variable stores the remainder before we overwrite 'b'
        long long remainder = a % b;
        
        // Update 'a' with the current 'b'
        a = b;
        
        // Update 'b' with the calculated remainder
        b = remainder;
    }
    
    // When the loop finishes, 'a' holds the GCD
    return a;
}

int main() {
    long long num1 = 270, num2 = 192;
    printf("GCD of %lld and %lld is %lld\n", num1, num2, get_gcd(num1, num2));
    return 0;
}
```

### Rust Implementation
```rust
fn get_gcd(mut a: u64, mut b: u64) -> u64 {
    // We use u64 (64-bit unsigned integer) for large positive numbers
    // The algorithm continues as long as b is not zero
    while b != 0 {
        // Calculate the remainder
        let remainder = a % b;
        
        // Update 'a' to 'b' and 'b' to the remainder for the next iteration
        a = b;
        b = remainder;
    }
    
    // Once b hits zero, a is the greatest common divisor
    a
}

fn main() {
    let x = 270;
    let y = 192;
    println!("The GCD of {} and {} is {}", x, y, get_gcd(x, y));
}
```
