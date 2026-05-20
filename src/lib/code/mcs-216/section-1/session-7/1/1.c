/*
 * Prim's Algorithm for Minimum Cost Spanning Tree
*/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 10  // Number of vertices
#define INF INT_MAX

// Map index 0-9 to V1-V10
const char* vertexNames[] = {"V1","V2","V3","V4","V5","V6","V7","V8","V9","V10"};

// Find vertex with minimum key value not yet in MST
int minKey(int key[], bool mstSet[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print MST construction steps
void printMST(int parent[], int graph[V][V]) {
    int totalCost = 0;
    printf("\n%-4s | %-5s | %-8s | %-6s | %-15s | %s\n",
           "Step", "Added", "Edge", "Weight", "Cumulative Cost", "MST Edges");
    printf("----------------------------------------------------------------------\n");

    for (int i = 1; i < V; i++) {
        int weight = graph[parent[i]][i];
        totalCost += weight;

        printf("%-4d | %-5s | %-8s | %-6d | %-15d | ",
               i, vertexNames[i],
               (parent[i] != -1) ? "" : "Root",
               weight, totalCost);

        // Print edges built so far
        for (int j = 1; j <= i; j++) {
            if (parent[j] != -1) {
                printf("%s-%s ", vertexNames[parent[j]], vertexNames[j]);
            }
        }
        printf("\n");
    }
    printf("\nTOTAL MINIMUM COST: %d\n", totalCost);
}

// Prim's algorithm implementation
void primMST(int graph[V][V]) {
    int parent[V];    // Stores MST structure
    int key[V];       // Key values to pick minimum weight edge
    bool mstSet[V];   // True if vertex is included in MST

    // Initialize all keys as INFINITE, mstSet as false
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Start from vertex 0 (V1)
    key[0] = 0;

    printf("\n======================================================================\n");
    printf("PRIM'S ALGORITHM - Starting Vertex: V1\n");
    printf("======================================================================\n");

    // MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Update key values of adjacent vertices
        for (int v = 0; v < V; v++) {
            // graph[u][v] != 0 means edge exists
            // mstSet[v] == false means v not in MST
            // graph[u][v] < key[v] means new shorter path found
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main() {
    // Adjacency matrix representation of the graph
    // 0 represents no direct edge
    int graph[V][V] = {
        {0, 35, 0, 20, 0, 0, 0, 0, 0, 0},  // V1
        {35, 0, 0, 10, 50, 0, 0, 0, 0, 0}, // V2
        {0, 0, 0, 22, 0, 0, 8, 0, 0, 0},   // V3
        {20, 10, 22, 0, 12, 0, 0, 5, 0, 0},// V4
        {0, 50, 0, 12, 0, 30, 0, 0, 30, 0},// V5
        {0, 0, 0, 0, 30, 0, 0, 0, 0, 9},   // V6
        {0, 0, 8, 0, 0, 0, 0, 60, 0, 0},   // V7
        {0, 0, 0, 5, 0, 0, 60, 0, 8, 0},   // V8
        {0, 0, 0, 0, 30, 0, 0, 8, 0, 16},  // V9
        {0, 0, 0, 0, 0, 9, 0, 0, 16, 0}    // V10
    };

    primMST(graph);
    return 0;
}
