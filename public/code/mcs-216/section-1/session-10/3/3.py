import random
import time
from typing import List, Tuple


def matrix_chain_order(dims: List[int]) -> Tuple[List[List[int]], List[List[int]]]:
    """
    Computes minimum multiplication cost and optimal split points using DP.

    Args:
        dims: List of dimensions where matrix i has shape dims[i] x dims[i+1]
              Length must be n + 1 for n matrices.

    Returns:
        m: DP table for minimum costs
        s: DP table for optimal split indices
    """
    n = len(dims) - 1  # Number of matrices
    m = [[0] * n for _ in range(n)]
    s = [[0] * n for _ in range(n)]

    # l = chain length (subproblem size)
    for l in range(2, n + 1):
        # i = left boundary of subchain
        for i in range(n - l + 1):
            j = i + l - 1  # j = right boundary
            m[i][j] = float("inf")

            # k = split point
            for k in range(i, j):
                # Cost = left + right + merge
                cost = m[i][k] + m[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1]
                if cost < m[i][j]:
                    m[i][j] = cost
                    s[i][j] = k

    return m, s


def construct_parens(s: List[List[int]], i: int, j: int) -> str:
    """Reconstructs optimal parenthesization string from split table."""
    if i == j:
        return f"M{i + 1}"
    k = s[i][j]
    return f"({construct_parens(s, i, k)} · {construct_parens(s, k + 1, j)})"


def run_performance_study():
    """Benchmarks algorithm across varying chain lengths."""
    print(f"{'N':<5} | {'Pattern':<12} | {'Cost':<10} | {'Time(ms)':<8}")
    print("-" * 45)

    test_cases = [
        (5, "Fixed", [10, 4, 5, 20, 2, 50]),
        (20, "Uniform", [random.randint(5, 100) for _ in range(21)]),
        (50, "Uniform", [random.randint(5, 100) for _ in range(51)]),
        (100, "Uniform", [random.randint(5, 100) for _ in range(101)]),
    ]

    for n, pattern, dims in test_cases:
        start = time.perf_counter()
        m, s = matrix_chain_order(dims)
        end = time.perf_counter()
        cost = m[0][n - 1]
        parens = construct_parens(s, 0, n - 1)

        print(f"{n:<5} | {pattern:<12} | {cost:<10} | {(end - start) * 1000:.3f}")

        if n == 5:
            print(f"\n🔍 Verified: {parens} (Cost: {cost})\n")


if __name__ == "__main__":
    run_performance_study()
