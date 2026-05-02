struct Analysis {
    result: i64,
    multiplications: usize,
    additions: usize,
    iterations: usize,
}

fn horner_analysis(coeffs: &[i64], x: i64) -> Analysis {
    let mut res = coeffs[0];
    let mut m = 0;
    let mut a = 0;
    let mut i_count = 0;

    // Skipping the first element as it's our starting 'res'
    for &c in coeffs.iter().skip(1) {
        i_count += 1;
        res = (res * x) + c;
        m += 1;
        a += 1;
    }

    Analysis {
        result: res,
        multiplications: m,
        additions: a,
        iterations: i_count,
    }
}

fn main() {
    let coeffs = [6, 5, 4, -3, 2, 8, -7];
    let x = 3;
    let stats = horner_analysis(&coeffs, x);

    println!("Result: {}", stats.result);
    println!(
        "(a) Multiplications: {}, Additions: {}",
        stats.multiplications, stats.additions
    );
    println!("(b) Loop Iterations: {}", stats.iterations);
}
