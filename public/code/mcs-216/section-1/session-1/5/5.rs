fn bubble_sort(arr: &mut [i32]) {
    let n = arr.len();
    let (mut exchanges, mut comparisons) = (0, 0);
    let (mut outer_iters, mut inner_iters) = (0, 0);

    // Outer loop: Tracks how many elements are already placed at the end
    for i in 0..n {
        outer_iters += 1;

        // Inner loop: Comparison limit decreases as 'i' increases
        for j in 0..n - i - 1 {
            inner_iters += 1;
            comparisons += 1;

            if arr[j] > arr[j + 1] {
                // Exchange using Rust's safe swap method
                arr.swap(j, j + 1);
                exchanges += 1;
            }
        }
    }

    println!("Exchanges: {}, Comparisons: {}", exchanges, comparisons);
    println!(
        "Outer Loop Iters: {}, Inner Loop Iters: {}",
        outer_iters, inner_iters
    );
}

fn main() {
    let mut nums = [55, 25, 15, 40, 60, 35, 17, 65, 75, 10];
    bubble_sort(&mut nums);
}
