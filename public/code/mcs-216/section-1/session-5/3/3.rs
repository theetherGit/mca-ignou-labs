/// Merge Sort Implementation in Rust
/// Time Complexity: O(n log n)
/// Space Complexity: O(n)

/// Merge two sorted subarrays
///
/// # Arguments
/// * `arr` - Mutable slice to sort
/// * `left` - Starting index of left subarray
/// * `mid` - Ending index of left subarray
/// * `right` - Ending index of right subarray
/// * `depth` - Recursion depth for indentation
fn merge(arr: &mut [i32], left: usize, mid: usize, right: usize, depth: usize) {
    let indent = "  ".repeat(depth);

    // Create temporary vectors
    let left_arr: Vec<i32> = arr[left..=mid].to_vec();
    let right_arr: Vec<i32> = arr[mid + 1..=right].to_vec();

    println!(
        "{}  Merge: Left={:?} Right={:?}",
        indent, left_arr, right_arr
    );

    let mut i = 0; // Index for left_arr
    let mut j = 0; // Index for right_arr
    let mut k = left; // Index for merged array

    // Merge the temp arrays
    while i < left_arr.len() && j < right_arr.len() {
        if left_arr[i] <= right_arr[j] {
            arr[k] = left_arr[i];
            println!(
                "{}    Compare {} <= {} → Take {}",
                indent, left_arr[i], right_arr[j], left_arr[i]
            );
            i += 1;
        } else {
            arr[k] = right_arr[j];
            println!(
                "{}    Compare {} > {} → Take {}",
                indent, left_arr[i], right_arr[j], right_arr[j]
            );
            j += 1;
        }
        k += 1;
    }

    // Copy remaining elements
    while i < left_arr.len() {
        arr[k] = left_arr[i];
        println!("{}    Append remaining left: {}", indent, left_arr[i]);
        i += 1;
        k += 1;
    }

    while j < right_arr.len() {
        arr[k] = right_arr[j];
        println!("{}    Append remaining right: {}", indent, right_arr[j]);
        j += 1;
        k += 1;
    }

    println!("{}  Result: {:?}\n", indent, &arr[left..=right]);
}

/// Recursive merge sort function
///
/// # Arguments
/// * `arr` - Mutable slice to sort
/// * `left` - Left index
/// * `right` - Right index
/// * `depth` - Recursion depth for indentation
fn merge_sort(arr: &mut [i32], left: usize, right: usize, depth: usize) {
    let indent = "  ".repeat(depth);

    // Print current subarray
    print!(
        "{}mergeSort({},{}) → {:?}\n",
        indent,
        left,
        right,
        &arr[left..=right]
    );

    if left < right {
        // Calculate mid point (avoid overflow)
        let mid = left + (right - left) / 2;

        // Sort first half
        merge_sort(arr, left, mid, depth + 1);

        // Sort second half
        merge_sort(arr, mid + 1, right, depth + 1);

        // Merge sorted halves
        merge(arr, left, mid, right, depth);
    } else {
        println!("{}  Base case: single element", indent);
    }
}

fn main() {
    let mut arr = [200, 150, 50, 100, 75, 25, 10, 5];
    let n = arr.len();

    println!("=== Merge Sort Implementation in Rust ===");
    println!("Original array: {:?}\n", arr);

    merge_sort(&mut arr, 0, n - 1, 0);

    println!("Sorted array: {:?}", arr);
}
