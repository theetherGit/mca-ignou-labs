use std::time::Instant;

/// Computes minimum scalar multiplication cost and optimal split points.
///
/// DP State:
///   m[i][j] = min cost to multiply matrices i..j
///   s[i][j] = optimal split index k
///
/// Complexity: O(n³) time, O(n²) space
/// Uses u64 for costs to safely handle large chains without overflow.
fn matrix_chain_order(dims: &[usize]) -> (Vec<Vec<u64>>, Vec<Vec<usize>>) {
    let n = dims.len() - 1;
    // Initialize DP tables with 0s
    let mut m = vec![vec![0u64; n]; n];
    let mut s = vec![vec![0usize; n]; n];

    // Iterate over chain lengths from 2 to n
    for length in 2..=n {
        // i = left index of the chain
        for i in 0..=(n - length) {
            let j = i + length - 1; // j = right index
            m[i][j] = u64::MAX;

            // Test every valid split point k
            for k in i..j {
                let cost = m[i][k] + m[k + 1][j] + (dims[i] * dims[k + 1] * dims[j + 1]) as u64;
                if cost < m[i][j] {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    (m, s)
}

/// Recursively builds the optimal parenthesization string.
fn construct_parens(s: &[Vec<usize>], i: usize, j: usize) -> String {
    if i == j {
        // Base case: single matrix
        format!("M{}", i + 1)
    } else {
        // Recursive case: split at optimal k and wrap in parentheses
        let k = s[i][j];
        format!(
            "({} · {})",
            construct_parens(s, i, k),
            construct_parens(s, k + 1, j)
        )
    }
}

fn main() {
    // Example dimensions: A(10x4), B(4x5), C(5x20), D(20x2), E(2x50)
    let dims = vec![10, 4, 5, 20, 2, 50];
    let n = dims.len() - 1;

    let start = Instant::now();
    let (m, s) = matrix_chain_order(&dims);
    let duration = start.elapsed();

    let optimal_parens = construct_parens(&s, 0, n - 1);
    let min_cost = m[0][n - 1];

    println!("Optimal Parenthesization: {}", optimal_parens);
    println!("Minimum Scalar Multiplications: {}", min_cost);
    println!(
        "DP Execution Time: {:.3} ms",
        duration.as_secs_f64() * 1000.0
    );
}
