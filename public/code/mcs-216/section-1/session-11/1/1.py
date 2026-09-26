def optimal_bst(p, q):
    n = len(p) - 1  # p is 1-indexed, so length is n+1
    # e[i][j] stores expected cost, w[i][j] stores probability sum
    e = [[0.0] * (n + 2) for _ in range(n + 2)]
    w = [[0.0] * (n + 2) for _ in range(n + 2)]
    root = [[0] * (n + 1) for _ in range(n + 1)]

    # Base cases: single dummy keys
    for i in range(1, n + 2):
        e[i][i - 1] = q[i - 1]
        w[i][i - 1] = q[i - 1]

    # DP over chain length l
    for l in range(1, n + 1):
        for i in range(1, n - l + 2):
            j = i + l - 1
            e[i][j] = float("inf")
            w[i][j] = w[i][j - 1] + p[j] + q[j]

            # Try every key as root
            for r in range(i, j + 1):
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = t
                    root[i][j] = r
    return e, root


def print_tree(root, i, j, depth=0, is_left=True):
    """Recursively print the tree structure"""
    prefix = "L" if is_left else "R"
    indent = "    " * depth
    if i > j:
        print(f"{indent}{prefix} -> d{i - 1} (q={q[i - 1]:.2f})")
        return

    r = root[i][j]
    print(f"{indent}{prefix} -> k{r} (p={p[r]:.2f})")
    print_tree(root, i, r - 1, depth + 1, True)
    print_tree(root, r + 1, j, depth + 1, False)


if __name__ == "__main__":
    p = [0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14]
    q = [0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05]
    e, root = optimal_bst(p, q)
    print(f"Optimal Expected Cost: {e[1][len(p) - 1]:.4f}\n")
    print("Tree Structure:")
    print_tree(root, 1, len(p) - 1)
