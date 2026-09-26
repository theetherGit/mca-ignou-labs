# Binomial Coefficient using Dynamic Programming (Bottom-Up Tabulation)


def binomial_dp(n, k, print_table=False):
    """
    Computes C(n,k) using DP tabulation.
    Fills a 2D table iteratively to avoid recomputation.
    """
    # Handle invalid inputs
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1

    # DP table initialization: (n+1) rows, (k+1) columns
    dp = [[0] * (k + 1) for _ in range(n + 1)]

    # Fill table using Pascal's recurrence
    for i in range(n + 1):
        # Base case: C(i, 0) = 1
        dp[i][0] = 1
        for j in range(1, min(i, k) + 1):
            # DP Transition: C(i,j) = C(i-1,j-1) + C(i-1,j)
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

    # Optional: Print DP table for lab verification
    if print_table:
        print(f"\n{'=' * 40}")
        print(f"DP TABLE CONSTRUCTION (n={n}, k={k})")
        print(f"{'=' * 40}")
        print(f"{'i\\j':<4}", end="")
        for j in range(k + 1):
            print(f"j={j:<3}", end="")
        print()
        print("-" * 40)
        for i in range(n + 1):
            print(f"i={i:<2}", end="")
            for j in range(k + 1):
                print(f"{dp[i][j]:<6}", end="")
            print()
        print(f"{'=' * 40}\n")

    return dp[n][k]


def main():
    n, k = 5, 2
    print(f"Computing C({n}, {k}) using Dynamic Programming...\n")
    result = binomial_dp(n, k, print_table=True)
    print(f"Result: C({n}, {k}) = {result}")
    print("DP Advantage: Each subproblem computed exactly once.")
    print("   Time Complexity: O(n×k) | Space Complexity: O(n×k)")


if __name__ == "__main__":
    main()
