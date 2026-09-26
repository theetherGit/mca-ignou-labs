#include <stdio.h>
#include <float.h>

#define N 5

void construct_optimal_bst(double p[], double q[], double e[][N+2], int root[][N+1]) {
    double w[N+2][N+2];
    // Base cases
    for (int i = 1; i <= N + 1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    // DP
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

void print_tree(int root[][N+1], double p[], double q[], int i, int j, int depth, char side) {
    if (i > j) {
        printf("%*c%c -> d%d (q=%.2f)\n", depth * 4, ' ', side, i-1, q[i-1]);
        return;
    }
    int r = root[i][j];
    printf("%*c%c -> k%d (p=%.2f)\n", depth * 4, ' ', side, r, p[r]);
    print_tree(root, p, q, i, r-1, depth+1, 'L');
    print_tree(root, p, q, r+1, j, depth+1, 'R');
}

int main() {
    double p[] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    double e[N+2][N+2];
    int root[N+1][N+1];

    construct_optimal_bst(p, q, e, root);
    printf("Optimal Expected Cost: %.4f\n\n", e[1][N]);
    printf("Tree Structure:\n");
    print_tree(root, p, q, 1, N, 0, 'R');
    return 0;
}
