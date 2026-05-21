const V: usize = 5;
const INF: i32 = 999999;

fn floyd_warshall(graph: &[[i32; V]; V]) {
    // Create a mutable copy of the graph to store distances
    let mut dist = *graph;

    // k is the intermediate vertex
    for k in 0..V {
        // i is the source vertex
        for i in 0..V {
            // j is the destination vertex
            for j in 0..V {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                // We check for INF to prevent overflow, though with these values it's unlikely
                if dist[i][k] != INF && dist[k][j] != INF {
                    if dist[i][k] + dist[k][j] < dist[i][j] {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    println!("The following matrix shows the shortest distances between every pair of vertices:");
    for i in 0..V {
        for j in 0..V {
            if dist[i][j] == INF {
                print!("{:>7} ", "INF");
            } else {
                print!("{:>7} ", dist[i][j]);
            }
        }
        println!();
    }
}

fn main() {
    /*
       Graph representation (0-indexed):
       Node 1 -> index 0
       Node 2 -> index 1
       ...
    */
    let graph: [[i32; V]; V] = [
        [0, 4, 2, INF, -5],
        [INF, 0, INF, 2, 8],
        [INF, 5, 0, INF, INF],
        [3, INF, 6, 0, INF],
        [INF, INF, INF, 6, 0],
    ];

    floyd_warshall(&graph);
}
