"""
Dijkstra's Algorithm Implementation
Finds shortest path from source to all other vertices
"""

import heapq
from collections import defaultdict


class DijkstraAlgorithm:
    def __init__(self):
        # Graph represented as adjacency list
        self.graph = defaultdict(list)

    def add_edge(self, u, v, weight):
        """Add directed edge from u to v with given weight"""
        self.graph[u].append((v, weight))

    def dijkstra(self, source, vertices):
        """Dijkstra's algorithm to find shortest paths from source

        Args:
            source: Starting vertex
            vertices: List of all vertices

        Returns:
            distances: Shortest distance from source to each vertex
            previous: Previous vertex in shortest path
            steps: Intermediate steps for visualization
        """
        # Initialize distances to infinity
        distances = {v: float("inf") for v in vertices}
        distances[source] = 0

        # Track previous vertex for path reconstruction
        previous = {v: None for v in vertices}

        # Track visited vertices
        visited = set()

        # Priority queue: (distance, vertex)
        pq = [(0, source)]

        # Store intermediate steps
        steps = []
        iteration = 0

        while pq:
            iteration += 1
            current_dist, current_vertex = heapq.heappop(pq)

            # Skip if already visited
            if current_vertex in visited:
                continue

            # Mark as visited
            visited.add(current_vertex)

            # Record this step
            step = {
                "iteration": iteration,
                "current_vertex": current_vertex,
                "current_distance": current_dist,
                "distances": distances.copy(),
                "visited": visited.copy(),
            }
            steps.append(step)

            # Explore neighbors
            for neighbor, weight in self.graph[current_vertex]:
                if neighbor not in visited:
                    new_distance = current_dist + weight

                    # If shorter path found
                    if new_distance < distances[neighbor]:
                        distances[neighbor] = new_distance
                        previous[neighbor] = current_vertex
                        heapq.heappush(pq, (new_distance, neighbor))

        return distances, previous, steps

    def get_path(self, previous, source, target):
        """Reconstruct path from source to target"""
        path = []
        current = target
        while current is not None:
            path.append(current)
            current = previous[current]
        path.reverse()
        return path if path[0] == source else []


def print_dijkstra_steps(steps, distances, previous, source, vertices):
    """Print detailed step-by-step execution"""
    print("\n" + "=" * 80)
    print(f"DIJKSTRA'S ALGORITHM - Source: {source}")
    print("=" * 80)

    for step in steps:
        print(f"\nIteration {step['iteration']}:")
        print(f"  Current Vertex: {step['current_vertex']}")
        print(f"  Distance to {step['current_vertex']}: {step['current_distance']}")
        print(f"  Visited: {sorted(step['visited'])}")
        print("  Current Distances: ", end="")
        for v in sorted(vertices):
            dist = step["distances"][v]
            if dist == float("inf"):
                print(f"{v}=∞ ", end="")
            else:
                print(f"{v}={dist} ", end="")
        print()

    print("\n" + "=" * 80)
    print("FINAL RESULTS:")
    print("=" * 80)
    for v in sorted(vertices):
        dist = distances[v]
        if dist == float("inf"):
            print(f"Distance from {source} to {v}: ∞ (unreachable)")
        else:
            path = []
            current = v
            while current is not None:
                path.append(current)
                current = previous[current]
            path.reverse()
            path_str = " → ".join(path)
            print(f"Distance from {source} to {v}: {dist} | Path: {path_str}")


