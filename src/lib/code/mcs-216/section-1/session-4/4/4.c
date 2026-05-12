#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 13
#define MAX_CODE_LEN 20

// Huffman Tree Node
typedef struct Node {
    int freq;
    char data;
    struct Node *left, *right;
} Node;

// Priority Queue (simple array-based min-heap simulation)
Node* pq[100];
int pq_size = 0;

// Create new node
Node* newNode(int freq, char data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->freq = freq;
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

// Insert into priority queue (maintain sorted order for simplicity)
void pq_insert(Node* node) {
    int i = pq_size - 1;
    while (i >= 0 && pq[i]->freq > node->freq) {
        pq[i + 1] = pq[i];
        i--;
    }
    pq[i + 1] = node;
    pq_size++;
}

// Extract minimum frequency node
Node* pq_extract_min() {
    if (pq_size == 0) return NULL;
    return pq[pq_size--];
}

// Generate and print codes via DFS
void printCodes(Node* root, char arr[], int top, int* total_bits, int freq_map[], char chars[]) {
    if (root->left) {
        arr[top] = '0';
        printCodes(root->left, arr, top + 1, total_bits, freq_map, chars);
    }
    if (root->right) {
        arr[top] = '1';
        printCodes(root->right, arr, top + 1, total_bits, freq_map, chars);
    }
    // Leaf node: print code and accumulate bits
    if (root->data != '\0') {
        arr[top] = '\0';
        // Find frequency for this character
        for (int i = 0; i < MAX_CHARS; i++) {
            if (chars[i] == root->data) {
                int len = top;
                *total_bits += freq_map[i] * len;
                // Handle special character display
                if (root->data == ' ') printf("  ' '  ");
                else if (root->data == '\n') printf(" '\\n' ");
                else if (root->data == ':') printf("  ':'  ");
                else if (root->data == ',') printf("  ','  ");
                else printf("  '%c'  ", root->data);
                printf("(freq=%4d): %s\n", freq_map[i], arr);
                break;
            }
        }
    }
}

int main() {
    // Character-frequency pairs
    char chars[MAX_CHARS] = {':', ' ', '\n', ',', '0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int freqs[MAX_CHARS] = {80, 500, 110, 500, 300, 200, 150, 60, 180, 240, 170, 200, 202};
    int total_freq = 0;

    // Initialize priority queue with leaf nodes
    for (int i = 0; i < MAX_CHARS; i++) {
        pq_insert(newNode(freqs[i], chars[i]));
        total_freq += freqs[i];
    }

    // Build Huffman Tree
    while (pq_size > 1) {
        Node* left = pq_extract_min();
        Node* right = pq_extract_min();
        Node* merged = newNode(left->freq + right->freq, '\0');
        merged->left = left;
        merged->right = right;
        pq_insert(merged);
    }

    Node* root = pq_extract_min();
    char code[MAX_CODE_LEN];
    int total_bits = 0;

    printf("Huffman Codes:\n");
    printCodes(root, code, 0, &total_bits, freqs, chars);

    double avg_bits = (double)total_bits / total_freq;
    printf("\nAverage bits per character: %.2f\n", avg_bits);
    printf("Total frequency: %d\n", total_freq);
    printf("Total bits for encoded file: %d\n", total_bits);

    return 0;
}
