#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define N 7

void construct_optimal_bst(double p[], double q[], double e[][N+2], int root[][N+1]) {
    double w[N+2][N+2];

    // Initialize base cases
    for (int i = 1; i <= N + 1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    // DP over subtree length l
    for (int l = 1; l <= N; l++) {
        for (int i = 1; i <= N - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void print_tree(int root[][N+1], int i, int j, int depth, char side) {
    if (i > j) {
        printf("%*c%c -> d%d\n", depth * 4, ' ', side, i-1);
        return;
    }
    int r = root[i][j];
    printf("%*c%c -> k%d\n", depth * 4, ' ', side, r);
    print_tree(root, i, r-1, depth+1, 'L');
    print_tree(root, r+1, j, depth+1, 'R');
}

int main() {
    double p[] = {0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    double q[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    double e[N+2][N+2];
    int root[N+1][N+1];

    construct_optimal_bst(p, q, e, root);

    printf("Optimal Expected Cost: %.4f\n", e[1][N]);
    printf("\nTree Structure:\n");
    print_tree(root, 1, N, 0, 'R');

    return 0;
}
