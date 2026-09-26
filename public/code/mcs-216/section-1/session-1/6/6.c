#include <stdio.h>

void selection_sort(int arr[], int n) {
    int exchanges = 0, comparisons = 0, inner_loops = 0;

    // Loop through each position in the array
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        // Search the unsorted part of the array for the smallest value
        for (int j = i + 1; j < n; j++) {
            inner_loops++;
            comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // If the smallest value is not in its correct place, swap it
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
            exchanges++;
        }
    }

    printf("Result -> Exchanges: %d, Comparisons: %d, Inner Loops: %d\n",
            exchanges, comparisons, inner_loops);
}
