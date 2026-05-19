/*
 * Dijkstra's Algorithm Implementation in C
 * Finds shortest path from source to all vertices
 *
 * Compilation: gcc -o dijkstra dijkstra.c -std=c99
 * Execution: ./dijkstra
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 7
#define INF INT_MAX

// Structure to represent the graph
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    char vertices[MAX_VERTICES];
    int numVertices;
} Graph;

// Structure to store distance information
typedef struct {
    int distance;
    int previous;
    bool visited;
} DistInfo;

// Initialize graph
void initGraph(Graph *g) {
    g->numVertices = MAX_VERTICES;
    g->vertices[0] = 'A';
    g->vertices[1] = 'B';
    g->vertices[2] = 'C';
    g->vertices[3] = 'D';
    g->vertices[4] = 'E';
    g->vertices[5] = 'F';
    g->vertices[6] = 'G';

    // Initialize adjacency matrix with INF
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adjMatrix[i][j] = INF;
        }
    }
}

// Add edge to graph
void addEdge(Graph *g, char from, char to, int weight) {
    int fromIdx = -1, toIdx = -1;

    // Find indices
    for (int i = 0; i < g->numVertices; i++) {
        if (g->vertices[i] == from) fromIdx = i;
        if (g->vertices[i] == to) toIdx = i;
    }

    if (fromIdx != -1 && toIdx != -1) {
        g->adjMatrix[fromIdx][toIdx] = weight;
    }
}

// Find vertex with minimum distance
int findMinDistance(DistInfo dist[], int numVertices) {
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < numVertices; i++) {
        if (!dist[i].visited && dist[i].distance < min) {
            min = dist[i].distance;
            minIndex = i;
        }
    }

    return minIndex;
}

// Print path
void printPath(Graph *g, int previous[], int target) {
    if (previous[target] == -1) {
        printf("%c", g->vertices[target]);
        return;
    }
    printPath(g, previous, previous[target]);
    printf(" -> %c", g->vertices[target]);
}

// Dijkstra's algorithm
void dijkstra(Graph *g, char source) {
    DistInfo dist[MAX_VERTICES];
    int previous[MAX_VERTICES];
    int sourceIdx = -1;

    // Find source index
    for (int i = 0; i < g->numVertices; i++) {
        if (g->vertices[i] == source) {
            sourceIdx = i;
            break;
        }
    }

    // Initialize distances
    for (int i = 0; i < g->numVertices; i++) {
        dist[i].distance = INF;
        dist[i].visited = false;
        previous[i] = -1;
    }
    dist[sourceIdx].distance = 0;

    printf("\n%s\n", "==========================================================");
    printf("DIJKSTRA'S ALGORITHM - Source: %c\n", source);
    printf("%s\n", "==========================================================");

    // Main loop
    for (int count = 0; count < g->numVertices - 1; count++) {
        int u = findMinDistance(dist, g->numVertices);

        if (u == -1 || dist[u].distance == INF) break;

        dist[u].visited = true;

        printf("\nIteration %d: Processing vertex %c (distance: %d)\n",
               count + 1, g->vertices[u], dist[u].distance);

        // Update distances of adjacent vertices
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMatrix[u][v] != INF && !dist[v].visited) {
                int newDist = dist[u].distance + g->adjMatrix[u][v];

                if (newDist < dist[v].distance) {
                    dist[v].distance = newDist;
                    previous[v] = u;
                    printf("  Updated %c: distance = %d\n",
                           g->vertices[v], newDist);
                }
            }
        }
    }

    // Print final results
    printf("\n%s\n", "==========================================================");
    printf("FINAL RESULTS:\n");
    printf("%s\n", "==========================================================");

    for (int i = 0; i < g->numVertices; i++) {
        printf("Distance from %c to %c: ", source, g->vertices[i]);
        if (dist[i].distance == INF) {
            printf("∞ (unreachable)\n");
        } else {
            printf("%d | Path: %c -> ", dist[i].distance, source);
            printPath(g, previous, i);
            printf("\n");
        }
    }
}

int main() {
    Graph g;
    initGraph(&g);

    // Add edges (original graph)
    addEdge(&g, 'A', 'B', 6);
    addEdge(&g, 'A', 'G', 4);
    addEdge(&g, 'B', 'C', 2);
    addEdge(&g, 'B', 'D', 4);
    addEdge(&g, 'C', 'D', 2);
    addEdge(&g, 'G', 'D', 8);
    addEdge(&g, 'G', 'F', 8);
    addEdge(&g, 'D', 'F', 2);
    addEdge(&g, 'D', 'E', 1);
    addEdge(&g, 'F', 'A', 3);
    addEdge(&g, 'F', 'E', 7);

    // Q1: Shortest path from A
    printf("\n%s\n", "##################################################");
    printf("# Q1: SHORTEST PATH FROM A TO ALL VERTICES");
    printf("%s\n", "##################################################");
    dijkstra(&g, 'A');

    // Q2: Shortest path from B
    printf("\n\n%s\n", "##################################################");
    printf("# Q2: SHORTEST PATH FROM B TO ALL VERTICES");
    printf("%s\n", "##################################################");
    dijkstra(&g, 'B');

    return 0;
}
