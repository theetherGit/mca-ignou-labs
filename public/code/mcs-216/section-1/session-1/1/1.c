#include <stdio.h>
#include <stdlib.h>

/**
 * Calculates GCD and updates operation counters via pointers.
 */
long long gcd_metrics(long long a, long long b, int *mods, int *assigns) {
    *mods = 0;
    *assigns = 0;

    a = llabs(a);
    b = llabs(b);
    *assigns += 2;

    while (b != 0) {
        long long remainder = a % b;
        (*mods)++;

        a = b;
        b = remainder;
        *assigns += 2;
    }

    return a;
}

int main() {
    int mod_count, assign_count;
    long long a = 15265, b = 15;

    long long result = gcd_metrics(a, b, &mod_count, &assign_count);

    printf("GCD(%lld, %lld) = %lld\n", a, b, result);
    printf("Total Modulo Operations: %d\n", mod_count);
    printf("Total Assignment Operations: %d\n", assign_count);

    return 0;
}
