---
title: Session 4
description: Huffman's Coding Algorithm
section: MCS-216 Section 1
---

<script>
  import {Callout} from "@ethercorps/kit"
  import BinocularsIcon from "phosphor-svelte/lib/BinocularsIcon"
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />


**Huffman Coding** is a popular **greedy algorithm** used for *8*. It is particularly effective for sequences where certain characters appear more frequently than others.

<Callout type="note">
    <!-- Space here -->
    Compression is a technique used to reduce the overall size of data, making storage and transmission more efficient.
    <!-- Space here -->
</Callout>

#### How the Algorithm Works

The core idea behind Huffman Coding is to assign variable-length binary codes to characters based on their frequency:
- **Frequency Analysis**: The algorithm counts how many times each character occurs in the dataset.
- **Tree Construction**: It builds a binary tree (the **Huffman Tree**) from the bottom up, starting with the least frequent characters.
- **Binary Encoding**: In this tree, more frequent characters are placed closer to the root, resulting in shorter binary strings. Conversely, rarer characters receive longer codes.

#### Key Benefits

- **Significant Reduction**: Huffman algorithms can typically compress data size by 70–80%, depending on the redundancy of the source material.
- **Optimal Prefix Codes**: It ensures that no code is a prefix of another, which prevents ambiguity during the decompression (decoding) process.
- *Efficiency*: By utilizing a greedy approach, the algorithm consistently finds the most mathematically optimal way to represent characters as binary strings for a given frequency set.

## Objective

The main objectives of this session are to:
- Implement Huffman’s Coding algorithm.
- Test the implementation on different problem instances
- Construct the optimal binary prefix code

## Question 1

### Problem Statement

Apply Huffman’s algorithm to construct an optimal binary prefix code for the letters and its frequencies in the following table.

| Letters | A | B | I | M | S | X | Z|
|----------|---|---|---|---|---|---|---|
| Frequency | 10 | 7 | 15 | 8 | 10 | 5 | 2 |

Show the complete steps.

### Explanation

Using your data: A(10), B(7), I(15), M(8), S(10), X(5), Z(2).

- **Initialize**: Create a leaf node for each character.
- **Merge (Greedy Step)**: Pick the two smallest: `Z(2)` and `X(5)`.
  - **Create** a parent node with frequency `2 + 5 = 7`.
- **Repeat**: Now pick the next two smallest from the remaining list. This continues until only one node (the **Root**) remains.
- **Assign Bits**: Starting from the Root, assign `0` to every left branch and `1` to every right branch.

### Implementation

### Python
```python title="huffman.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/1/1.py 

```

### C Language
```c title="huffman.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/1/1.c 

```

### Rust
```rust title="huffman.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/1/1.rs

```

### Sample Output

```sh
--- STEP-BY-STEP MERGING (GREEDY STEPS) ---
Step 1: Merged Z(2) and X(5) -> New Node(7)
Step 2: Merged B(7) and Node(7) -> New Node(14)
Step 3: Merged M(8) and A(10) -> New Node(18)
Step 4: Merged S(10) and Node(14) -> New Node(24)
Step 5: Merged I(15) and Node(18) -> New Node(33)
Step 6: Merged Node(24) and Node(33) -> New Node(57)

--- FINAL OPTIMAL BINARY PREFIX CODES ---
Letter     | Frequency  | Huffman Code
----------------------------------------
A          | 10         | 111
B          | 7          | 010
I          | 15         | 10
M          | 8          | 110
S          | 10         | 00
X          | 5          | 0111
Z          | 2          | 0110
```

## Question 2

### Problem Statement

Implement Huffman's coding algorithm and run it on the problem instance of Q1.

### Implementation

<Callout type="note" icon={BinocularsIcon} title="Implementation">
    <!-- Space here -->
    Refer to Question 1, Implementation. It's the proper solution for this question.
    <!-- Space here -->
</Callout>

## Question 3

### Problem Statement

What is an optimal binary tree and Huffman code for the following set of frequencies? Find out the average number of bits required per character. Show complete steps.

A:15 B:25 C:5 D:7 E:10 F:13 G:9

### Initial Frequencies - Sorted

| Char | C | D | G | E | F | A | B |
|------|---|---|---|---|---|---|---|
| Freq | 5 | 7 | 9 | 10 | 13 | 15 | 25 |

#### Total Frequency = `84`

### Huffman Tree

