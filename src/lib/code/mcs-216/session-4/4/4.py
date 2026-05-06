import heapq
from collections import defaultdict

class Node:
    """Huffman Tree Node"""
    def __init__(self, freq, char=None):
        self.freq = freq
        self.char = char  # None for internal nodes
        self.left = None
        self.right = None

    def __lt__(self, other):
        """Enable comparison for heapq (min-heap by frequency)"""
        return self.freq < other.freq

def build_huffman_tree(freq_dict):
    """Build Huffman tree using priority queue (min-heap)"""
    heap = [Node(f, c) for c, f in freq_dict.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        # Extract two smallest frequency nodes
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)

        # Create merged internal node
        merged = Node(left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    return heap[0] if heap else None

def generate_codes(node, current_code="", codes=None):
    """DFS traversal to assign binary codes (0=left, 1=right)"""
    if codes is None:
        codes = {}
    if node is None:
        return codes
    if node.char is not None:  # Leaf node
        codes[node.char] = current_code
        return codes
    generate_codes(node.left, current_code + "0", codes)
    generate_codes(node.right, current_code + "1", codes)
    return codes

def calculate_avg_bits(codes, freq_dict):
    """Calculate weighted average bits per character"""
    total_bits = sum(freq_dict[c] * len(codes[c]) for c in codes)
    total_freq = sum(freq_dict.values())
    return total_bits / total_freq

def main():
    # Input frequencies
    freq = {
        ':': 80, ' ': 500, '\n': 110, ',': 500,
        '0': 300, '1': 200, '2': 150, '3': 60,
        '4': 180, '5': 240, '6': 170, '7': 200, '8': 202
    }

    # Build tree and generate codes
    root = build_huffman_tree(freq)
    codes = generate_codes(root)

    # Display results
    print("Huffman Codes:")
    for char in sorted(codes.keys(), key=lambda c: freq[c], reverse=True):
        display = repr(char) if char in [' ', '\n', ':', ','] else char
        print(f"{display:>6} (freq={freq[char]:4d}): {codes[char]}")

    avg = calculate_avg_bits(codes, freq)
    print(f"\nAverage bits per character: {avg:.2f}")
    print(f"Total frequency: {sum(freq.values())}")
    print(f"Total bits for encoded file: {sum(freq[c]*len(codes[c]) for c in codes)}")

if __name__ == "__main__":
    main()
