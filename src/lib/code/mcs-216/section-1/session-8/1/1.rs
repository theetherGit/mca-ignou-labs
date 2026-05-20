// Binomial Coefficient using Divide & Conquer

struct BinomialDnC {
    call_count: u32,
}

impl BinomialDnC {
    fn new() -> Self {
        BinomialDnC { call_count: 0 }
    }

    fn compute(&mut self, n: i32, k: i32) -> i64 {
        self.call_count += 1;

        // Base Cases: Directly solvable subproblems
        if k == 0 || k == n {
            return 1;
        }
        if k > n || k < 0 {
            return 0;
        }

        // Divide: Split into C(n-1, k-1) and C(n-1, k)
        // Conquer: Recursive resolution
        // Combine: Addition of subproblem results
        self.compute(n - 1, k - 1) + self.compute(n - 1, k)
    }
}

fn main() {
    let mut solver = BinomialDnC::new();
    let (n, k) = (5, 2);

    println!("Computing C({}, {}) using Divide & Conquer...\n", n, k);

    let result = solver.compute(n, k);

    println!("✅ Result: C({}, {}) = {}", n, k, result);
    println!("📊 Total Recursive Calls: {}", solver.call_count);
    println!("📈 Complexity Note: Overlapping subproblems cause O(2^n) calls.");
    println!("   Use memoization (DP) to reduce to O(nk) time.");
}
