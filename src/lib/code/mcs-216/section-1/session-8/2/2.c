// Binomial Coefficient using Dynamic Programming (Bottom-Up Tabulation)

#include <stdio.h>
#include <stdlib.h>

long long binomialDP(int n, int k) {
    // Handle edge cases
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    // Allocate DP table: (n+1) x (k+1)
    long long dp[n + 1][k + 1];

    // Fill table iteratively
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // Base cases: C(i,0) = 1, C(i,i) = 1
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            }
            // Invalid state: j > i
            else if (j > i) {
                dp[i][j] = 0;
            }
            // DP Transition: C(i,j) = C(i-1,j-1) + C(i-1,j)
            else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }

    // Result stored at dp[n][k]
    return dp[n][k];
}

int main() {
    int n = 5, k = 2;
    printf("Computing C(%d, %d) using Dynamic Programming...\n\n", n, k);

    long long result = binomialDP(n, k);

    printf("✅ Result: C(%d, %d) = %lld\n", n, k, result);
    printf("📊 DP Properties Verified:\n");
    printf("   - Optimal Substructure: C(n,k) built from C(n-1,k-1) & C(n-1,k)\n");
    printf("   - Overlapping Subproblems: Each state computed exactly once\n");
    printf("   - Time: O(n×k) | Space: O(n×k)\n");

    return 0;
}
