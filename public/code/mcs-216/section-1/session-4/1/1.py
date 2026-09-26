import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def solve_huffman():
    # 1. Initialize data from the problem table
    data = {'A': 10, 'B': 7, 'I': 15, 'M': 8, 'S': 10, 'X': 5, 'Z': 2}
    heap = [Node(c, f) for c, f in data.items()]
    heapq.heapify(heap)

    print("--- STEP-BY-STEP MERGING (GREEDY STEPS) ---")
    step = 1
    while len(heap) > 1:
        # Extract two smallest frequencies
        n1 = heapq.heappop(heap)
        n2 = heapq.heappop(heap)

        # Merge them
        merged = Node(None, n1.freq + n2.freq)
        merged.left = n1
        merged.right = n2

        print(f"Step {step}: Merged {n1.char or 'Node'}({n1.freq}) and "
              f"{n2.char or 'Node'}({n2.freq}) -> New Node({merged.freq})")

        heapq.heappush(heap, merged)
        step += 1

    # 2. Generate Codes and Print Table
    root = heap[0]
    codes = {}

    def generate_codes(node, current_code):
        if node:
            if node.char:
                codes[node.char] = current_code
            generate_codes(node.left, current_code + "0")
            generate_codes(node.right, current_code + "1")

    generate_codes(root, "")

    print("\n--- FINAL OPTIMAL BINARY PREFIX CODES ---")
    print(f"{'Letter':<10} | {'Frequency':<10} | {'Huffman Code':<15}")
    print("-" * 40)
    for char in sorted(data.keys()):
        print(f"{char:<10} | {data[char]:<10} | {codes[char]:<15}")

solve_huffman()
