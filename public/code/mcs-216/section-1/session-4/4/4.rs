use std::cmp::Ordering;
use std::collections::BinaryHeap;

// Huffman Tree Node
#[derive(Debug)]
struct Node {
    freq: usize,
    ch: Option<char>,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

// Implement ordering for BinaryHeap (min-heap by frequency)
impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        self.freq == other.freq
    }
}
impl Eq for Node {}
impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        // Reverse for min-heap behavior
        Some(other.freq.cmp(&self.freq))
    }
}
impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.freq.cmp(&self.freq)
    }
}

fn build_tree(freqs: &[(char, usize)]) -> Box<Node> {
    let mut heap = BinaryHeap::new();

    // Push all leaf nodes
    for &(ch, f) in freqs {
        heap.push(Box::new(Node {
            freq: f,
            ch: Some(ch),
            left: None,
            right: None,
        }));
    }

    // Merge nodes until one root remains
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

fn display_char(ch: char) -> String {
    match ch {
        ' ' => "' '".to_string(),
        '\n' => "'\\n'".to_string(),
        ':' => "':'".to_string(),
        ',' => "','".to_string(),
        _ => format!("'{}'", ch),
    }
}

fn main() {
    // Input: (character, frequency) pairs
    let freqs = [
        (':', 80),
        (' ', 500),
        ('\n', 110),
        (',', 500),
        ('0', 300),
        ('1', 200),
        ('2', 150),
        ('3', 60),
        ('4', 180),
        ('5', 240),
        ('6', 170),
        ('7', 200),
        ('8', 202),
    ];

    let root = build_tree(&freqs);
    let mut codes: Vec<(char, String)> = Vec::new();
    generate_codes(&root, "", &mut codes);

    // Sort by frequency (descending) for display
    codes.sort_by(|a, b| {
        let fa = freqs.iter().find(|(c, _)| *c == a.0).unwrap().1;
        let fb = freqs.iter().find(|(c, _)| *c == b.0).unwrap().1;
        fb.cmp(&fa)
    });

    // Calculate statistics
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
        let f = freqs.iter().find(|(c, _)| *c == *ch).unwrap().1;
        println!("{:>6} (freq={:4o}): {}", display_char(*ch), f, code);
    }

    let avg_bits = total_bits as f64 / total_freq as f64;
    println!("\nAverage bits per character: {}", avg_bits);
    println!("Total frequency: {}", total_freq);
    println!("Total bits for encoded file: {}", total_bits);
}
