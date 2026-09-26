import heapq

class Node:
    def __init__(self, freq, char=None):
        self.freq = freq
        self.char = char
        self.left = None
        self.right = None

    # Required for heapq to compare nodes by frequency
    def __lt__(self, other):
        return self.freq < other.freq

def build_huffman_tree(freq_dict):
    """Builds Huffman Tree using a Min-Heap"""
    heap = [Node(f, c) for c, f in freq_dict.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = Node(left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    return heap[0] if heap else None

def generate_codes(root, current_code="", codes=None):
    """DFS traversal to assign 0/1 codes"""
    if codes is None:
        codes = {}
    if root is None:
        return
    if root.char is not None:  # Leaf node
        codes[root.char] = current_code
        return
    generate_codes(root.left, current_code + "0", codes)
    generate_codes(root.right, current_code + "1", codes)
    return codes

def main():
    freq = {'A': 15, 'B': 25, 'C': 5, 'D': 7, 'E': 10, 'F': 13, 'G': 9}
    root = build_huffman_tree(freq)
    codes = generate_codes(root)

    # Calculate average bits
    total_bits = sum(freq[c] * len(codes[c]) for c in codes)
    total_freq = sum(freq.values())
    avg_bits = total_bits / total_freq

    print("Huffman Codes:")
    for char in sorted(codes.keys()):
        print(f"{char}: {codes[char]}")
    print(f"\nAverage bits per character: {avg_bits:.2f}")

if __name__ == "__main__":
    main()
