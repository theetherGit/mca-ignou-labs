#include <stdio.h>
#include <stdlib.h>

struct Job {
    int id;
    int service_time;
};

// Comparator for qsort: sorts in ascending order of service_time
int compare_jobs(const void *a, const void *b) {
    return ((struct Job*)a)->service_time - ((struct Job*)b)->service_time;
}

int main() {
    struct Job jobs[] = {{1, 5}, {2, 10}, {3, 7}, {4, 8}};
    int n = 4;

    // Sort jobs using Shortest Job First strategy
    qsort(jobs, n, sizeof(struct Job), compare_jobs);

    int finish_time = 0;
    int total_system_time = 0;

    printf("Optimal Sequence: ");
    for (int i = 0; i < n; i++) {
        finish_time += jobs[i].service_time;   // Completion time of job i
        total_system_time += finish_time;     // Cumulative system wait time
        printf("%d%s", jobs[i].id, (i == n - 1) ? "" : " -> ");
    }

    printf("\nTotal Time Spent in System: %d\n", total_system_time);

    return 0;
}
