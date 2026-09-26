# Number of vertices in the graph
V = 5


def floydWarshall(graph):
    """
    Implements the Floyd-Warshall algorithm to find all pairs shortest paths.
    """
    # dist[][] will be the output matrix that will finally have the shortest
    # distances between every pair of vertices.
    # We create a deep copy to avoid modifying the original graph structure.
    dist = [row[:] for row in graph]

    # Add all vertices one by one to the set of intermediate vertices.
    # k is the intermediate vertex
    for k in range(V):
        # i is the source vertex
        for i in range(V):
            # j is the destination vertex
            for j in range(V):
                # If vertex k is on the shortest path from i to j,
                # then update the value of dist[i][j]
                # We check if dist[i][k] and dist[k][j] are not infinity
                if dist[i][k] != float("inf") and dist[k][j] != float("inf"):
                    if dist[i][k] + dist[k][j] < dist[i][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]

    print("Shortest distance matrix (D5):")
    for i in range(V):
        for j in range(V):
            if dist[i][j] == float("inf"):
                print("%7s" % ("INF"), end=" ")
            else:
                print("%7d" % (dist[i][j]), end=" ")
        print()


# Driver program to test the above program
# Mapping: V1->0, V2->1, V3->2, V4->3, V5->4
graph = [
    [0, 3, float("inf"), float("inf"), 9],
    [4, 0, 15, 5, float("inf")],
    [float("inf"), float("inf"), 0, float("inf"), float("inf")],
    [float("inf"), 7, 5, 0, float("inf")],
    [float("inf"), float("inf"), 16, 8, 0],
]

floydWarshall(graph)
