// Prim's Algorithm for Minimum Cost Spanning Tree
use std::cmp::Ordering;
use std::collections::{BinaryHeap, HashMap, HashSet};

// Structure for priority queue items
#[derive(Debug, Eq, PartialEq)]
struct QueueItem {
    weight: i32,
    from: String,
    to: String,
}

// Implement min-heap ordering
impl Ord for QueueItem {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .weight
            .cmp(&self.weight)
            .then_with(|| self.to.cmp(&other.to))
    }
}

impl PartialOrd for QueueItem {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct PrimsAlgorithm {
    adjacency_list: HashMap<String, Vec<(String, i32)>>,
}

impl PrimsAlgorithm {
    fn new() -> Self {
        PrimsAlgorithm {
            adjacency_list: HashMap::new(),
        }
    }

    fn add_edge(&mut self, u: &str, v: &str, w: i32) {
        self.adjacency_list
            .entry(u.to_string())
            .or_default()
            .push((v.to_string(), w));
        self.adjacency_list
            .entry(v.to_string())
            .or_default()
            .push((u.to_string(), w));
    }

    fn run(&self, start: &str) {
        let mut mst_edges = Vec::new();
        let mut total_cost = 0;
        let mut visited = HashSet::new();
        let mut heap = BinaryHeap::new();

        heap.push(QueueItem {
            weight: 0,
            from: "Root".to_string(),
            to: start.to_string(),
        });

        println!("\n{}", "=".repeat(70));
        println!("PRIM'S ALGORITHM - Starting Vertex: {}", start);
        println!("{}", "=".repeat(70));
        println!(
            "{:<4} | {:<5} | {:<8} | {:<6} | {:<15} | {}",
            "Step", "Added", "Edge", "Weight", "Cumulative Cost", "MST Edges"
        );
        println!("{}", "-".repeat(70));

        let mut step = 0;
        while let Some(item) = heap.pop() {
            if visited.contains(&item.to) {
                continue;
            }

            visited.insert(item.to.clone());

            if item.from != "Root" {
                mst_edges.push((item.from.clone(), item.to.clone(), item.weight));
                total_cost += item.weight;
                step += 1;

                let edge_str: Vec<String> = mst_edges
                    .iter()
                    .map(|(u, v, _)| format!("{}-{}", u, v))
                    .collect();

                println!(
                    "{:<4} | {:<5} | {:<8} | {:<6} | {:<15} | {}",
                    step,
                    item.to,
                    format!("{}-{}", item.from, item.to),
                    item.weight,
                    total_cost,
                    edge_str.join(" ")
                );
            }

            if let Some(neighbors) = self.adjacency_list.get(&item.to) {
                for (neighbor, weight) in neighbors {
                    if !visited.contains(neighbor) {
                        heap.push(QueueItem {
                            weight: *weight,
                            from: item.to.clone(),
                            to: neighbor.clone(),
                        });
                    }
                }
            }
        }

        println!("\n{}", "=".repeat(70));
        println!("TOTAL MINIMUM COST: {}", total_cost);
        println!("{}", "=".repeat(70));
    }
}

fn main() {
    let mut prim = PrimsAlgorithm::new();

    let edges = [
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
    ];

    for &(u, v, w) in &edges {
        prim.add_edge(u, v, w);
    }

    prim.run("V1");
}
