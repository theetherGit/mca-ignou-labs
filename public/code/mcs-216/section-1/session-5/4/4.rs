/// Quick Sort Implementation in Rust
/// Uses Lomuto partition scheme with last element as pivot

/// Swaps two elements in a mutable slice
fn swap(arr: &mut [i32], i: usize, j: usize) {
    arr.swap(i, j);
}

/// Partition function
fn partition(arr: &mut [i32], low: usize, high: usize) -> usize {
    let pivot = arr[high];
    let mut i = if low == 0 { 0 } else { low } - 1;

    println!("  Partitioning [{low}..{high}] with pivot={pivot}");

    for j in low..high {
        print!("    Compare arr[{j}]={} with pivot={pivot} → ", arr[j]);
        if arr[j] <= pivot {
            i += 1;
            if i != j {
                swap(arr, i, j);
                println!("SWAP {} ↔ {}", arr[i], arr[j]);
            } else {
                println!("No swap needed");
            }
        } else {
            println!("Skip (greater)");
        }
    }

    // Place pivot in correct position
    swap(arr, i + 1, high);
    println!("  Final swap: place pivot at index {}", i + 1);
    i + 1
}

/// Recursive quick sort
fn quick_sort(arr: &mut [i32], low: usize, high: usize) {
    if low < high {
        println!("quickSort({}, {})", low, high);
        let pi = partition(arr, low, high);
        quick_sort(arr, low, if pi == 0 { 0 } else { pi - 1 });
        if pi + 1 <= high {
            quick_sort(arr, pi + 1, high);
        }
    }
}

fn main() {
    let mut arr = [12, 20, 22, 16, 25, 18, 8, 10, 6, 15];
    let n = arr.len();

    println!("=== Quick Sort Implementation in Rust ===");
    println!("Original: {:?}\n", arr);

    quick_sort(&mut arr, 0, n - 1);

    println!("\nSorted:   {:?}", arr);
}
