def bubble_sort(numbers):
    n = len(numbers)
    # Counters for the requested metrics
    exchanges = 0
    comparisons = 0
    outer_iterations = 0
    inner_iterations = 0

    # The outer loop runs 'n' times (once for each element)
    for i in range(n):
        outer_iterations += 1

        # The inner loop runs from the start to the 'unsorted' portion.
        # We subtract 'i' because the last 'i' elements are already sorted.
        for j in range(0, n - i - 1):
            inner_iterations += 1
            comparisons += 1

            # Comparison: Is the current element larger than the next?
            if numbers[j] > numbers[j + 1]:
                # Exchange: Swap the elements
                numbers[j], numbers[j + 1] = numbers[j + 1], numbers[j]
                exchanges += 1

    return exchanges, comparisons, outer_iterations, inner_iterations


# Input data
data = [55, 25, 15, 40, 60, 35, 17, 65, 75, 10]
ex, comp, out, inn = bubble_sort(data)

print(f"Sorted: {data}")
print(f"Exchanges: {ex}, Comparisons: {comp}, Outer: {out}, Inner: {inn}")
