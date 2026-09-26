fn optimal_bst(p: &[f64], q: &[f64]) -> (Vec<Vec<f64>>, Vec<Vec<usize>>) {
    let n = p.len() - 1;
    let mut e = vec![vec![0.0; n + 2]; n + 2];
    let mut w = vec![vec![0.0; n + 2]; n + 2];
    let mut root = vec![vec![0; n + 1]; n + 1];

    for i in 1..=n + 1 {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for l in 1..=n {
        for i in 1..=(n - l + 1) {
            let j = i + l - 1;
            e[i][j] = f64::MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for r in i..=j {
                let t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if t < e[i][j] {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    (e, root)
}

fn print_tree(
    root: &[Vec<usize>],
    p: &[f64],
    q: &[f64],
    i: usize,
    j: usize,
    depth: usize,
    side: char,
) {
    if i > j {
        println!(
            "{:indent$}{} -> d{} (q={:.2f})",
            "",
            side,
            i - 1,
            q[i - 1],
            indent = depth * 4
        );
        return;
    }
    let r = root[i][j];
    println!(
        "{:indent$}{} -> k{} (p={:.2f})",
        "",
        side,
        r,
        p[r],
        indent = depth * 4
    );
    print_tree(root, p, q, i, r - 1, depth + 1, 'L');
    print_tree(root, p, q, r + 1, j, depth + 1, 'R');
}

fn main() {
    let p = vec![0.0, 0.15, 0.10, 0.05, 0.10, 0.20];
    let q = vec![0.05, 0.10, 0.05, 0.05, 0.05, 0.10];
    let (e, root) = optimal_bst(&p, &q);
    println!("Optimal Expected Cost: {:.4}\n", e[1][p.len() - 1]);
    println!("Tree Structure:");
    print_tree(&root, &p, &q, 1, p.len() - 1, 0, 'R');
}
