#include <stdio.h>

void evaluate_horner(int coeffs[], int n, int x) {
    long long result = coeffs[0];
    int mults = 0, adds = 0, iterations = 0;

    // The loop iterates from 1 to n-1 (total iterations = degree)
    for (int i = 1; i < n; i++) {
        iterations++;

        result = (result * x) + coeffs[i];

        mults++; // One multiplication per step
        adds++;  // One addition per step
    }

    printf("Result: %lld\n", result);
    printf("(a) Multiplications: %d, Additions: %d\n", mults, adds);
    printf("(b) Loop Iterations: %d\n", iterations);
}

int main() {
    int coeffs[] = {6, 5, 4, -3, 2, 8, -7};
    int n = sizeof(coeffs) / sizeof(coeffs[0]);
    evaluate_horner(coeffs, n, 3);
    return 0;
}
