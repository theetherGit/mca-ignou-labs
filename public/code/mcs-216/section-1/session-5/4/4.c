#include <stdio.h>

/**
 * Swap two integers
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Lomuto Partition Scheme
 * @param arr   Array to partition
 * @param low   Starting index
 * @param high  Ending index (pivot is at high)
 * @return      Final pivot index
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Select last element as pivot
    int i = low - 1;        // Index of smaller element

    printf("  Partitioning [%d..%d] with pivot=%d\n", low, high, pivot);

    for (int j = low; j < high; j++) {
        printf("    Compare arr[%d]=%d with pivot=%d → ", j, arr[j], pivot);
        if (arr[j] <= pivot) {
            i++;
            if (i != j) {
                swap(&arr[i], &arr[j]);
                printf("SWAP %d ↔ %d\n", arr[i], arr[j]);
            } else {
                printf("No swap needed\n");
            }
        } else {
            printf("Skip (greater)\n");
        }
    }

    // Place pivot in correct position
    swap(&arr[i + 1], &arr[high]);
    printf("  Final swap: place pivot at index %d\n", i + 1);
    return i + 1;
}

/**
 * Recursive Quick Sort
 */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        printf("quickSort(%d, %d)\n", low, high);
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * Print array
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
    int arr[] = {12, 20, 22, 16, 25, 18, 8, 10, 6, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Quick Sort Implementation in C ===\n");
    printf("Original: "); printArray(arr, n);
    printf("\n");

    quickSort(arr, 0, n - 1);

    printf("\nSorted:   "); printArray(arr, n);
    return 0;
}
