#!/usr/bin/env python3
"""Entropy, information gain, gain ratio and the ID3 tree for weather.nominal (14 rows).
Every number WEKA's Id3 / J48 uses on this data set is printed, then the tree and its
if-then rules, then the kappa statistic from a confusion matrix by hand.
Run: python3 entropy_gain.py
"""
import math
from collections import Counter

ATTRS = ['outlook', 'temperature', 'humidity', 'windy', 'play']
DATA = [r.split(',') for r in """sunny,hot,high,FALSE,no
sunny,hot,high,TRUE,no
overcast,hot,high,FALSE,yes
rainy,mild,high,FALSE,yes
rainy,cool,normal,FALSE,yes
rainy,cool,normal,TRUE,no
overcast,cool,normal,TRUE,yes
sunny,mild,high,FALSE,no
sunny,cool,normal,FALSE,yes
rainy,mild,normal,FALSE,yes
sunny,mild,normal,TRUE,yes
overcast,mild,high,TRUE,yes
overcast,hot,normal,FALSE,yes
rainy,mild,high,TRUE,no""".splitlines()]


def entropy(rows):
    n = len(rows)
    return -sum(c / n * math.log2(c / n) for c in Counter(r[-1] for r in rows).values())


def gain(rows, j):
    parts = {}
    for r in rows:
        parts.setdefault(r[j], []).append(r)
    rem = sum(len(p) / len(rows) * entropy(p) for p in parts.values())
    split = -sum(len(p) / len(rows) * math.log2(len(p) / len(rows)) for p in parts.values())
    return entropy(rows) - rem, rem, split, parts


def id3(rows, avail, depth=0, path=()):
    counts = Counter(r[-1] for r in rows)
    pad = '    ' * depth
    if len(counts) == 1 or not avail:
        label = counts.most_common(1)[0][0]
        print(f"{pad}leaf: {label} ({len(rows)})")
        return [(path, label, len(rows))]
    print(f"{pad}node {list(path) or 'root'}: {len(rows)} rows, {dict(counts)}, H = {entropy(rows):.4f}")
    best = None
    for j in avail:
        g, rem, split, parts = gain(rows, j)
        ratio = g / split if split else 0
        print(f"{pad}  gain({ATTRS[j]}) = {entropy(rows):.4f} - {rem:.4f} = {g:.4f}   splitinfo = {split:.4f}   gain ratio = {ratio:.4f}")
        if best is None or g > best[0]:
            best = (g, j, parts)
    g, j, parts = best
    print(f"{pad}  split on {ATTRS[j]}")
    rules = []
    for v, p in parts.items():
        print(f"{pad}{ATTRS[j]} = {v}")
        rules += id3(p, [a for a in avail if a != j], depth + 1, path + ((ATTRS[j], v),))
    return rules


def kappa(matrix):
    n = sum(map(sum, matrix))
    po = sum(matrix[i][i] for i in range(len(matrix))) / n
    pe = sum(sum(matrix[i]) * sum(row[i] for row in matrix) for i in range(len(matrix))) / n ** 2
    return po, pe, (po - pe) / (1 - pe)


if __name__ == '__main__':
    print(f"root: 14 rows, {dict(Counter(r[-1] for r in DATA))}, H(S) = {entropy(DATA):.4f}\n")
    rules = id3(DATA, [0, 1, 2, 3])
    print("\nif-then rules from the tree:")
    for i, (path, label, n) in enumerate(rules, 1):
        cond = ' and '.join(f"{a} = {v}" for a, v in path)
        print(f"R{i}: if {cond} then play = {label}   ({n} instances)")
    assert sum(n for _, _, n in rules) == 14  # rules cover every row exactly once
    print("\nkappa by hand for J48's 10-fold confusion matrix on weather.nominal:")
    m = [[5, 4], [3, 2]]
    po, pe, k = kappa(m)
    print(f"matrix = {m}   po = {po:.4f}   pe = {pe:.4f}   kappa = {k:.4f}")
    assert abs(k + 0.0426) < 5e-4
