#include <stdio.h>
#include <stdlib.h>

struct Job {
    int id, deadline, profit;
};

// Sort descending based on profit
int compare(const void* a, const void* b) {
    return ((struct Job*)b)->profit - ((struct Job*)a)->profit;
}

void schedule_jobs(struct Job jobs[], int n) {
    qsort(jobs, n, sizeof(struct Job), compare);

    int max_d = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > max_d) max_d = jobs[i].deadline;

    int slots[max_d + 1];
    int result[max_d + 1];
    for (int i = 0; i <= max_d; i++) slots[i] = 0; // Initialize as free

    int total_profit = 0;
    for (int i = 0; i < n; i++) {
        // Find a slot from its deadline backwards
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slots[j] == 0) {
                slots[j] = 1; // Mark as occupied
                result[j] = jobs[i].id;
                total_profit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Maximum Profit: %d\nScheduled Sequence: ", total_profit);
    for (int i = 1; i <= max_d; i++) {
        if (slots[i]) printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    struct Job jobs[] = {{1,3,50}, {2,4,20}, {3,5,70}, {4,3,15}, {5,2,10}, {6,1,47}, {7,1,60}};
    int n = sizeof(jobs) / sizeof(jobs[0]);
    schedule_jobs(jobs, n);
    return 0;
}
