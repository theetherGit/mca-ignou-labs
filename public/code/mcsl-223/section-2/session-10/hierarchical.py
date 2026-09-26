#!/usr/bin/env python3
"""Agglomerative hierarchical clustering (single, complete, average linkage) on the numeric
attributes of an ARFF file, normalised to [0,1] like WEKA's HierarchicalClusterer.
Prints every merge (the dendrogram as text) and the clusters when the tree is cut at k.
Run: python3 hierarchical.py employee.arff average 2
"""
import math
import sys


def load_numeric(path):
    names, nominal, rows, data = [], [], [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith('%') or line.lower().startswith('@relation'):
            continue
        if line.lower().startswith('@attribute'):
            _, name, typ = line.split(None, 2)
            names.append(name)
            nominal.append(typ.strip().startswith('{'))
        elif line.lower() == '@data':
            data = True
        elif data:
            rows.append([v.strip() for v in line.split(',')])
    num = [i for i, n in enumerate(nominal) if not n]
    X = [[float(r[i]) for i in num] for r in rows]
    lo, hi = [min(c) for c in zip(*X)], [max(c) for c in zip(*X)]
    Xn = [[(v - l) / ((h - l) or 1) for v, l, h in zip(r, lo, hi)] for r in X]
    return [names[i] for i in num], X, Xn


def dist(a, b):
    return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))


def linkage_distance(kind, A, B, D):
    ds = [D[i][j] for i in A for j in B]
    return {'single': min, 'complete': max, 'average': lambda v: sum(v) / len(v)}[kind](ds)


def cluster(Xn, kind, k):
    n = len(Xn)
    D = [[dist(a, b) for b in Xn] for a in Xn]
    clusters = [[i] for i in range(n)]
    merges = []
    while len(clusters) > 1:
        best = min(((linkage_distance(kind, A, B, D), i, j) for i, A in enumerate(clusters) for j, B in enumerate(clusters) if i < j))
        d, i, j = best
        merges.append((d, clusters[i], clusters[j]))
        clusters = [c for t, c in enumerate(clusters) if t not in (i, j)] + [clusters[i] + clusters[j]]
        if len(clusters) == k:
            cut = [sorted(c) for c in clusters]
    return merges, cut


def main(path, kind, k):
    names, X, Xn = load_numeric(path)
    merges, cut = cluster(Xn, kind, k)
    print(f"{path}: {len(X)} instances on {names}, {kind} linkage\n")
    print("merge order (instance numbers start at 1; distance is on normalised attributes):")
    for step, (d, A, B) in enumerate(merges, 1):
        show = lambda c: '{' + ','.join(str(i + 1) for i in sorted(c)) + '}'
        print(f"step {step:2d}  d = {d:.4f}  {show(A)} + {show(B)}")
    print(f"\nclusters when cut at k = {k}:")
    for j, c in enumerate(cut):
        mean = [sum(X[i][a] for i in c) / len(c) for a in range(len(names))]
        print(f"cluster {j}: {len(c)} instances {[i + 1 for i in c]}")
        print('           mean ' + ', '.join(f"{n} = {m:.1f}" for n, m in zip(names, mean)))
    # self-check: merge distances never decrease for single/complete/average linkage
    assert all(a[0] <= b[0] + 1e-12 for a, b in zip(merges, merges[1:]))


if __name__ == '__main__':
    a = sys.argv[1:] + ['employee.arff', 'average', '2'][len(sys.argv) - 1:]
    main(a[0], a[1], int(a[2]))
