/*
 * Dijkstra's Algorithm Implementation in Rust
 * Finds shortest path from source to all vertices
 *
 * Compilation: rustc -o dijkstra dijkstra.rs
 * Execution: ./dijkstra
 */

use std::cmp::Ordering;
use std::collections::{BinaryHeap, HashMap, HashSet};

// Structure to represent an edge
#[derive(Debug, Clone)]
struct Edge {
    to: char,
    weight: i32,
}

// Structure for priority queue
#[derive(Debug, Eq, PartialEq)]
struct QueueItem {
    distance: i32,
    vertex: char,
}

// Implement ordering for min-heap
impl Ord for QueueItem {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .distance
            .cmp(&self.distance)
            .then_with(|| self.vertex.cmp(&other.vertex))
    }
}

impl PartialOrd for QueueItem {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

// Graph structure
struct Graph {
    adjacency_list: HashMap<char, Vec<Edge>>,
    vertices: Vec<char>,
}

impl Graph {
    fn new() -> Self {
        Graph {
            adjacency_list: HashMap::new(),
            vertices: vec!['A', 'B', 'C', 'D', 'E', 'F', 'G'],
        }
    }

    fn add_edge(&mut self, from: char, to: char, weight: i32) {
        self.adjacency_list
            .entry(from)
            .or_insert_with(Vec::new)
            .push(Edge { to, weight });
    }

    fn dijkstra(&self, source: char) -> (HashMap<char, i32>, HashMap<char, Option<char>>) {
        let mut distances: HashMap<char, i32> =
            self.vertices.iter().map(|&v| (v, i32::MAX)).collect();

        let mut previous: HashMap<char, Option<char>> =
            self.vertices.iter().map(|&v| (v, None)).collect();

        let mut visited: HashSet<char> = HashSet::new();
        let mut heap = BinaryHeap::new();

        *distances.get_mut(&source).unwrap() = 0;
        heap.push(QueueItem {
            distance: 0,
            vertex: source,
        });

        println!("\n{}", "=".repeat(70));
        println!("DIJKSTRA'S ALGORITHM - Source: {}", source);
        println!("{}", "=".repeat(70));

        let mut iteration = 0;

        while let Some(QueueItem {
            distance: current_dist,
            vertex: current_vertex,
        }) = heap.pop()
        {
            if visited.contains(&current_vertex) {
                continue;
            }

            visited.insert(current_vertex);
            iteration += 1;

            println!(
                "\nIteration {}: Processing vertex {} (distance: {})",
                iteration, current_vertex, current_dist
            );

            if let Some(edges) = self.adjacency_list.get(&current_vertex) {
                for edge in edges {
                    if !visited.contains(&edge.to) {
                        let new_distance = current_dist + edge.weight;

                        if new_distance < *distances.get(&edge.to).unwrap() {
                            *distances.get_mut(&edge.to).unwrap() = new_distance;
                            *previous.get_mut(&edge.to).unwrap() = Some(current_vertex);
                            heap.push(QueueItem {
                                distance: new_distance,
                                vertex: edge.to,
                            });
                            println!("  Updated {}: distance = {}", edge.to, new_distance);
                        }
                    }
                }
            }
        }

        // Print results
        println!("\n{}", "=".repeat(70));
        println!("FINAL RESULTS:");
        println!("{}", "=".repeat(70));

        for &vertex in &self.vertices {
            print!("Distance from {} to {}: ", source, vertex);
            let dist = *distances.get(&vertex).unwrap();
            if dist == i32::MAX {
                println!("∞ (unreachable)");
            } else {
                println!("{}", dist);
            }
        }

        (distances, previous)
    }
}

fn main() {
    let mut graph = Graph::new();

    // Add edges
    graph.add_edge('A', 'B', 6);
    graph.add_edge('A', 'G', 4);
    graph.add_edge('B', 'C', 2);
    graph.add_edge('B', 'D', 4);
    graph.add_edge('C', 'D', 2);
    graph.add_edge('G', 'D', 8);
    graph.add_edge('G', 'F', 8);
    graph.add_edge('D', 'F', 2);
    graph.add_edge('D', 'E', 1);
    graph.add_edge('F', 'A', 3);
    graph.add_edge('F', 'E', 7);

    // Q1: From A
    println!("\n{}", "#".repeat(70));
    println!("# Q1: SHORTEST PATH FROM A TO ALL VERTICES");
    println!("{}", "#".repeat(70));
    graph.dijkstra('A');

    // Q2: From B
    println!("\n\n{}", "#".repeat(70));
    println!("# Q2: SHORTEST PATH FROM B TO ALL VERTICES");
    println!("{}", "#".repeat(70));
    graph.dijkstra('B');
}
