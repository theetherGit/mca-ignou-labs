use std::cmp::Reverse;
use std::collections::BinaryHeap;

#[derive(Eq, PartialEq)]
struct Node {
    freq: i32,
    char: Option<char>,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.freq.cmp(&other.freq)
    }
}
impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

fn traverse(node: &Node, code: String) {
    if let Some(c) = node.char {
        println!("{:<7} | {:<7} | {}", c, node.freq, code);
    } else {
        if let Some(ref l) = node.left {
            traverse(l, code.clone() + "0");
        }
        if let Some(ref r) = node.right {
            traverse(r, code + "1");
        }
    }
}

fn main() {
    let mut heap = BinaryHeap::new();
    let items = vec![
        ('A', 10),
        ('B', 7),
        ('I', 15),
        ('M', 8),
        ('S', 10),
        ('X', 5),
        ('Z', 2),
    ];

    for (c, f) in items {
        heap.push(Reverse(Node {
            freq: f,
            char: Some(c),
            left: None,
            right: None,
        }));
    }

    println!("--- MERGING STEPS ---");
    while heap.len() > 1 {
        let Reverse(n1) = heap.pop().unwrap();
        let Reverse(n2) = heap.pop().unwrap();
        let parent = Node {
            freq: n1.freq + n2.freq,
            char: None,
            left: Some(Box::new(n1)),
            right: Some(Box::new(n2)),
        };
        println!(
            "Merged: {} + {} = {}",
            parent.left.as_ref().unwrap().freq,
            parent.right.as_ref().unwrap().freq,
            parent.freq
        );
        heap.push(Reverse(parent));
    }

    let Reverse(root) = heap.pop().unwrap();
    println!(
        "\n--- FINAL TABLE ---\n{:<7} | {:<7} | {}",
        "Letter", "Freq", "Code"
    );
    println!("-----------------------------");
    traverse(&root, "".to_string());
}
