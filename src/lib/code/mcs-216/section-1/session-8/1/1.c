// Binomial Coefficient using Divide & Conquer

#include <stdio.h>

// Global counter to track recursive calls for lab analysis
static int call_count = 0;

/**
 * Computes C(n,k) using Pascal's Identity:
 * C(n,k) = C(n-1, k-1) + C(n-1, k)
 */
long long binomialCoeff(int n, int k) {
    call_count++;

    // Base Cases: Trivial subproblems
    if (k == 0 || k == n) return 1;
    if (k > n || k < 0) return 0;

    // Divide & Conquer Step
    // Divide: Create two subproblems
    // Conquer: Recursively solve them
    // Combine: Sum the results
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

int main() {
    int n = 5, k = 2;

    printf("Computing C(%d, %d) using Divide & Conquer...\n\n", n, k);

    long long result = binomialCoeff(n, k);

    printf("✅ Result: C(%d, %d) = %lld\n", n, k, result);
    printf(" Total Recursive Calls: %d\n", call_count);
    printf("📈 Complexity Note: Overlapping subproblems cause O(2^n) calls.\n");
    printf("   Use memoization (DP) to reduce to O(nk) time.\n");

    return 0;
}
