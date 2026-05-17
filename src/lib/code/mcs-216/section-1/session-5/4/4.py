def partition(arr, low, high):
    """
    Lomuto Partition: Rearranges array so elements <= pivot are left,
    and elements > pivot are right. Returns pivot's final index.
    """
    pivot = arr[high]
    i = low - 1  # Boundary for smaller elements

    print(f"  Partitioning [{low}..{high}] with pivot={pivot}")

    for j in range(low, high):
        print(f"    Compare arr[{j}]={arr[j]} with pivot={pivot} → ", end="")
        if arr[j] <= pivot:
            i += 1
            if i != j:
                arr[i], arr[j] = arr[j], arr[i]
                print(f"SWAP {arr[i]} ↔ {arr[j]}")
            else:
                print("No swap needed")
        else:
            print("Skip (greater)")

    # Place pivot in correct sorted position
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    print(f"  Final swap: place pivot at index {i + 1}")
    return i + 1

def quick_sort(arr, low, high):
    """Recursive Quick Sort"""
    if low < high:
        print(f"quickSort({low}, {high})")
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)   # Sort left partition
        quick_sort(arr, pi + 1, high)  # Sort right partition

if __name__ == "__main__":
    arr = [12, 20, 22, 16, 25, 18, 8, 10, 6, 15]
    print("=== Quick Sort Implementation in Python ===")
    print(f"Original: {arr}\n")

    quick_sort(arr, 0, len(arr) - 1)

    print(f"\nSorted:   {arr}")
