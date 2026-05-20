// Binomial Coefficient using Dynamic Programming (Bottom-Up Tabulation)

fn binomial_dp(n: usize, k: usize) -> i64 {
    if k > n {
        return 0;
    }

    // DP table: (n+1) rows, (k+1) columns
    let mut dp = vec![vec![0i64; k + 1]; n + 1];

    // Fill table using iterative DP transition
    for i in 0..=n {
        for j in 0..=k.min(i) {
            if j == 0 || j == i {
                dp[i][j] = 1; // Base cases
            } else {
                // DP Transition: C(i,j) = C(i-1,j-1) + C(i-1,j)
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }

    dp[n][k]
}

fn main() {
    let (n, k) = (5, 2);
    println!("Computing C({}, {}) using Dynamic Programming...\n", n, k);

    let result = binomial_dp(n, k);

    println!("✅ Result: C({}, {}) = {}", n, k, result);
    println!(" DP Advantage: Eliminates exponential recomputation.");
    println!("   Each of the (n+1)*(k+1) states computed exactly once.");
    println!("   Time: O(n×k) | Space: O(n×k)");
}
