#!/usr/bin/env python3
"""Reproduce WEKA's Preprocess panel numbers and four filters on student.arff.

Standard library only. Prints, in order:
  1. the per-attribute summary the Preprocess panel shows (counts, min, max,
     mean, sample standard deviation, missing, distinct)
  2. ReplaceMissingValues  (numeric -> mean, nominal -> mode)
  3. Normalize             (x' = (x - min) / (max - min) on every numeric attribute)
  4. Discretize            (equal-width bins with WEKA's labels)
  5. Resample              (50 % without replacement; class counts before and after)

Usage: python3 preprocess.py student.arff
"""
import random
import re
import statistics
import sys
from collections import Counter


def read_arff(path):
    attrs, rows, in_data = [], [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith("%"):
            continue
        if in_data:
            rows.append([v.strip() for v in line.split(",")])
        elif line.lower().startswith("@attribute"):
            m = re.match(r"@attribute\s+(\S+)\s+(.*)", line, re.I)
            typ = m.group(2).strip()
            attrs.append((m.group(1), [v.strip() for v in typ.strip("{}").split(",")] if typ.startswith("{") else None))
        elif line.lower().startswith("@data"):
            in_data = True
    return attrs, rows


def fmt(x, places=3):
    return f"{x:.{places}f}".rstrip("0").rstrip(".")


def summary(attrs, rows):
    print(f"Instances: {len(rows)}   Attributes: {len(attrs)}\n")
    for j, (name, values) in enumerate(attrs):
        col = [r[j] for r in rows]
        missing = col.count("?")
        present = [v for v in col if v != "?"]
        if values is None:
            nums = [float(v) for v in present]
            print(f"{name:12s} Numeric  Missing: {missing} ({100 * missing // len(col)}%)  Distinct: {len(set(present))}"
                  f"  Min: {fmt(min(nums))}  Max: {fmt(max(nums))}  Mean: {fmt(statistics.mean(nums))}"
                  f"  StdDev: {fmt(statistics.stdev(nums))}")
        else:
            c = Counter(present)
            print(f"{name:12s} Nominal  Missing: {missing} ({100 * missing // len(col)}%)  " +
                  "  ".join(f"{v}: {c[v]}" for v in values))


def main():
    attrs, rows = read_arff(sys.argv[1])
    print("=== 1. Preprocess panel, as loaded ===")
    summary(attrs, rows)

    print("\n=== 2. ReplaceMissingValues ===")
    for j, (name, values) in enumerate(attrs):
        present = [r[j] for r in rows if r[j] != "?"]
        fill = fmt(statistics.mean(float(v) for v in present)) if values is None else Counter(present).most_common(1)[0][0]
        for i, r in enumerate(rows):
            if r[j] == "?":
                print(f"row {i + 1}: {name} ? -> {fill}")
                r[j] = fill

    print("\n=== 3. Normalize (first 5 rows, numeric attributes only) ===")
    numeric = [j for j, (_, v) in enumerate(attrs) if v is None]
    lo = {j: min(float(r[j]) for r in rows) for j in numeric}
    hi = {j: max(float(r[j]) for r in rows) for j in numeric}
    print("before:", *[" ".join(r[j] for j in numeric) for r in rows[:5]], sep="\n  ")
    norm = [[fmt((float(r[j]) - lo[j]) / (hi[j] - lo[j])) for j in numeric] for r in rows[:5]]
    print("after: ", *[" ".join(r) for r in norm], sep="\n  ")

    print("\n=== 4. Discretize attendance, 3 equal-width bins ===")
    j = [n for n, _ in attrs].index("attendance")
    vals = [float(r[j]) for r in rows]
    width = (max(vals) - min(vals)) / 3
    cuts = [min(vals) + width, min(vals) + 2 * width]
    labels = [f"'(-inf-{fmt(cuts[0], 6)}]'", f"'({fmt(cuts[0], 6)}-{fmt(cuts[1], 6)}]'", f"'({fmt(cuts[1], 6)}-inf)'"]
    bins = Counter(labels[0 if v <= cuts[0] else 1 if v <= cuts[1] else 2] for v in vals)
    for lab in labels:
        print(f"{lab} {bins[lab]}")

    print("\n=== 5. Resample 50% without replacement (seed 1) ===")
    cls = len(attrs) - 1
    print("before:", len(rows), dict(Counter(r[cls] for r in rows)))
    sample = random.Random(1).sample(rows, len(rows) // 2)
    print("after: ", len(sample), dict(Counter(r[cls] for r in sample)))


if __name__ == "__main__":
    main()
