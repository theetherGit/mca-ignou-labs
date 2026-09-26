use std::cmp::Ordering;
use std::collections::BinaryHeap;

#[derive(Debug)]
struct Node {
    freq: usize,
    ch: Option<char>,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

// Implement Ord for BinaryHeap (defaults to max-heap)
// We reverse comparison to simulate a min-heap based on frequency
impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        self.freq == other.freq
    }
}
impl Eq for Node {}
impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(other.freq.cmp(&self.freq)) // Reverse order
    }
}
impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.freq.cmp(&self.freq)
    }
}

fn build_tree(freqs: &[(char, usize)]) -> Box<Node> {
    let mut heap = BinaryHeap::new();
    for &(ch, f) in freqs {
        heap.push(Box::new(Node {
            freq: f,
            ch: Some(ch),
            left: None,
            right: None,
        }));
    }

    while heap.len() > 1 {
        let left = heap.pop().unwrap();
        let right = heap.pop().unwrap();
        heap.push(Box::new(Node {
            freq: left.freq + right.freq,
            ch: None,
            left: Some(left),
            right: Some(right),
        }));
    }
    heap.pop().unwrap()
}

fn generate_codes(node: &Box<Node>, current: &str, codes: &mut Vec<(char, String)>) {
    if let Some(ch) = node.ch {
        codes.push((ch, current.to_string()));
        return;
    }
    if let Some(ref left) = node.left {
        generate_codes(left, &format!("{}0", current), codes);
    }
    if let Some(ref right) = node.right {
        generate_codes(right, &format!("{}1", current), codes);
    }
}

fn main() {
    let freqs = [
        ('A', 15),
        ('B', 25),
        ('C', 5),
        ('D', 7),
        ('E', 10),
        ('F', 13),
        ('G', 9),
    ];
    let root = build_tree(&freqs);

    let mut codes: Vec<(char, String)> = Vec::new();
    generate_codes(&root, "", &mut codes);
    codes.sort_by_key(|c| c.0); // Sort alphabetically for clean output

    let total_freq: usize = freqs.iter().map(|(_, f)| f).sum();
    let total_bits: usize = codes
        .iter()
        .map(|(ch, code)| {
            let f = freqs.iter().find(|(c, _)| *c == *ch).unwrap().1;
            f * code.len()
        })
        .sum();

    println!("Huffman Codes:");
    for (ch, code) in &codes {
        println!("{}: {}", ch, code);
    }
    println!(
        "\nAverage bits per character: {:.2}",
        total_bits as f64 / total_freq as f64
    );
}
