const V: usize = 5;
const INF: i32 = 999999;

fn floyd_warshall(graph: &[[i32; V]; V]) {
    // Create a mutable copy of the graph to store distances.
    // In Rust, arguments are immutable by default, so we clone it.
    let mut dist = *graph;

    // k is the intermediate vertex
    for k in 0..V {
        // i is the source vertex
        for i in 0..V {
            // j is the destination vertex
            for j in 0..V {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]

                // Check for INF to prevent integer overflow during addition
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
       V1 -> index 0
       V2 -> index 1
       V3 -> index 2
       V4 -> index 3
       V5 -> index 4
    */
    let graph: [[i32; V]; V] = [
        [0, 3, INF, INF, 9],
        [4, 0, 15, 5, INF],
        [INF, INF, 0, INF, INF],
        [INF, 7, 5, 0, INF],
        [INF, INF, 16, 8, 0],
    ];

    floyd_warshall(&graph);
}