if __name__ == "__main__":
    # Create graph instance
    dijkstra = DijkstraAlgorithm()

    # Define all vertices
    vertices = ["A", "B", "C", "D", "E", "F", "G"]

    # Add edges (original graph)
    dijkstra.add_edge("A", "B", 6)
    dijkstra.add_edge("A", "G", 4)
    dijkstra.add_edge("B", "C", 2)
    dijkstra.add_edge("B", "D", 4)
    dijkstra.add_edge("C", "D", 2)
    dijkstra.add_edge("G", "D", 8)
    dijkstra.add_edge("G", "F", 8)
    dijkstra.add_edge("D", "F", 2)
    dijkstra.add_edge("D", "E", 1)
    dijkstra.add_edge("F", "A", 3)
    dijkstra.add_edge("F", "E", 7)

    # =========================================================================
    # Q1: Shortest path from A to rest of vertices
    # =========================================================================
    print("\n" + "#" * 80)
    print("# Q1: SHORTEST PATH FROM A TO ALL VERTICES")
    print("#" * 80)

    distances_A, previous_A, steps_A = dijkstra.dijkstra("A", vertices)
    print_dijkstra_steps(steps_A, distances_A, previous_A, "A", vertices)

    # =========================================================================
    # Q2: Shortest path from B to rest of vertices
    # =========================================================================
    print("\n\n" + "#" * 80)
    print("# Q2: SHORTEST PATH FROM B TO ALL VERTICES")
    print("#" * 80)

    # Create new graph for source B
    dijkstra_B = DijkstraAlgorithm()
    dijkstra_B.add_edge("A", "B", 6)
    dijkstra_B.add_edge("A", "G", 4)
    dijkstra_B.add_edge("B", "C", 2)
    dijkstra_B.add_edge("B", "D", 4)
    dijkstra_B.add_edge("C", "D", 2)
    dijkstra_B.add_edge("G", "D", 8)
    dijkstra_B.add_edge("G", "F", 8)
    dijkstra_B.add_edge("D", "F", 2)
    dijkstra_B.add_edge("D", "E", 1)
    dijkstra_B.add_edge("F", "A", 3)
    dijkstra_B.add_edge("F", "E", 7)

    distances_B, previous_B, steps_B = dijkstra_B.dijkstra("B", vertices)
    print_dijkstra_steps(steps_B, distances_B, previous_B, "B", vertices)

    # =========================================================================
    # Q3: Graph with negative weights (G→F = -8, F→A = -3)
    # =========================================================================
    print("\n\n" + "#" * 80)
    print("# Q3: SHORTEST PATH FROM A WITH NEGATIVE WEIGHTS")
    print("# Note: Dijkstra's algorithm DOES NOT WORK with negative weights!")
    print("# We'll show why it fails and use Bellman-Ford instead")
    print("#" * 80)

    # Show Dijkstra failure
    dijkstra_neg = DijkstraAlgorithm()
    dijkstra_neg.add_edge("A", "B", 6)
    dijkstra_neg.add_edge("A", "G", 4)
    dijkstra_neg.add_edge("B", "C", 2)
    dijkstra_neg.add_edge("B", "D", 4)
    dijkstra_neg.add_edge("C", "D", 2)
    dijkstra_neg.add_edge("G", "D", 8)
    dijkstra_neg.add_edge("G", "F", -8)  # NEGATIVE WEIGHT
    dijkstra_neg.add_edge("D", "F", 2)
    dijkstra_neg.add_edge("D", "E", 1)
    dijkstra_neg.add_edge("F", "A", -3)  # NEGATIVE WEIGHT
    dijkstra_neg.add_edge("F", "E", 7)

    print("\n⚠️  PROBLEM: Dijkstra's algorithm fails with negative weights!")
    print("   Reason: Once a vertex is marked 'visited', Dijkstra assumes")
    print("   the shortest path is found. But negative edges can create")
    print("   shorter paths later, which Dijkstra will miss.")

    # Implement Bellman-Ford for negative weights
    def bellman_ford(graph, source, vertices):
        """Bellman-Ford algorithm that handles negative weights"""
        distances = {v: float("inf") for v in vertices}
        distances[source] = 0
        previous = {v: None for v in vertices}

        # Relax all edges |V| - 1 times
        for i in range(len(vertices) - 1):
            updated = False
            for u in vertices:
                # Only check paths if u itself is reachable
                if u in graph and distances[u] != float("inf"):
                    for v, weight in graph[u]:
                        if distances[u] + weight < distances[v]:
                            distances[v] = distances[u] + weight
                            previous[v] = u
                            updated = True
            if not updated:
                break

        # Check for negative weight cycles
        for u in vertices:
            if u in graph and distances[u] != float("inf"):
                for v, weight in graph[u]:
                    if distances[u] + weight < distances[v]:
                        print(
                            "\n⚠️  CRITICAL ERROR: Graph contains a negative weight cycle!"
                        )
                        print(
                            "   Shortest paths cannot be accurately found because you can loop infinitely to decrease distance."
                        )
                        return None, None

        return distances, previous

    # Build graph for Bellman-Ford
    graph_neg = defaultdict(list)
    graph_neg["A"] = [("B", 6), ("G", 4)]
    graph_neg["B"] = [("C", 2), ("D", 4)]
    graph_neg["C"] = [("D", 2)]
    graph_neg["G"] = [("D", 8), ("F", -8)]
    graph_neg["D"] = [("F", 2), ("E", 1)]
    graph_neg["F"] = [("A", -3), ("E", 7)]

    distances_neg, previous_neg = bellman_ford(graph_neg, "A", vertices)

    print("\n" + "=" * 80)
    print("BELLMAN-FORD ALGORITHM (Handles Negative Weights)")
    print("=" * 80)

    if distances_neg is None:
        print("Could not calculate final paths due to the negative weight cycle.")
    else:
        for v in sorted(vertices):
            dist = distances_neg[v]
            if dist == float("inf"):
                print(f"Distance from A to {v}: ∞ (unreachable)")
            else:
                path = []
                current = v
                visited_in_path = set()
                while current is not None and current not in visited_in_path:
                    path.append(current)
                    visited_in_path.add(current)
                    current = previous_neg[current]
                    if len(path) > len(vertices):  # Safety check
                        break
                path.reverse()
                if path and path[0] == "A":
                    path_str = " → ".join(path)
                    print(f"Distance from A to {v}: {dist} | Path: {path_str}")
                else:
                    print(f"Distance from A to {v}: {dist} | Path: (cycle detected)")
