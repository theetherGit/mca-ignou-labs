fn main() {
    let a: [[i32; 4]; 4] = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16],
    ];
    let b: [[i32; 4]; 4] = [[1, 0, 0, 1], [0, 1, 0, 1], [0, 0, 1, 1], [1, 1, 1, 0]];

    let mut c = [[0i32; 4]; 4];
    let (mut outer, mut inner, mut mul, mut add) = (0, 0, 0, 0);

    for i in 0..4 {
        outer += 1;
        for j in 0..4 {
            for k in 0..4 {
                c[i][j] += a[i][k] * b[k][j];
                inner += 1;
                mul += 1;
                add += 1;
            }
        }
    }

    println!("Result Matrix C:");
    for row in &c {
        println!("{:4} {:4} {:4} {:4}", row[0], row[1], row[2], row[3]);
    }
    println!("\nOuter-most loop runs: {} times", outer);
    println!("Inner-most loop runs: {} times", inner);
    println!("Total Multiplications: {}", mul);
    println!("Total Additions: {}", add);
}
