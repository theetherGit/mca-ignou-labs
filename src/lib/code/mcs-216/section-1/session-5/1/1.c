#include <stdio.h>

/**
 * Recursive Binary Search
 * @param arr    Sorted integer array
 * @param low    Starting index of current search range
 * @param high   Ending index of current search range
 * @param target Value to search for
 * @return       Index of target, or -1 if not found
 */
int binarySearch(int arr[], int low, int high, int target) {
    // Base case: invalid range means target is not in array
    if (low > high) {
        return -1;
    }

    // Calculate mid to avoid integer overflow
    int mid = low + (high - low) / 2;

    // Print step-by-step trace for lab documentation
    printf("[Call] low=%d, high=%d, mid=%d, arr[mid]=%d\n", low, high, mid, arr[mid]);

    // Check if target is present at mid
    if (arr[mid] == target) {
        return mid;
    }

    // If target is greater, ignore left half and search right
    if (arr[mid] < target) {
        return binarySearch(arr, mid + 1, high, target);
    }

    // If target is smaller, ignore right half and search left
    return binarySearch(arr, low, mid - 1, target);
}

int main() {
    int arr[] = {10, 35, 40, 45, 50, 55, 60, 65, 70, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 100;

    printf("=== Recursive Binary Search in C ===\n");
    int result = binarySearch(arr, 0, n - 1, target);

    if (result != -1)
        printf("\n✅ Target %d found at index %d\n", target, result);
    else
        printf("\n❌ Target %d not found in array\n", target);

    return 0;
}
