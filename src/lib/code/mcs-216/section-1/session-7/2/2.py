class Graph:
    def __init__(self, vertices):
        self.V = vertices  # Total count of nodes
        self.graph = []  # Default storage array for data streams

    def add_edge(self, u, v, w):
        """Append an un-directed edge configuration containing weight"""
        self.graph.append([u, v, w])

    def find(self, parent, i):
        """Find the root element of element i with path compression technique"""
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        """Perform union of two sets using rank optimization"""
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_mcst(self):
        result = []  # Stores the final built tree
        i, e = (
            0,
            0,
        )  # i: tracking index for sorted edges, e: tracking count for MCST edges

        # Step 1: Sort all edges in non-decreasing order of weight
        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        # Create V individual subset components
        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        # Process elements until the tree contains exactly V-1 components
        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            # If roots are distinct, no cycle is formed. Accept edge.
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        # Print out compiled outputs
        minimum_cost = 0
        print("Edges in the constructed MCST (Python Implementation):")
        for u, v, weight in result:
            minimum_cost += weight
            print(f"V{u + 1} -- V{v + 1} == {weight}")
        print(f"Minimum Spanning Tree Cost: {minimum_cost}")


# Driver execution matching our graph data schema
if __name__ == "__main__":
    g = Graph(10)
    g.add_edge(0, 1, 35)  # V1-V2
    g.add_edge(0, 3, 20)  # V1-V4
    g.add_edge(1, 3, 10)  # V2-V4
    g.add_edge(1, 4, 50)  # V2-V5
    g.add_edge(2, 3, 22)  # V3-V4
    g.add_edge(2, 6, 8)  # V3-V7
    g.add_edge(3, 4, 12)  # V4-V5
    g.add_edge(3, 7, 5)  # V4-V8
    g.add_edge(4, 5, 30)  # V5-V6
    g.add_edge(4, 8, 30)  # V5-V9
    g.add_edge(5, 9, 9)  # V6-V10
    g.add_edge(6, 7, 60)  # V7-V8
    g.add_edge(7, 8, 8)  # V8-V9
    g.add_edge(8, 9, 16)  # V9-V10

    g.kruskal_mcst()
