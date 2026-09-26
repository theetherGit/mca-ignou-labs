# Prim's Algorithm for Minimum Cost Spanning Tree

import heapq


class PrimsAlgorithm:
    def __init__(self):
        # Adjacency list: vertex -> [(neighbor, weight), ...]
        self.graph = {}

    def add_edge(self, u, v, w):
        """Add undirected edge between u and v with weight w"""
        self.graph.setdefault(u, []).append((v, w))
        self.graph.setdefault(v, []).append((u, w))

    def prim(self, start_vertex):
        """
        Execute Prim's algorithm from start_vertex.
        Returns: mst_edges, total_cost, step_by_step_log
        """
        mst_edges = []
        total_cost = 0
        visited = set()
        # Min-heap stores: (weight, from_vertex, to_vertex)
        heap = [(0, None, start_vertex)]
        steps = []

        print(f"\n{'=' * 70}")
        print(f"PRIM'S ALGORITHM - Starting Vertex: {start_vertex}")
        print(f"{'=' * 70}")
        print(
            f"{'Step':<4} | {'Added':<5} | {'Edge':<8} | {'Weight':<6} | {'Cumulative Cost':<15} | {'MST Edges'}"
        )
        print(f"{'-' * 70}")

        while heap and len(visited) < len(self.graph):
            weight, frm, to = heapq.heappop(heap)

            # Skip if already included in MST
            if to in visited:
                continue

            visited.add(to)
            if frm is not None:
                mst_edges.append((frm, to, weight))
                total_cost += weight

                # Log this step
                step_info = {
                    "step": len(steps) + 1,
                    "added": to,
                    "edge": f"{frm}-{to}",
                    "weight": weight,
                    "cost": total_cost,
                    "edges": list(mst_edges),
                }
                steps.append(step_info)

                # Print formatted row
                edge_str = ", ".join([f"{u}-{v}" for u, v, _ in mst_edges])
                print(
                    f"{step_info['step']:<4} | {to:<5} | {step_info['edge']:<8} | {weight:<6} | {total_cost:<15} | {edge_str}"
                )

            # Explore neighbors
            for neighbor, w in self.graph.get(to, []):
                if neighbor not in visited:
                    heapq.heappush(heap, (w, to, neighbor))

        print(f"\n{'=' * 70}")
        print(f"TOTAL MINIMUM COST: {total_cost}")
        print(f"{'=' * 70}")
        return mst_edges, total_cost, steps


def main():
    prims = PrimsAlgorithm()

    # Build the exact graph from the problem image
    edges = [
        ("V1", "V2", 35),
        ("V1", "V4", 20),
        ("V2", "V4", 10),
        ("V2", "V5", 50),
        ("V3", "V4", 22),
        ("V3", "V7", 8),
        ("V4", "V5", 12),
        ("V4", "V8", 5),
        ("V5", "V6", 30),
        ("V5", "V9", 30),
        ("V6", "V10", 9),
        ("V7", "V8", 60),
        ("V8", "V9", 8),
        ("V9", "V10", 16),
    ]

    for u, v, w in edges:
        prims.add_edge(u, v, w)

    # Run Prim's starting from V1
    prims.prim("V1")


if __name__ == "__main__":
    main()
