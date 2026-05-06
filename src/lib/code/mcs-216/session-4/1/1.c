#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char data, int freq) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data; n->freq = freq;
    n->left = n->right = NULL;
    return n;
}

void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) { arr[top] = 0; printCodes(root->left, arr, top + 1); }
    if (root->right) { arr[top] = 1; printCodes(root->right, arr, top + 1); }
    if (!root->left && !root->right) {
        printf("%-7c | %-7d | ", root->data, root->freq);
        for (int i = 0; i < top; i++) printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    char letters[] = {'A', 'B', 'I', 'M', 'S', 'X', 'Z'};
    int freqs[] = {10, 7, 15, 8, 10, 5, 2};
    struct Node* nodes[7];

    for (int i = 0; i < 7; i++) nodes[i] = createNode(letters[i], freqs[i]);

    printf("--- STEP-BY-STEP MERGING ---\n");
    int size = 7;
    while (size > 1) {
        int m1 = 0, m2 = 1;
        if (nodes[m1]->freq > nodes[m2]->freq) { int t = m1; m1 = m2; m2 = t; }
        for (int i = 2; i < size; i++) {
            if (nodes[i]->freq < nodes[m1]->freq) { m2 = m1; m1 = i; }
            else if (nodes[i]->freq < nodes[m2]->freq) { m2 = i; }
        }

        struct Node* parent = createNode('$', nodes[m1]->freq + nodes[m2]->freq);
        parent->left = nodes[m1]; parent->right = nodes[m2];
        printf("Merged %d + %d = %d\n", nodes[m1]->freq, nodes[m2]->freq, parent->freq);

        nodes[m1] = parent;
        nodes[m2] = nodes[size - 1];
        size--;
    }

    printf("\n--- FINAL TABLE ---\n%-7s | %-7s | %-12s\n", "Letter", "Freq", "Code");
    printf("-----------------------------\n");
    int path[10];
    printCodes(nodes[0], path, 0);
    return 0;
}
