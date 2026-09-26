def binary_search(arr, low, high, target):
    """
    Recursive Binary Search in Python
    :param arr: Sorted list of integers
    :param low: Starting index
    :param high: Ending index
    :param target: Value to find
    :return: Index of target, or -1 if not found
    """
    # Base case: search range is invalid
    if low > high:
        return -1

    # Integer division for mid calculation
    mid = low + (high - low) // 2

    # Step-by-step trace for lab submission
    print(f"[Call] low={low}, high={high}, mid={mid}, arr[mid]={arr[mid]}")

    # Base case: target found
    if arr[mid] == target:
        return mid
    # Target is in the right half
    elif arr[mid] < target:
        return binary_search(arr, mid + 1, high, target)
    # Target is in the left half
    else:
        return binary_search(arr, low, mid - 1, target)

# Driver code
if __name__ == "__main__":
    arr = [10, 35, 40, 45, 50, 55, 60, 65, 70, 100]
    target = 100
    print("=== Recursive Binary Search in Python ===")

    result = binary_search(arr, 0, len(arr) - 1, target)

    if result != -1:
        print(f"\n✅ Target {target} found at index {result}")
    else:
        print(f"\n❌ Target {target} not found in array")