| Step | Nodes in Pool (Sorted) | Merged Nodes | New Node |
|------|------------------------|--------------|----------|
| 1 | C:5, D:7, G:9, E:10, F:13, A:15, B:25 | C(5) + D(7) | N1:12 |
| 2 | N1:12, G:9, E:10, F:13, A:15, B:25 → Sort: G:9, E:10, N1:12... | G(9) + E(10) | N2:19 |
| 3 | N1:12, F:13, A:15, N2:19, B:25 | N1(12)+F(13) | N3:25 |
| 4 | A:15, N2:19, N3:25, B:25 | A(15)+N2(19) | N4:34 |
| 5 | N3:25, B:25, N4:34 | N3(25)+B(25) | N5:50 |
| 6 | N4:34, N5:50 | N4(34)+N5(50) | Root:84 |

### Assigning Codes

Convention: `0` = Left Child, `1` = Right Child

```sh
Root(84)
 ├─ 0 → N4(34)
 │    ├─ 0 → A(15)   → 00
 │    └─ 1 → N2(19)
 │         ├─ 0 → G(9)  → 010
 │         └─ 1 → E(10) → 011
 └─ 1 → N5(50)
      ├─ 0 → N3(25)
      │    ├─ 0 → N1(12)
      │    │    ├─ 0 → C(5)  → 1000
      │    │    └─ 1 → D(7)  → 1001
      │    └─ 1 → F(13) → 101
      └─ 1 → B(25)   → 11
```

### Huffman Codes

| Char | Frequency | Code | Length |
|------|-----------|------|--------|
| A | 15 | 00 | 2 |
| B | 25 | 11 | 2 |
| C | 5 | 1000 | 4 |
| D | 7 | 1001 | 4 |
| E | 10 | 011 | 3 |
| F | 13 | 101 | 3 |
| G | 9 | 010 | 3 |

### Bits/Character

```sh
Total Bits = Σ (Frequency × Code Length)
           = (15×2) + (25×2) + (5×4) + (7×4) + (10×3) + (13×3) + (9×3)
           = 30 + 50 + 20 + 28 + 30 + 39 + 27 = 224

Average Bits = Total Bits / Total Frequency
             = 224 / 84 ≈ 2.67 bits/character
```

### Implementations

### Python
```python title="huffman.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/3/3.py 

```

### C Language
```c title="huffman.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/3/3.c 

```

### Rust
```rust title="huffman.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/3/3.rs

```

### Sample Output

```sh
Huffman Codes:
A: 00
B: 11
C: 1000
D: 1001
E: 011
F: 101
G: 010

Average bits per character: 2.67
```

## Question 4

### Problem Statement

A file contains only colon, spaces, new line character and digits in the following frequency:
colon(80), space(500), new line(110), commas(500), 0(300), 1(200), 2(150), 3(60), 4(180), 5(240), 6(170), 7(200), 8(202).

Using the Huffman’s algorithm to construct an optimal binary prefix code.

### Frequencies - Sorted

| Char | Frequency |
|------|-----------|
| 3 | 60 |
| colon | 80 |
| new line | 110 |
| 2 | 150 |
| 6 | 170 |
| 4 | 180 |
| 1 | 200 |
| 7 | 200 |
| 8 | 202 |
| 5 | 240 |
| 0 | 300 |
| space | 500 |
| comma | 500 |

#### Total Frequency = `2892`

### Merge Steps

- We are using min-heap approach
- `\n` - New line

