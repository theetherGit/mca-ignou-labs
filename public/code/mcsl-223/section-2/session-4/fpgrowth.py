#!/usr/bin/env python3
"""FP-Growth frequent-pattern miner with WEKA-style rule output.

Standard library only. Builds the FP-tree (items ordered by frequency),
prints the header table and the tree, mines every frequent itemset by
recursive conditional pattern bases (no candidate generation), then derives
rules the way weka.associations.FPGrowth prints them.

Item rule (same as WEKA): if every attribute has exactly two values, only the
second value counts as 'present' (positiveIndex 2). Otherwise each
attribute=value pair is an item.

Usage: python3 fpgrowth.py FILE.arff [-M minSupport] [-C minConfidence] [-N rules]
"""
import argparse
import itertools
import re
from collections import Counter
from decimal import ROUND_HALF_UP, Decimal


def read_arff(path):
    relation, attrs, rows, in_data = "", [], [], False
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("%"):
                continue
            if in_data:
                rows.append([v.strip().strip("'\"") for v in line.split(",")])
            elif line.lower().startswith("@relation"):
                relation = line.split(None, 1)[1].strip("'\"")
            elif line.lower().startswith("@attribute"):
                m = re.match(r"@attribute\s+('[^']*'|\"[^\"]*\"|\S+)\s+\{(.*)\}", line, re.I)
                attrs.append((m.group(1).strip("'\""), [v.strip() for v in m.group(2).split(",")]))
            elif line.lower().startswith("@data"):
                in_data = True
    return relation, attrs, rows


class Node:
    __slots__ = ("item", "count", "parent", "children")

    def __init__(self, item, parent):
        self.item, self.count, self.parent, self.children = item, 0, parent, {}


def build(trans, min_count):
    """trans: list of (frozenset of items, weight). Returns root, header, order, counts."""
    freq = Counter()
    for items, w in trans:
        for i in items:
            freq[i] += w
    freq = {i: c for i, c in freq.items() if c >= min_count}
    order = sorted(freq, key=lambda i: (-freq[i], i))
    root, header = Node(None, None), {i: [] for i in order}
    for items, w in trans:
        node = root
        for i in [x for x in order if x in items]:
            if i not in node.children:
                node.children[i] = Node(i, node)
                header[i].append(node.children[i])
            node = node.children[i]
            node.count += w
    return root, header, order, freq


def mine(trans, min_count, suffix, out):
    root, header, order, freq = build(trans, min_count)
    for item in reversed(order):  # least frequent item first
        pattern = suffix | {item}
        out[pattern] = freq[item]
        base = []  # conditional pattern base of `item`
        for node in header[item]:
            path, p = [], node.parent
            while p.item is not None:
                path.append(p.item)
                p = p.parent
            if path:
                base.append((frozenset(path), node.count))
        if base:
            mine(base, min_count, pattern, out)
    return root, header, order, freq


def show(node, depth=0):
    for child in node.children.values():
        print("  " * depth + f"{child.item}:{child.count}")
        show(child, depth + 1)


def fmt(x):
    """WEKA's Utils.doubleToString(x, 2): rounds half up, trailing zeros trimmed."""
    s = str(Decimal(repr(x)).quantize(Decimal("0.01"), ROUND_HALF_UP)).rstrip("0").rstrip(".")
    return s or "0"


def main():
    p = argparse.ArgumentParser()
    p.add_argument("file")
    p.add_argument("-M", type=float, default=0.2, help="minimum support (fraction)")
    p.add_argument("-C", type=float, default=0.9, help="minimum confidence")
    p.add_argument("-N", type=int, default=10, help="rules to display")
    a = p.parse_args()

    relation, attrs, rows = read_arff(a.file)
    binary = all(len(v) == 2 for _, v in attrs)
    trans = []
    for r in rows:
        items = set()
        for (name, values), v in zip(attrs, r):
            if v == "?" or (binary and v != values[1]):
                continue
            items.add(f"{name}={v}")
        trans.append((frozenset(items), 1))
    n = len(trans)
    min_count = int(a.M * n + 0.5)
    print(f"Relation: {relation}   Instances: {n}   Minimum support: {a.M} ({min_count} instances)")

    out = {}
    root, header, order, freq = mine(trans, min_count, frozenset(), out)
    print("\nHeader table (frequency-ordered items):")
    for i in order:
        print(f"  {i} {freq[i]}  ({len(header[i])} node(s))")
    print("\nFP-tree (item:count, indented by depth):")
    show(root)

    by_size = Counter(len(k) for k in out)
    print("\nFrequent itemsets by size:", dict(sorted(by_size.items())))
    for k in sorted(by_size):
        print(f"L({k}):")
        for iset in sorted((s for s in out if len(s) == k), key=sorted):
            print("  " + " ".join(sorted(iset)), out[iset])

    rules = []
    for iset, nxy in out.items():
        if len(iset) < 2:
            continue
        for size in range(1, len(iset)):
            for cons in itertools.combinations(sorted(iset), size):
                cons = frozenset(cons)
                prem = iset - cons
                nx, ny = out[prem], out[cons]
                conf = nxy / nx
                if conf >= a.C - 1e-9:
                    lift = conf / (ny / n)
                    lev = nxy / n - (nx / n) * (ny / n)
                    conv = (nx * (n - ny) / n) / (nx - nxy + 1)
                    rules.append((prem, cons, nx, nxy, conf, lift, lev, conv))
    rules.sort(key=lambda r: (-r[4], -r[3]))
    print(f"\nFPGrowth found {len(rules)} rules (displaying top {min(a.N, len(rules))})\n")
    for i, (prem, cons, nx, nxy, conf, lift, lev, conv) in enumerate(rules[: a.N], 1):
        print(f"{i:2d}. [{', '.join(sorted(prem))}]: {nx} ==> [{', '.join(sorted(cons))}]: {nxy}"
              f"   <conf:({fmt(conf)})> lift:({fmt(lift)}) lev:({fmt(lev)}) conv:({fmt(conv)})")


if __name__ == "__main__":
    main()
