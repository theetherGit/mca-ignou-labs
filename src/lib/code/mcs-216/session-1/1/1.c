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
