# Binomial Coefficient using Divide & Conquer
class BinomialDnC:
    def __init__(self):
        self.call_count = 0  # Tracks recursive calls for analysis

    def compute(self, n, k):
        """
        Divides problem using Pascal's Identity:
        C(n,k) = C(n-1, k-1) + C(n-1, k)
        """
        self.call_count += 1

        # Base Cases (Conquer step for trivial problems)
        if k == 0 or k == n:
            return 1
        if k > n or k < 0:
            return 0

        # Divide: Split into two subproblems
        left = self.compute(n - 1, k - 1)
        right = self.compute(n - 1, k)

        # Combine: Add results of subproblems
        return left + right


def main():
    solver = BinomialDnC()
    n, k = 5, 2

    print(f"Computing C({n}, {k}) using Divide & Conquer...\n")
    result = solver.compute(n, k)

    print(f"✅ Result: C({n}, {k}) = {result}")
    print(f"📊 Total Recursive Calls: {solver.call_count}")
    print(
        "📈 Note: Pure D&C has overlapping subproblems. For n=5,k=2, it takes 19 calls."
    )
    print("   Optimal approach: Add memoization → O(nk) time (Dynamic Programming).")


if __name__ == "__main__":
    main()
