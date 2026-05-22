#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/**
 * Matrix Chain Multiplication - Optimal Parenthesization
 *
 * DP State:
 *   m[i][j] = minimum scalar multiplications to compute product A[i]...A[j]
 *   s[i][j] = index k where the optimal split occurs (A[i]...A[k]) · (A[k+1]...A[j])
 *
 * Complexity: O(n³) time, O(n²) space
 * Note: We use long long for costs to prevent integer overflow on larger chains.
 */
void matrix_chain_order(const int* dims, int n, long long** m, int** s) {
    // Base case: multiplying a single matrix costs 0
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }

    // l = chain length (number of matrices in current subproblem)
    for (int l = 2; l <= n; l++) {
        // i = starting matrix index
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1; // j = ending matrix index
            m[i][j] = LLONG_MAX;

            // Try every possible split point k between i and j
            for (int k = i; k < j; k++) {
                // Cost = left subchain + right subchain + final merge
                // dims[i] x dims[k+1]  *  dims[k+1] x dims[j+1]  →  dims[i] x dims[j+1]
                long long cost = m[i][k] + m[k+1][j] + (long long)dims[i] * dims[k+1] * dims[j+1];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

/**
 * Recursively reconstruct optimal parentheses using the split table `s`.
 * Uses 1-based naming (M1, M2, ...) for readability.
 */
void print_optimal_parens(const int* const* s, int i, int j) {
    if (i == j) {
        printf("M%d", i + 1);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        printf(" · ");
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

/**
 * Safe 2D array deallocation
 */
void free_dp_tables(long long** m, int** s, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
}

int main() {
    // Example: A(10x4), B(4x5), C(5x20), D(20x2), E(2x50)
    int dims[] = {10, 4, 5, 20, 2, 50};
    int n = sizeof(dims)/sizeof(dims[0]) - 1; // n = 5 matrices

    // Allocate DP tables on the heap
    long long** m = malloc(n * sizeof(long long*));
    int** s = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        m[i] = malloc(n * sizeof(long long));
        s[i] = malloc(n * sizeof(int));
    }

    // Run DP
    matrix_chain_order(dims, n, m, s);

    // Output results
    printf("Optimal Parenthesization: ");
    print_optimal_parens((const int* const*)s, 0, n - 1);
    printf("\nMinimum Scalar Multiplications: %lld\n", m[0][n-1]);

    // Cleanup
    free_dp_tables(m, s, n);
    return 0;
}
