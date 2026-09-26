/// Recursive Binary Search in Rust
/// Returns Some(index) if found, None otherwise
fn binary_search(arr: &[i32], low: isize, high: isize, target: i32) -> Option<isize> {
    // Base case: invalid range
    if low > high {
        return None;
    }

    // Safe mid calculation using isize to prevent underflow
    let mid = low + (high - low) / 2;

    // Trace output for lab documentation
    println!(
        "[Call] low={}, high={}, mid={}, arr[mid]={}",
        low, high, mid, arr[mid as usize]
    );

    // Check if target is at mid
    if arr[mid as usize] == target {
        return Some(mid);
    }

    // Recurse right or left based on comparison
    if arr[mid as usize] < target {
        return binary_search(arr, mid + 1, high, target);
    }

    binary_search(arr, low, mid - 1, target)
}

fn main() {
    let arr = [10, 35, 40, 45, 50, 55, 60, 65, 70, 100];
    let target = 100;
    println!("=== Recursive Binary Search in Rust ===");

    // Pass initial bounds: 0 to length-1
    match binary_search(&arr, 0, arr.len() as isize - 1, target) {
        Some(idx) => println!("\n✅ Target {} found at index {}", target, idx),
        None => println!("\n❌ Target {} not found in array", target),
    }
}
