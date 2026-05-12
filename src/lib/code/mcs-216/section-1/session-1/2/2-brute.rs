fn brute_force(coeffs: &[i64], x: i64) {
    let mut total_sum = 0;
    let mut mults = 0;
    let mut adds = 0;
    let n = coeffs.len() - 1; // Highest degree

    // Loop through coefficients from highest degree to constant
    for (i, &coeff) in coeffs.iter().enumerate() {
        let power = n - i;
        let mut current_pow_val = 1;

        // Manually compute power to track multiplication overhead
        for _ in 0..power {
            current_pow_val *= x;
            mults += 1;
        }

        // Perform: coefficient * (x^power)
        if power > 0 {
            total_sum += coeff * current_pow_val;
            mults += 1;
        } else {
            // Constant term (x^0)
            total_sum += coeff;
        }

        // Perform the addition to the total sum
        if i > 0 {
            adds += 1;
        }
    }

    println!("Brute Force Result: {}", total_sum);
    println!("Multiplications: {}, Additions: {}", mults, adds);
}

fn main() {
    let coeffs = [6, 5, 4, -3, 2, 8, -7];
    brute_force(&coeffs, 3);
}
