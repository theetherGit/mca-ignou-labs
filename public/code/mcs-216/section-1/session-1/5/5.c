#include <stdio.h>

void bubble_sort(int arr[], int n) {
    int exchanges = 0, comparisons = 0;
    int outer_iters = 0, inner_iters = 0;

    // Outer loop: Each pass ensures the i-th largest element is in place
    for (int i = 0; i < n; i++) {
        outer_iters++;

        // Inner loop: Reduces range as elements are sorted at the end
        for (int j = 0; j < n - i - 1; j++) {
            inner_iters++;
            comparisons++;

            // Comparison
            if (arr[j] > arr[j + 1]) {
                // Exchange logic using a temporary variable
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                exchanges++;
            }
        }
    }

    printf("Metrics for Bubble Sort:\n");
    printf("(i)   Exchanges: %d\n", exchanges);
    printf("(ii)  Comparisons: %d\n", comparisons);
    printf("(iii) Outer Iterations: %d, Inner Iterations: %d\n", outer_iters, inner_iters);
}

int main() {
    int data[] = {55, 25, 15, 40, 60, 35, 17, 65, 75, 10};
    int size = sizeof(data) / sizeof(data[0]);
    bubble_sort(data, size);
    return 0;
}
