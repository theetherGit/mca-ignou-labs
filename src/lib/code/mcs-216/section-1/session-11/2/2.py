def optimal_bst(p, q):
    """Compute optimal BST using dynamic programming."""
    n = len(p) - 1
    e = [[0.0] * (n + 2) for _ in range(n + 2)]
    w = [[0.0] * (n + 2) for _ in range(n + 2)]
    root = [[0] * (n + 1) for _ in range(n + 1)]

    # Base cases: empty subtrees
    for i in range(1, n + 2):
        e[i][i - 1] = q[i - 1]
        w[i][i - 1] = q[i - 1]

    # DP over chain length l
    for l in range(1, n + 1):
        for i in range(1, n - l + 2):
            j = i + l - 1
            e[i][j] = float("inf")
            w[i][j] = w[i][j - 1] + p[j] + q[j]

            for r in range(i, j + 1):
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = t
                    root[i][j] = r
    return e, root


def print_tree(root, p, q, i, j, depth=0, side="R"):
    """Recursively print tree structure."""
    indent = "    " * depth
    if i > j:
        print(f"{indent}{side} -> d{i - 1} (q={q[i - 1]:.2f})")
        return
    r = root[i][j]
    print(f"{indent}{side} -> k{r} (p={p[r]:.2f})")
    print_tree(root, p, q, i, r - 1, depth + 1, "L")
    print_tree(root, p, q, r + 1, j, depth + 1, "R")


if __name__ == "__main__":
    p = [0, 0.15, 0.10, 0.05, 0.10, 0.20]
    q = [0.05, 0.10, 0.05, 0.05, 0.05, 0.10]
    e, root = optimal_bst(p, q)
    print(f"Optimal Expected Cost: {e[1][len(p) - 1]:.4f}\n")
    print("Tree Structure:")
    print_tree(root, p, q, 1, len(p) - 1)
