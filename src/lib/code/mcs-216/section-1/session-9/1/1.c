#include <stdio.h>

#define V 5
#define INF 999999

void floydWarshall(int graph[V][V]) {
    int dist[V][V];
    int i, j, k;

    // Initialize the solution matrix same as input graph matrix
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of intermediate
       vertices.
       ---> Before start of an iteration, we have shortest
            distances between all pairs of vertices such that
            the shortest distances consider only the vertices
            in set {0, 1, 2, .. k-1} as intermediate vertices.
       ----> After the end of an iteration, vertex no. k is
             added to the set of intermediate vertices and the
             set becomes {0, 1, 2, .. k}
    */
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printf("The following matrix shows the shortest distances between every pair of vertices\n");
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
    /* Let us create the following weighted graph
            1       2       3       4       5
        1   0       4       2       INF    -5
        2   INF     0       INF     2       8
        3   INF     5       0       INF     INF
        4   3       INF     6       0       INF
        5   INF     INF     INF     6       0
    */
    int graph[V][V] = { {0, 4, 2, INF, -5},
                        {INF, 0, INF, 2, 8},
                        {INF, 5, 0, INF, INF},
                        {3, INF, 6, 0, INF},
                        {INF, INF, INF, 6, 0} };

    floydWarshall(graph);
    return 0;
}
