#include <stdio.h>

/**
 * Merge Sort - Divide and Conquer Algorithm
 * Time Complexity: O(n log n) in all cases
 * Space Complexity: O(n) for temporary arrays
 */

/**
 * Merge two sorted subarrays arr[left...mid] and arr[mid+1...right]
 * @param arr     Original array
 * @param left    Starting index of left subarray
 * @param mid     Ending index of left subarray
 * @param right   Ending index of right subarray
 */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;      // Size of right subarray

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays
    printf("  Merge: Left=[");
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        printf("%d ", L[i]);
    }
    printf("] Right=[");
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        printf("%d ", R[j]);
    }
    printf("]\n");

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            printf("    Compare %d <= %d → Take %d\n", L[i], R[j], L[i]);
            i++;
        } else {
            arr[k] = R[j];
            printf("    Compare %d > %d → Take %d\n", L[i], R[j], R[j]);
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] (if any)
    while (i < n1) {
        arr[k] = L[i];
        printf("    Append remaining left: %d\n", L[i]);
        i++;
        k++;
    }

    // Copy remaining elements of R[] (if any)
    while (j < n2) {
        arr[k] = R[j];
        printf("    Append remaining right: %d\n", R[j]);
        j++;
        k++;
    }

    printf("  Result: [");
    for (int idx = left; idx <= right; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("]\n\n");
}

/**
 * Recursive merge sort function
 * @param arr   Array to sort
 * @param left  Left index
 * @param right Right index
 */
void mergeSort(int arr[], int left, int right, int depth) {
    // Print indentation for recursion depth
    for (int i = 0; i < depth; i++) printf("  ");
    printf("mergeSort(%d,%d) → [", left, right);
    for (int i = left; i <= right; i++) printf("%d ", arr[i]);
    printf("]\n");

    if (left < right) {
        // Find the middle point (avoid overflow)
        int mid = left + (right - left) / 2;

        // Sort first half
        mergeSort(arr, left, mid, depth + 1);

        // Sort second half
        mergeSort(arr, mid + 1, right, depth + 1);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    } else {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("  Base case: single element\n");
    }
}

/**
 * Print array elements
 */
void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int arr[] = {200, 150, 50, 100, 75, 25, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Merge Sort Implementation in C ===\n");
    printf("Original array: ");
    printArray(arr, n);
    printf("\n");

    mergeSort(arr, 0, n - 1, 0);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
