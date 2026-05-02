fn get_gcd(mut a: u64, mut b: u64) -> u64 {
    // We use u64 (64-bit unsigned integer) for large positive numbers
    // The algorithm continues as long as b is not zero
    while b != 0 {
        // Calculate the remainder
        let remainder = a % b;

        // Update 'a' to 'b' and 'b' to the remainder for the next iteration
        a = b;
        b = remainder;
    }

    // Once b hits zero, a is the greatest common divisor
    a
}

fn main() {
    let x = 270;
    let y = 192;
    println!("The GCD of {} and {} is {}", x, y, get_gcd(x, y));
}
