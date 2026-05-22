#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define MAX_N 50  // Safe upper bound for small instances

typedef struct {
    double cost;
    long ops;
    double time_us;
} Result;

Result optimal_bst(double p[], double q[], int n, const char* name) {
    // Allocate 2D tables on heap to avoid stack overflow for larger n
    double (*e)[MAX_N+2] = calloc(n + 2, sizeof(double[MAX_N+2]));
    double (*w)[MAX_N+2] = calloc(n + 2, sizeof(double[MAX_N+2]));
    int    (*root)[MAX_N+1] = calloc(n + 1, sizeof(int[MAX_N+1]));

    long ops = 0;

    // Base case initialization
    for (int i = 1; i <= n + 1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // DP recurrence: O(n^3) time, O(n^2) space
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                ops++;  // Count comparison operation
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    printf("[%s] Optimal Cost: %.4f | Time: %.2f µs | Ops: %ld\n",
           name, e[1][n], elapsed_us, ops);

    Result res = {e[1][n], ops, elapsed_us};
    free(e); free(w); free(root);
    return res;
}

int main() {
    printf("🔬 OBST Performance Study (C)\n\n");

    // Problem 1 (n=7)
    double p1[] = {0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    double q1[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    optimal_bst(p1, q1, 7, "Problem 1 (n=7)");

    // Problem 2 (n=5)
    double p2[] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q2[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    optimal_bst(p2, q2, 5, "Problem 2 (n=5)");

    return 0;
}
