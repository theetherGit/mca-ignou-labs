def merge_sort(arr, left=0, right=None, depth=0):
    """
    Recursive Merge Sort Implementation
    :param arr: List to sort
    :param left: Left index
    :param right: Right index
    :param depth: Recursion depth for indentation
    :return: Sorted list
    """
    if right is None:
        right = len(arr) - 1

    # Print current state with indentation
    indent = "  " * depth
    print(f"{indent}mergeSort({left},{right}) → {arr[left:right+1]}")

    if left < right:
        # Calculate mid point (avoid overflow)
        mid = left + (right - left) // 2

        # Recursively sort first half
        merge_sort(arr, left, mid, depth + 1)

        # Recursively sort second half
        merge_sort(arr, mid + 1, right, depth + 1)

        # Merge the sorted halves
        merge(arr, left, mid, right, depth)
    else:
        print(f"{indent}  Base case: single element")

    return arr

def merge(arr, left, mid, right, depth):
    """
    Merge two sorted subarrays
    :param arr: Original array
    :param left: Start of left subarray
    :param mid: End of left subarray
    :param right: End of right subarray
    :param depth: Indentation level
    """
    indent = "  " * depth

    # Create temporary arrays
    left_arr = arr[left:mid + 1]
    right_arr = arr[mid + 1:right + 1]

    print(f"{indent}  Merge: Left={left_arr} Right={right_arr}")

    i = j = 0  # Initial indices for left and right subarrays
    k = left   # Initial index of merged subarray

    # Merge the temp arrays back
    while i < len(left_arr) and j < len(right_arr):
        if left_arr[i] <= right_arr[j]:
            arr[k] = left_arr[i]
            print(f"{indent}    Compare {left_arr[i]} <= {right_arr[j]} → Take {left_arr[i]}")
            i += 1
        else:
            arr[k] = right_arr[j]
            print(f"{indent}    Compare {left_arr[i]} > {right_arr[j]} → Take {right_arr[j]}")
            j += 1
        k += 1

    # Copy remaining elements
    while i < len(left_arr):
        arr[k] = left_arr[i]
        print(f"{indent}    Append remaining left: {left_arr[i]}")
        i += 1
        k += 1

    while j < len(right_arr):
        arr[k] = right_arr[j]
        print(f"{indent}    Append remaining right: {right_arr[j]}")
        j += 1
        k += 1

    print(f"{indent}  Result: {arr[left:right+1]}\n")

# Driver code
if __name__ == "__main__":
    arr = [200, 150, 50, 100, 75, 25, 10, 5]

    print("=== Merge Sort Implementation in Python ===")
    print(f"Original array: {arr}\n")

    merge_sort(arr)

    print(f"Sorted array: {arr}")