| Step | Two Smallest Nodes | Merged Node (Freq) | Pool After Merge (Sorted) |
|------|--------------------|--------------------|---------------------------|
| 1 | 3(60) + colon(80) | N1:140 | \n:110, N1:140, 2:150, 6:170, 4:180, 1:200, 7:200, 8:202, 5:240, 0:300, space:500, comma:500 |
| 2 | \n(110) + N1(140) | N2:250 | 2:150, 6:170, 4:180, 1:200, 7:200, 8:202, 5:240, N2:250, 0:300, space:500, comma:500 |
| 3 | 2(150) + 6(170) | N3:320 | 4:180, 1:200, 7:200, 8:202, 5:240, N2:250, 0:300, N3:320, space:500, comma:500 |
| 4 | 4(180) + 1(200) | N4:380 | 7:200, 8:202, 5:240, N2:250, 0:300, N3:320, N4:380, space:500, comma:500 |
| 5 | 7(200) + 8(202) | N5:402 | 5:240, N2:250, 0:300, N3:320, N4:380, N5:402, space:500, comma:500 |
| 6 | 5(240) + N2(250) | N6:490 | 0:300, N3:320, N4:380, N5:402, N6:490, space:500, comma:500 |
| 7 | 0(300) + N3(320) | N7:620 | N4:380, N5:402, N6:490, N7:620, space:500, comma:500 |
| 8 | N4(380) + N5(402) | N8:782 | N6:490, N7:620, N8:782, space:500, comma:500 |
| 9 | N6(490) + space(500) | N9:990 | N7:620, N8:782, N9:990, comma:500 |
| 10 | comma(500) + N7(620) | N10:1120 | N8:782, N9:990, N10:1120 |
| 11 | N8(782) + N9(990) | N11:1772 | N10:1120, N11:1772 | 
| 12 | N10(1120) + N11(1772) | Root:2892 | Tree Complete |

### Tree

```sh
Root(2892)
 ├─ 0 → N10(1120)
 │    ├─ 0 → comma(500)           → 00
 │    └─ 1 → N7(620)
 │         ├─ 0 → 0(300)          → 010
 │         └─ 1 → N3(320)
 │              ├─ 0 → 2(150)     → 0110
 │              └─ 1 → 6(170)     → 0111
 └─ 1 → N11(1772)
      ├─ 0 → N8(782)
      │    ├─ 0 → N4(380)
      │    │    ├─ 0 → 4(180)    → 1000
      │    │    └─ 1 → 1(200)    → 1001
      │    └─ 1 → N5(402)
      │         ├─ 0 → 7(200)    → 1010
      │         └─ 1 → 8(202)    → 1011
      └─ 1 → N9(990)
           ├─ 0 → N6(490)
           │    ├─ 0 → 5(240)    → 1100
           │    └─ 1 → N2(250)
           │         ├─ 0 → \n(110)  → 11010
           │         └─ 1 → N1(140)
           │              ├─ 0 → 3(60)  → 110110
           │              └─ 1 → colon(80) → 110111
           └─ 1 → space(500)    → 111
```

### Huffman Codes

| Char | Freq | Code | Length |
|:----:|:----:|:----:|:------:|
| `,` | 500 | 00 | 2 |
| `0` | 300 | 010 | 3 |
| `2` | 150 | 0110 | 4 |
| `6` | 170 | 0111 | 4 |
| `4` | 180 | 1000 |4 |
| `1` | 200 | 1001 | 4 |
| `7` | 200 | 1010 | 4 |
| `8` | 202 | 1011 | 4 |
| `5` | 240 | 1100 | 4 |
| `\n` | 110 | 11010 | 5 |
| `3` | 60 | 110110 | 6 |
| `:` | 80 | 110111 | 6 |
| `space` | 500 | 111 | 3 |

### Bits/Character

```sh
Total Bits = Σ(Frequency × Code Length) 
=> (500×2) + (300×3) + (150×4) + (170×4) + (180×4) + (200×4)  (200×4) + (202×4) + (240×4) + (110×5) + (60×6) + (80×6) + (500×3) 
=> 1000 + 900 + 600 + 680 + 720 + 800 + 800 + 808 + 960 + 550 + 360 + 480 + 1500 
=> 10,158 bits

Average Bits = Total Bits / Total Frequency 
=> 10,158 / 2,892 ≈ 3.51 bits/character
```

### Implementations

### Python
```python title="huffman.py" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/4/4.py 

```

### C Language
```c title="huffman.c" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/4/4.c 

```

### Rust
```rust title="huffman.rs" showLineNumbers file=../../../lib/code/mcs-216/section-1/session-4/4/4.rs

```

### Sample Output

```sh
Huffman Codes:
   ' ' (freq= 764): 00
   ',' (freq= 764): 111
   '0' (freq= 454): 010
   '5' (freq= 360): 1100
   '8' (freq= 312): 1011
   '7' (freq= 310): 1001
   '1' (freq= 310): 1010
   '4' (freq= 264): 1000
   '6' (freq= 252): 0111
   '2' (freq= 226): 0110
  '\n' (freq= 156): 11010
   ':' (freq= 120): 110111
   '3' (freq=  74): 110110

Average bits per character: 3.512448132780083
Total frequency: 2892
Total bits for encoded file: 10158
```
