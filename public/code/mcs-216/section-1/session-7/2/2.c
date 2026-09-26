#include <stdio.h>
#include <stdlib.h>

// Structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a connected, undirected, and weighted graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// A utility function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of u and v (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator function used by qsort to sort edges based on their weight
int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

// The main function to construct MCST using Kruskal's algorithm
void KruskalMCST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];  // Stores the final constructed MCST edges
    int e = 0;  // Index variable used for result[]
    int i = 0;  // Index variable used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));

    // Initialize V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the contents of result[] to display the built MCST
    int minimumCost = 0;
    printf("Edges in the constructed MCST (C Implementation):\n");
    for (i = 0; i < e; ++i) {
        printf("V%d -- V%d == %d\n", result[i].src + 1, result[i].dest + 1, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Spanning Tree Cost: %d\n", minimumCost);

    free(subsets);
}

int main() {
    int V = 10; // Number of vertices in graph
    int E = 14; // Number of edges in graph
    struct Graph* graph = createGraph(V, E);

    // Adding edges matching the problem image data (0-indexed adjustment: V1 -> 0, V2 -> 1...)
    graph->edge[0].src = 0; graph->edge[0].dest = 1; graph->edge[0].weight = 35; // V1-V2
    graph->edge[1].src = 0; graph->edge[1].dest = 3; graph->edge[1].weight = 20; // V1-V4
    graph->edge[2].src = 1; graph->edge[2].dest = 3; graph->edge[2].weight = 10; // V2-V4
    graph->edge[3].src = 1; graph->edge[3].dest = 4; graph->edge[3].weight = 50; // V2-V5
    graph->edge[4].src = 2; graph->edge[4].dest = 3; graph->edge[4].weight = 22; // V3-V4
    graph->edge[5].src = 2; graph->edge[5].dest = 6; graph->edge[5].weight = 8;  // V3-V7
    graph->edge[6].src = 3; graph->edge[6].dest = 4; graph->edge[6].weight = 12; // V4-V5
    graph->edge[7].src = 3; graph->edge[7].dest = 7; graph->edge[7].weight = 5;  // V4-V8
    graph->edge[8].src = 4; graph->edge[8].dest = 5; graph->edge[8].weight = 30; // V5-V6
    graph->edge[9].src = 4; graph->edge[9].dest = 8; graph->edge[9].weight = 30; // V5-V9
    graph->edge[10].src = 5; graph->edge[10].dest = 9; graph->edge[10].weight = 9; // V6-V10
    graph->edge[11].src = 6; graph->edge[11].dest = 7; graph->edge[11].weight = 60;// V7-V8
    graph->edge[12].src = 7; graph->edge[12].dest = 8; graph->edge[12].weight = 8;  // V8-V9
    graph->edge[13].src = 8; graph->edge[13].dest = 9; graph->edge[13].weight = 16; // V9-V10

    KruskalMCST(graph);

    free(graph->edge);
    free(graph);
    return 0;
}
