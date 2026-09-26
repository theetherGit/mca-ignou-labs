# Number of vertices in the graph
V = 5

# Define infinity as a large enough value.
INF = 99999


def floydWarshall(graph):
    """
    Implements the Floyd-Warshall algorithm to find all pairs shortest paths.
    """
    # dist[][] will be the output matrix that will finally have the shortest
    # distances between every pair of vertices
    dist = list(map(lambda i: list(map(lambda j: j, i)), graph))

    # Add all vertices one by one to the set of intermediate vertices.
    # k is the intermediate vertex
    for k in range(V):
        # i is the source vertex
        for i in range(V):
            # j is the destination vertex
            for j in range(V):
                # If vertex k is on the shortest path from i to j,
                # then update the value of dist[i][j]
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    print("Shortest distance matrix (D5):")
    for i in range(V):
        for j in range(V):
            if dist[i][j] == INF:
                print("%7s" % ("INF"), end=" ")
            else:
                print("%7d" % (dist[i][j]), end=" ")
        print()


# Driver program to test the above program
# Mapping: V1->0, V2->1, V3->2, V4->3, V5->4
graph = [
    [0, 3, INF, INF, 9],
    [4, 0, 15, 5, INF],
    [INF, INF, 0, INF, INF],
    [INF, 7, 5, 0, INF],
    [INF, INF, 16, 8, 0],
]

floydWarshall(graph)
