// Structure representing an edge
#[derive(Debug, Clone, Copy)]
struct Edge {
    src: usize,
    dest: usize,
    weight: i32,
}

// Structure representing the Disjoint-Set (Union-Find)
struct DisjointSet {
    parent: Vec<usize>,
    rank: Vec<usize>,
}

impl DisjointSet {
    // Initialize standard subsets
    fn new(n: usize) -> Self {
        let parent = (0..n).collect();
        let rank = vec![0; n];
        DisjointSet { parent, rank }
    }

    // Find root using path compression technique
    fn find(&mut self, i: usize) -> usize {
        if self.parent[i] != i {
            self.parent[i] = self.find(self.parent[i]);
        }
        self.parent[i]
    }

    // Unify two sets by structural rank
    fn union(&mut self, x: usize, y: usize) {
        let xroot = self.find(x);
        let yroot = self.find(y);

        if self.rank[xroot] < self.rank[yroot] {
            self.parent[xroot] = yroot;
        } else if self.rank[xroot] > self.rank[yroot] {
            self.parent[yroot] = xroot;
        } else {
            self.parent[yroot] = xroot;
            self.rank[xroot] += 1;
        }
    }
}

fn kruskal_mcst(vertices: usize, mut edges: Vec<Edge>) {
    let mut result = Vec::new();
    let mut ds = DisjointSet::new(vertices);

    // Step 1: Sort edges in non-decreasing order of weight
    edges.sort_by_key(|edge| edge.weight);

    // Step 2: Iterate over sorted edges
    for edge in edges {
        let x = ds.find(edge.src);
        let y = ds.find(edge.dest);

        // If roots are distinct, it means adding this edge will not form a cycle
        if x != y {
            result.push(edge);
            ds.union(x, y);
        }

        // Optimization: Stop if we've successfully selected V - 1 edges
        if result.len() == vertices - 1 {
            break;
        }
    }

    // Display execution details
    let mut minimum_cost = 0;
    println!("Edges in the constructed MCST (Rust Implementation):");
    for edge in result {
        println!("V{} -- V{} == {}", edge.src + 1, edge.dest + 1, edge.weight);
        minimum_cost += edge.weight;
    }
    println!("Minimum Spanning Tree Cost: {}", minimum_cost);
}

fn main() {
    let vertices = 10;
    let edges = vec![
        Edge {
            src: 0,
            dest: 1,
            weight: 35,
        },
        Edge {
            src: 0,
            dest: 3,
            weight: 20,
        },
        Edge {
            src: 1,
            dest: 3,
            weight: 10,
        },
        Edge {
            src: 1,
            dest: 4,
            weight: 50,
        },
        Edge {
            src: 2,
            dest: 3,
            weight: 22,
        },
        Edge {
            src: 2,
            dest: 6,
            weight: 8,
        },
        Edge {
            src: 3,
            dest: 4,
            weight: 12,
        },
        Edge {
            src: 3,
            dest: 7,
            weight: 5,
        },
        Edge {
            src: 4,
            dest: 5,
            weight: 30,
        },
        Edge {
            src: 4,
            dest: 8,
            weight: 30,
        },
        Edge {
            src: 5,
            dest: 9,
            weight: 9,
        },
        Edge {
            src: 6,
            dest: 7,
            weight: 60,
        },
        Edge {
            src: 7,
            dest: 8,
            weight: 8,
        },
        Edge {
            src: 8,
            dest: 9,
            weight: 16,
        },
    ];

    kruskal_mcst(vertices, edges);
}
