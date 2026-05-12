def selection_sort_detailed(arr):
    n = len(arr)
    # Metric trackers
    exchanges, comparisons = 0, 0
    outer_iters, inner_iters = 0, 0

    # Outer loop: Moves the boundary of the unsorted subarray
    for i in range(n):
        outer_iters += 1

        # Step 1: Assume the first unsorted element is the smallest
        min_index = i

        # Step 2: Inner loop to find the actual minimum in the remaining unsorted list
        for j in range(i + 1, n):
            inner_iters += 1
            comparisons += 1
            if arr[j] < arr[min_index]:
                # We found a new minimum; just update the index (no swap yet!)
                min_index = j

        # Step 3: Swap the found minimum with the first unsorted element
        # This happens ONLY once per outer loop iteration.
        if min_index != i:
            arr[i], arr[min_index] = arr[min_index], arr[i]
            exchanges += 1

    return exchanges, comparisons, outer_iters, inner_iters


# Run the analysis
data = [55, 25, 15, 40, 60, 35, 17, 65, 75, 10]
ex, comp, out, inn = selection_sort_detailed(data)
print(f"Exchanges: {ex}, Comparisons: {comp}")
