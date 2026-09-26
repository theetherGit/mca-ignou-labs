fn gcd_with_metrics(mut a: i64, mut b: i64) -> (i64, u32, u32) {
    let mut mod_ops = 0;
    let mut assign_ops = 0;

    // Initial assignments to absolute values
    a = a.abs();
    b = b.abs();
    assign_ops += 2;

    while b != 0 {
        let remainder = a % b;
        mod_ops += 1;

        a = b;
        b = remainder;
        assign_ops += 2;
    }

    (a, mod_ops, assign_ops)
}

fn main() {
    let (result, mods, assigns) = gcd_with_metrics(15265, 15);
    println!("GCD: {}", result);
    println!("Modulo Ops: {}, Assignment Ops: {}", mods, assigns);
}
