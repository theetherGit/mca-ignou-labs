#include <stdio.h>

// Define the number of vertices
#define V 5
// Define Infinity (a value larger than any possible path sum)
#define INF 99999

void floydWarshall(int graph[V][V]) {
    // dist[i][j] will store the shortest distance from i to j
    int dist[V][V];
    int i, j, k;

    // 1. Initialize the solution matrix same as input graph matrix
    //    Or we can say the initial values of shortest distances are based
    //    on shortest paths considering no intermediate vertices.
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // 2. Add all vertices one by one to the set of intermediate vertices.
    //    k is the intermediate vertex.
    for (k = 0; k < V; k++) {
        // i is the source vertex
        for (i = 0; i < V; i++) {
            // j is the destination vertex
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                // Check for INF to prevent integer overflow
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    /*
       Example Graph (Based on the second image provided previously):
       Mapping: V1=0, V2=1, V3=2, V4=3, V5=4

       Edges:
       1->2 (3), 1->5 (9)
       2->1 (4), 2->3 (15), 2->4 (5)
       4->2 (7), 4->3 (5)
       5->3 (16), 5->4 (8)
    */
    int graph[V][V] = {
        {0,   3,  INF, INF, 9},
        {4,   0,  15,  5,   INF},
        {INF, INF, 0,   INF, INF},
        {INF, 7,  5,   0,   INF},
        {INF, INF, 16,  8,   0}
    };

    floydWarshall(graph);
    return 0;
}
