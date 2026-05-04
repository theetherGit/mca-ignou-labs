fn right_to_left(mut base: u128, mut exp: u32) -> (u32, u32) {
    let (mut res, mut loops, mut mults) = (1u128, 0, 0);
    while exp > 0 {
        loops += 1;
        if exp % 2 == 1 {
            res = res.wrapping_mul(base);
            mults += 1;
        }
        if exp > 1 {
            base = base.wrapping_mul(base);
            mults += 1;
        }
        exp /= 2;
    }
    (loops, mults)
}

fn left_to_right(base: u128, exp: u32) -> (u32, u32) {
    let (mut res, mut loops, mut mults) = (1u128, 0, 0);
    let bit_len = 32 - exp.leading_zeros();

    for i in (0..bit_len).rev() {
        loops += 1;
        res = res.wrapping_mul(res); // Square
        mults += 1;
        if (exp >> i) & 1 == 1 {
            res = res.wrapping_mul(base); // Multiply by original base
            mults += 1;
        }
    }
    (loops, mults)
}

fn main() {
    let problems = [(4, 512), (3, 31)];
    for (b, e) in problems {
        println!("--- Problem: {}^{} ---", b, e);
        let r = right_to_left(b, e);
        let l = left_to_right(b, e as u32);
        println!("R2L: Loops={}, Multiplications={}", r.0, r.1);
        println!("L2R: Loops={}, Multiplications={}\n", l.0, l.1);
    }
}
