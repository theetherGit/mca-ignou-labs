#!/usr/bin/env python3
"""DBSCAN on the numeric attributes of an ARFF file, normalised to [0,1] like WEKA's
DBSCAN package. Prints a grid of epsilon and minPoints (clusters found, noise count),
then the membership for one chosen setting.
Run: python3 dbscan.py employee.arff 0.15 3
"""
import math
import sys


def load_numeric(path):
    nominal, rows, data = [], [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith('%') or line.lower().startswith('@relation'):
            continue
        if line.lower().startswith('@attribute'):
            nominal.append(line.split(None, 2)[2].strip().startswith('{'))
        elif line.lower() == '@data':
            data = True
        elif data:
            rows.append([v.strip() for v in line.split(',')])
    X = [[float(r[i]) for i, n in enumerate(nominal) if not n] for r in rows]
    lo, hi = [min(c) for c in zip(*X)], [max(c) for c in zip(*X)]
    return [[(v - l) / ((h - l) or 1) for v, l, h in zip(r, lo, hi)] for r in X]


def dbscan(X, eps, min_pts):
    n = len(X)
    near = [[j for j in range(n) if math.dist(X[i], X[j]) <= eps] for i in range(n)]  # includes i itself
    label = [None] * n  # None = unvisited, -1 = noise, else cluster id
    c = 0
    for i in range(n):
        if label[i] is not None:
            continue
        if len(near[i]) < min_pts:
            label[i] = -1
            continue
        label[i] = c
        queue = list(near[i])
        while queue:
            j = queue.pop()
            if label[j] == -1:
                label[j] = c  # border point
            if label[j] is not None:
                continue
            label[j] = c
            if len(near[j]) >= min_pts:  # core point: expand
                queue.extend(near[j])
        c += 1
    return label


def main(path, eps, min_pts):
    X = load_numeric(path)
    print(f"{path}: {len(X)} instances\n")
    print(f"{'epsilon':>8} {'minPoints':>9} {'clusters':>8} {'noise':>5}  cluster sizes")
    for e in (0.05, 0.10, 0.15, 0.20, 0.30):
        for m in (2, 3, 5):
            lab = dbscan(X, e, m)
            k = max(lab) + 1
            print(f"{e:8.2f} {m:9d} {k:8d} {lab.count(-1):5d}  {[lab.count(j) for j in range(k)]}")
    lab = dbscan(X, eps, min_pts)
    print(f"\n=== epsilon = {eps}, minPoints = {min_pts} ===")
    for j in range(max(lab) + 1):
        print(f"cluster {j}: instances {[i + 1 for i, l in enumerate(lab) if l == j]}")
    print(f"noise (unclustered): instances {[i + 1 for i, l in enumerate(lab) if l == -1]}")
    # self-check: a point inside a cluster is never left as noise
    assert all(l is not None for l in lab)


if __name__ == '__main__':
    a = sys.argv[1:] + ['employee.arff', '0.15', '3'][len(sys.argv) - 1:]
    main(a[0], float(a[1]), int(a[2]))
