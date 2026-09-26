// strassen_complete.rs
// Strassen's Matrix Multiplication with Deterministic Operation Counting
// Language: Rust 2021 | Layout: Vec<f64> (Row-Major) | Complexity: O(n^2.807)
// Compile: rustc -O strassen_complete.rs -o strassen
// Run:     ./strassen

struct OpCounter {
    mults: u64,
    adds: u64,
}

#[inline]
fn idx(i: usize, j: usize, n: usize) -> usize {
    i * n + j
}

fn mat_add(a: &[f64], b: &[f64], n: usize, ctr: &mut OpCounter) -> Vec<f64> {
    let mut c = vec![0.0; n * n];
    for i in 0..n {
        for j in 0..n {
            c[idx(i, j, n)] = a[idx(i, j, n)] + b[idx(i, j, n)];
        }
    }
    ctr.adds += (n * n) as u64;
    c
}

fn mat_sub(a: &[f64], b: &[f64], n: usize, ctr: &mut OpCounter) -> Vec<f64> {
    let mut c = vec![0.0; n * n];
    for i in 0..n {
        for j in 0..n {
            c[idx(i, j, n)] = a[idx(i, j, n)] - b[idx(i, j, n)];
        }
    }
    ctr.adds += (n * n) as u64;
    c
}

fn extract_quad(src: &[f64], src_n: usize, dst_n: usize, r: usize, c: usize) -> Vec<f64> {
    let mut dst = vec![0.0; dst_n * dst_n];
    for i in 0..dst_n {
        for j in 0..dst_n {
            dst[idx(i, j, dst_n)] = src[idx(i + r, j + c, src_n)];
        }
    }
    dst
}

fn merge_quads(c11: &[f64], c12: &[f64], c21: &[f64], c22: &[f64], n: usize) -> Vec<f64> {
    let m = n / 2;
    let mut c = vec![0.0; n * n];
    for i in 0..m {
        for j in 0..m {
            c[idx(i, j, n)] = c11[idx(i, j, m)];
            c[idx(i, j + m, n)] = c12[idx(i, j, m)];
            c[idx(i + m, j, n)] = c21[idx(i, j, m)];
            c[idx(i + m, j + m, n)] = c22[idx(i, j, m)];
        }
    }
    c
}

fn strassen(a: &[f64], b: &[f64], n: usize, ctr: &mut OpCounter) -> Vec<f64> {
    if n == 1 {
        ctr.mults += 1;
        return vec![a[0] * b[0]];
    }
    let m = n / 2;
    let a11 = extract_quad(a, n, m, 0, 0);
    let a12 = extract_quad(a, n, m, 0, m);
    let a21 = extract_quad(a, n, m, m, 0);
    let a22 = extract_quad(a, n, m, m, m);
    let b11 = extract_quad(b, n, m, 0, 0);
    let b12 = extract_quad(b, n, m, 0, m);
    let b21 = extract_quad(b, n, m, m, 0);
    let b22 = extract_quad(b, n, m, m, m);

    let m1 = strassen(
        &mat_add(&a11, &a22, m, ctr),
        &mat_add(&b11, &b22, m, ctr),
        m,
        ctr,
    );
    let m2 = strassen(&mat_add(&a21, &a22, m, ctr), &b11, m, ctr);
    let m3 = strassen(&a11, &mat_sub(&b12, &b22, m, ctr), m, ctr);
    let m4 = strassen(&a22, &mat_sub(&b21, &b11, m, ctr), m, ctr);
    let m5 = strassen(&mat_add(&a11, &a12, m, ctr), &b22, m, ctr);
    let m6 = strassen(
        &mat_sub(&a21, &a11, m, ctr),
        &mat_add(&b11, &b12, m, ctr),
        m,
        ctr,
    );
    let m7 = strassen(
        &mat_sub(&a12, &a22, m, ctr),
        &mat_add(&b21, &b22, m, ctr),
        m,
        ctr,
    );

    let c11 = {
        let t = mat_add(&m1, &m4, m, ctr);
        let t = mat_sub(&t, &m5, m, ctr);
        mat_add(&t, &m7, m, ctr)
    };
    let c12 = mat_add(&m3, &m5, m, ctr);
    let c21 = mat_add(&m2, &m4, m, ctr);
    let c22 = {
        let t = mat_sub(&m1, &m2, m, ctr);
        let t = mat_add(&t, &m3, m, ctr);
        mat_add(&t, &m6, m, ctr)
    };
    merge_quads(&c11, &c12, &c21, &c22, n)
}

fn naive_mul(a: &[f64], b: &[f64], n: usize, ctr: &mut OpCounter) -> Vec<f64> {
    let mut c = vec![0.0; n * n];
    for i in 0..n {
        for j in 0..n {
            let mut sum = 0.0;
            for k in 0..n {
                sum += a[idx(i, k, n)] * b[idx(k, j, n)];
                ctr.mults += 1;
                if k > 0 {
                    ctr.adds += 1;
                }
            }
            c[idx(i, j, n)] = sum;
        }
    }
    c
}

fn init_matrix(n: usize) -> Vec<f64> {
    (0..n * n).map(|i| (i + 1) as f64).collect()
}

fn main() {
    println!(
        "{:<4} | {:<14} | {:<13} | {:<11} | {:<10}",
        "n", "Strassen Mults", "Strassen Adds", "Naive Mults", "Naive Adds"
    );
    println!("{:-<70}", "");

    let sizes = [2, 4, 8, 16, 32, 64];
    for n in sizes {
        let a = init_matrix(n);
        let b = init_matrix(n);

        let mut ctr_str = OpCounter { mults: 0, adds: 0 };
        strassen(&a, &b, n, &mut ctr_str);

        let mut ctr_naive = OpCounter { mults: 0, adds: 0 };
        naive_mul(&a, &b, n, &mut ctr_naive);

        println!(
            "{:<4} | {:<14} | {:<13} | {:<11} | {:<10}",
            n, ctr_str.mults, ctr_str.adds, ctr_naive.mults, ctr_naive.adds
        );
    }
}
