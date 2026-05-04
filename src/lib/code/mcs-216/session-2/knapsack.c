#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double p, w, ratio;
} Item;

// Comparator for descending order based on ratio
int compareItems(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;
    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

double fractionalKnapsack(double p[], double w[], int n, double capacity) {
    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        items[i].p = p[i];
        items[i].w = w[i];
        items[i].ratio = p[i] / w[i];
    }

    qsort(items, n, sizeof(Item), compareItems);

    double totalProfit = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].w) {
            capacity -= items[i].w;
            totalProfit += items[i].p;
        } else {
            // Add the fractional part
            totalProfit += items[i].p * (capacity / items[i].w);
            break;
        }
    }
    return totalProfit;
}

int main() {
    double p2[] = {20, 30, 40, 32, 55};
    double w2[] = {5, 8, 10, 12, 15};
    printf("Result Q2: %.2f\n", fractionalKnapsack(p2, w2, 5, 50));
    return 0;
}
