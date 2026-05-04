#include <stdio.h>
#include <string.h>

void swap(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }

// Function to calculate system time for a given permutation
int calculate_time(int arr[], int n) {
    int current_finish = 0, total = 0;
    for(int i = 0; i < n; i++) {
        current_finish += arr[i];
        total += current_finish;
    }
    return total;
}

void find_optimal(int arr[], int start, int n, int *min_time) {
    if (start == n) {
        int current_total = calculate_time(arr, n);
        if (current_total < *min_time) *min_time = current_total;
        return;
    }
    for (int i = start; i < n; i++) {
        swap(&arr[start], &arr[i]); // Generate permutation
        find_optimal(arr, start + 1, n, min_time);
        swap(&arr[start], &arr[i]); // Backtrack
    }
}

int main() {
    int times[] = {5, 8, 12};
    int n = 3;
    int min_time = 100000; // Initialize with a large value

    find_optimal(times, 0, n, &min_time);
    printf("Optimal Total System Time: %d\n", min_time);
    return 0;
}
