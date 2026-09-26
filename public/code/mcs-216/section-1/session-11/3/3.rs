use std::time::Instant;

/// Structure to hold performance metrics for a single run
struct BenchResult {
    optimal_cost: f64,
    operations: usize,
    time_us: f64,
}

fn optimal_bst(p: &[f64], q: &[f64], name: &str) -> BenchResult {
    let n = p.len() - 1;
    let mut ops = 0;

    // Allocate DP tables with 1-based indexing padding
    let mut e = vec![vec![0.0; n + 2]; n + 2];
    let mut w = vec![vec![0.0; n + 2]; n + 2];
    let mut root = vec![vec![0usize; n + 1]; n + 1];

    // Base case: empty subtrees
    for i in 1..=n + 1 {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    let start = Instant::now();

    // DP over chain length l
    for l in 1..=n {
        for i in 1..=(n - l + 1) {
            let j = i + l - 1;
            e[i][j] = f64::MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Root selection loop
            for r in i..=j {
                let t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                ops += 1;
                if t < e[i][j] {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    let elapsed_us = start.elapsed().as_secs_f64() * 1_000_000.0;

    println!(
        "[{}] Optimal Cost: {:.4} | Time: {:.2} µs | Ops: {}",
        name, e[1][n], elapsed_us, ops
    );

    BenchResult {
        optimal_cost: e[1][n],
        operations: ops,
        time_us: elapsed_us,
    }
}

fn main() {
    println!("🔬 OBST Performance Study (Rust)\n");

    // Problem 1 (n=7)
    let p1 = vec![0.0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14];
    let q1 = vec![0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05];
    optimal_bst(&p1, &q1, "Problem 1 (n=7)");

    // Problem 2 (n=5)
    let p2 = vec![0.0, 0.15, 0.10, 0.05, 0.10, 0.20];
    let q2 = vec![0.05, 0.10, 0.05, 0.05, 0.05, 0.10];
    optimal_bst(&p2, &q2, "Problem 2 (n=5)");
}
