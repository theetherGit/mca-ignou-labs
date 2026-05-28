import time
import sys

def optimal_bst(p, q, name="Instance"):
    """
    Dynamic Programming solution for Optimal Binary Search Tree.
    Tracks execution time and inner-loop operation count.
    """
    n = len(p) - 1  # p is 1-indexed
    ops = 0  # Counts primitive comparisons

    # Allocate DP tables: e[cost], w[weight], root[index]
    e = [[0.0] * (n + 2) for _ in range(n + 2)]
    w = [[0.0] * (n + 2) for _ in range(n + 2)]
    root = [[0] * (n + 1) for _ in range(n + 1)]

    # Base case: subtrees containing only dummy keys
    for i in range(1, n + 2):
        e[i][i - 1] = q[i - 1]
        w[i][i - 1] = q[i - 1]

    # High-resolution timing start
    start = time.perf_counter()

    # DP over chain length l = 1 to n
    for l in range(1, n + 1):
        for i in range(1, n - l + 2):
            j = i + l - 1
            e[i][j] = float('inf')
            # Weight recurrence: O(1) per cell
            w[i][j] = w[i][j - 1] + p[j] + q[j]

            # Try every key r in [i, j] as root: O(n) per cell
            for r in range(i, j + 1):
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                ops += 1  # Track primitive operation
                if t < e[i][j]:
                    e[i][j] = t
                    root[i][j] = r

    # Timing end
    elapsed = (time.perf_counter() - start) * 1_000_000  # Convert to microseconds

    print(f"[{name}] Optimal Cost: {e[1][n]:.4f} | Time: {elapsed:.2f} µs | Ops: {ops}")
    return e[1][n], ops, elapsed

if __name__ == "__main__":
    print("🔬 OBST Performance Study (Python)\n")
    # Instance 1 (n=7)
    p1 = [0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14]
    q1 = [0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05]
    optimal_bst(p1, q1, "Problem 1 (n=7)")

    # Instance 2 (n=5)
    p2 = [0, 0.15, 0.10, 0.05, 0.10, 0.20]
    q2 = [0.05, 0.10, 0.05, 0.05, 0.05, 0.10]
    optimal_bst(p2, q2, "Problem 2 (n=5)")
