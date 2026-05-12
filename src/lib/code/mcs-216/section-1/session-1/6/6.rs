fn selection_sort_analysis(arr: &mut [i32]) {
    let n = arr.len();
    let (mut ex, mut comp) = (0, 0);
    let (mut out, mut inn) = (0, 0);

    // Iterating through the array
    for i in 0..n {
        out += 1;
        let mut min_idx = i;

        // The inner loop scans the right side of the current index 'i'
        for j in i + 1..n {
            inn += 1;
            comp += 1;
            // Update min_idx if a smaller value is found
            if arr[j] < arr[min_idx] {
                min_idx = j;
            }
        }

        // Only swap if a new minimum was actually found at a different position
        if min_idx != i {
            arr.swap(i, min_idx);
            ex += 1;
        }
    }
    println!(
        "Exchanges: {}, Comparisons: {}, Inner Loops: {}",
        ex, comp, inn
    );
}
