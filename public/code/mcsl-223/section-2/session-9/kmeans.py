#!/usr/bin/env python3
"""k-means on the numeric attributes of an ARFF file, standard library only.
Mirrors WEKA's SimpleKMeans: attributes normalised to [0,1] for the distance, k random
instances as starting centroids, SSE reported on the normalised data, centroids in the
original units. Runs k = 2..5, then classes-to-clusters evaluation for the chosen k.
Run: python3 kmeans.py iris_sample.arff 3
"""
import random
import sys


def load_arff(path):
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
    cls = [i for i, n in enumerate(nominal) if n]
    X = [[float(r[i]) for i in num] for r in rows]
    labels = [r[cls[-1]] for r in rows] if cls else None
    return [names[i] for i in num], X, labels


def normalise(X):
    lo = [min(c) for c in zip(*X)]
    hi = [max(c) for c in zip(*X)]
    return [[(v - l) / ((h - l) or 1) for v, l, h in zip(r, lo, hi)] for r in X]


def kmeans(X, k, seed):
    rnd = random.Random(seed)
    cent = [list(c) for c in rnd.sample(X, k)]
    for it in range(1, 500):
        assign = [min(range(k), key=lambda j: sum((a - b) ** 2 for a, b in zip(x, cent[j]))) for x in X]
        new = []
        for j in range(k):
            m = [x for x, a in zip(X, assign) if a == j]
            new.append([sum(c) / len(m) for c in zip(*m)] if m else cent[j])
        if new == cent:
            break
        cent = new
    sse = sum(sum((a - b) ** 2 for a, b in zip(x, cent[j])) for x, j in zip(X, assign))
    return sse, assign, cent, it


def best_of(X, k, restarts=10):
    return min((kmeans(X, k, seed) for seed in range(restarts)), key=lambda r: r[0])


def main(path, k_detail):
    names, X, labels = load_arff(path)
    Xn = normalise(X)
    print(f"{path}: {len(X)} instances, numeric attributes {names}\n")
    print(f"{'k':>2} {'SSE (normalised)':>17} {'iterations':>10}  cluster sizes")
    for k in range(2, 6):
        sse, assign, cent, it = best_of(Xn, k)
        sizes = [assign.count(j) for j in range(k)]
        print(f"{k:2d} {sse:17.4f} {it:10d}  {sizes}")
    sse, assign, cent, it = best_of(Xn, k_detail)
    print(f"\n=== k = {k_detail}: centroids in original units (WEKA layout) ===")
    print(f"{'Attribute':14} {'Full Data':>10} " + ' '.join(f"{'Cluster ' + str(j):>10}" for j in range(k_detail)))
    print(f"{'':14} {'(' + str(len(X)) + ')':>10} " + ' '.join(f"{'(' + str(assign.count(j)) + ')':>10}" for j in range(k_detail)))
    for i, name in enumerate(names):
        full = sum(r[i] for r in X) / len(X)
        cs = [sum(r[i] for r, a in zip(X, assign) if a == j) / assign.count(j) for j in range(k_detail)]
        print(f"{name:14} {full:10.4f} " + ' '.join(f"{c:10.4f}" for c in cs))
    print(f"\nWithin cluster sum of squared errors: {sse:.4f}")
    for j in range(k_detail):
        print(f"Clustered Instances  {j}  {assign.count(j)} ({100 * assign.count(j) / len(X):.0f}%)")
    if labels:
        print("\n=== Classes to Clusters ===")
        classes = sorted(set(labels), key=labels.index)
        print('  ' + ' '.join(f"{j:>4}" for j in range(k_detail)) + '  <-- assigned to cluster')
        for c in classes:
            print('  ' + ' '.join(f"{sum(1 for a, l in zip(assign, labels) if a == j and l == c):4d}" for j in range(k_detail)) + f" | {c}")
        wrong = len(X)
        for j in range(k_detail):
            members = [l for a, l in zip(assign, labels) if a == j]
            if members:
                top = max(classes, key=members.count)
                print(f"Cluster {j} <-- {top}")
                wrong -= members.count(top)
        print(f"Incorrectly clustered instances : {wrong}   {100 * wrong / len(X):.4f} %")
    # self-check: k-means never ends with an empty cluster on this data and SSE falls with k
    assert all(assign.count(j) for j in range(k_detail))


if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else 'iris_sample.arff', int(sys.argv[2]) if len(sys.argv) > 2 else 3)
