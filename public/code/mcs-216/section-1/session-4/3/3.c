#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int freq;
    char data;
    struct Node *left, *right;
} Node;

// Simulated Priority Queue
Node* pq[20];
int pq_size = 0;
int active_nodes = 0;

Node* newNode(int freq, char data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->freq = freq;
    n->data = data;
    n->left = n->right = NULL;
    pq[pq_size++] = n;
    active_nodes++;
    return n;
}

// Extract minimum frequency node
Node* extractMin() {
    int minIdx = -1;
    for (int i = 0; i < pq_size; i++) {
        if (pq[i] != NULL) {
            if (minIdx == -1 || pq[i]->freq < pq[minIdx]->freq)
                minIdx = i;
        }
    }
    if (minIdx == -1) return NULL;
    Node* minNode = pq[minIdx];
    pq[minIdx] = NULL;
    active_nodes--;
    return minNode;
}

void printCodes(Node* root, char arr[], int top) {
    if (root->left) {
        arr[top] = '0';
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = '1';
        printCodes(root->right, arr, top + 1);
    }
    if (root->data != '\0') { // Leaf node
        arr[top] = '\0';
        printf("%c: %s\n", root->data, arr);
    }
}

// Calculate total weighted path length for average
int calculateTotalBits(Node* root, int depth) {
    if (root == NULL) return 0;
    if (root->data != '\0') return root->freq * depth;
    return calculateTotalBits(root->left, depth + 1) +
           calculateTotalBits(root->right, depth + 1);
}

int main() {
    char chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int freqs[] = {15, 25, 5, 7, 10, 13, 9};
    int n = 7, totalFreq = 0;

    for (int i = 0; i < n; i++) {
        newNode(freqs[i], chars[i]);
        totalFreq += freqs[i];
    }

    // Build Huffman Tree
    while (active_nodes > 1) {
        Node* left = extractMin();
        Node* right = extractMin();
        if (!left || !right) break;

        Node* merged = newNode(left->freq + right->freq, '\0');
        merged->left = left;
        merged->right = right;
    }

    Node* root = extractMin();
    char code[50];
    printf("Huffman Codes:\n");
    printCodes(root, code, 0);

    int totalBits = calculateTotalBits(root, 0);
    double avgBits = (double)totalBits / totalFreq;
    printf("\nAverage bits per character: %.2f\n", avgBits);

    return 0;
}
