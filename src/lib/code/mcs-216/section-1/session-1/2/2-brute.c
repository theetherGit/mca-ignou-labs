#include <stdio.h>

void brute_force_eval(int coeffs[], int n, int x) {
    long long total_sum = 0;
    int mult_count = 0, add_count = 0;
    int degree = n - 1;

    // Iterate through the array of coefficients
    for (int i = 0; i < n; i++) {
        int power = degree - i;
        long long current_pow_val = 1;

        // Inner loop: Calculate x to the power of 'power'
        // This is the source of extra multiplications compared to Horner
        for (int j = 0; j < power; j++) {
            current_pow_val *= x;
            mult_count++;
        }

        // Multiply the resulting power by the coefficient
        if (power > 0) {
            total_sum += (long long)coeffs[i] * current_pow_val;
            mult_count++;
        } else {
            // Constant term (last element)
            total_sum += coeffs[i];
        }

        // Add to the running total (Addition operation)
        if (i > 0) add_count++;
    }

    printf("Brute Force Result: %lld\n", total_sum);
    printf("Multiplications: %d, Additions: %d\n", mult_count, add_count);
}

int main() {
    // Array representing 6x^6 + 5x^5 + 4x^4 - 3x^3 + 2x^2 + 8x - 7
    int coeffs[] = {6, 5, 4, -3, 2, 8, -7};
    brute_force_eval(coeffs, 7, 3);
    return 0;
}
