#!/usr/bin/env python3
"""Apriori the way WEKA's weka.associations.Apriori runs it with the confidence metric.

Support starts at upperBoundMinSupport - delta and drops by delta each cycle until at least
numRules rules with confidence >= minMetric exist (or lowerBoundMinSupport is reached).
Itemsets whose support is above the upper bound are dropped, as in WEKA. Rules are ranked
by confidence, ties by support. Output mimics WEKA's "Associator model" block.
Run: python3 apriori.py zoo.arff --remove animal,legs --numRules 10 --upper 1.0
"""
import argparse
import itertools
from collections import Counter


def load_arff(path, remove=()):
    names, rows, data = [], [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith('%') or line.lower().startswith('@relation'):
            continue
        if line.lower().startswith('@attribute'):
            names.append(line.split(None, 2)[1])
        elif line.lower() == '@data':
            data = True
        elif data:
            rows.append([v.strip() for v in line.split(',')])
    keep = [j for j, n in enumerate(names) if n not in remove]
    return [names[j] for j in keep], [[r[j] for j in keep] for r in rows]


def large_itemsets(rows, nec, nec_max):
    """Levels L1, L2, ... of itemsets with nec <= support <= nec_max. An item is (attr, value)."""
    counts = Counter((j, v) for r in rows for j, v in enumerate(r))
    level = {(it,): c for it, c in counts.items() if nec <= c <= nec_max}
    levels = []
    while level:
        levels.append(level)
        keys = sorted(level)
        cands = set()
        for a, b in itertools.combinations(keys, 2):
            if a[:-1] == b[:-1] and a[-1][0] != b[-1][0]:  # same prefix, last items on different attributes
                c = a + (b[-1],)
                if all(c[:i] + c[i + 1:] in level for i in range(len(c))):  # every subset frequent
                    cands.add(c)
        cnt = Counter()
        for r in rows:
            for c in cands:
                if all(r[j] == v for j, v in c):
                    cnt[c] += 1
        level = {c: n for c, n in cnt.items() if nec <= n <= nec_max}
    return levels


def rules_from(levels, min_conf):
    support = {s: c for lv in levels for s, c in lv.items()}
    out = []
    for lv in levels[1:]:
        for s, c in lv.items():
            for r in range(1, len(s)):
                for cons in itertools.combinations(s, r):
                    prem = tuple(x for x in s if x not in cons)
                    conf = c / support[prem]
                    if conf >= min_conf:
                        out.append((conf, c, prem, support[prem], cons))
    out.sort(key=lambda t: (-t[0], -t[1]))
    return out


def run(names, rows, num_rules=10, min_conf=0.9, delta=0.05, upper=1.0, lower=0.1):
    n = len(rows)
    nec_max = int(upper * n + 0.5)
    min_sup = upper - delta          # same double arithmetic as WEKA, so the printed supports match
    cycles = 0
    while True:
        nec = int(min_sup * n + 0.5)
        levels = large_itemsets(rows, nec, nec_max)
        rules = rules_from(levels, min_conf)
        cycles += 1
        if len(rules) >= num_rules or min_sup - delta < lower - 1e-12:
            break
        min_sup -= delta
    return min_sup, nec, cycles, levels, rules


def fmt(items, names):
    return ' '.join(f"{names[j]}={v}" for j, v in items)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('arff')
    ap.add_argument('--remove', default='', help='comma separated attribute names to drop')
    ap.add_argument('--numRules', type=int, default=10)
    ap.add_argument('--minMetric', type=float, default=0.9)
    ap.add_argument('--delta', type=float, default=0.05)
    ap.add_argument('--upper', type=float, default=1.0)
    ap.add_argument('--lower', type=float, default=0.1)
    ap.add_argument('--find', default='', help='report the rank of the first rule mentioning this item, e.g. type=mammal')
    a = ap.parse_args()
    names, rows = load_arff(a.arff, set(filter(None, a.remove.split(','))))
    min_sup, nec, cycles, levels, rules = run(names, rows, a.numRules, a.minMetric, a.delta, a.upper, a.lower)
    print(f"Scheme:       weka.associations.Apriori -N {a.numRules} -T 0 -C {a.minMetric} -D {a.delta} -U {a.upper} -M {a.lower} -S -1.0 -c -1")
    print(f"Instances:    {len(rows)}\nAttributes:   {len(names)}\n")
    print("Apriori\n=======\n")
    print(f"Minimum support: {min_sup:.2f} ({nec} instances)")
    print(f"Minimum metric <confidence>: {a.minMetric}")
    print(f"Number of cycles performed: {cycles}\n")
    print("Generated sets of large itemsets:\n")
    for i, lv in enumerate(levels, 1):
        print(f"Size of set of large itemsets L({i}): {len(lv)}")
    print(f"\nBest rules found:\n")
    for i, (conf, c, prem, ps, cons) in enumerate(rules[:a.numRules], 1):
        print(f"{i:2d}. {fmt(prem, names)} {ps} ==> {fmt(cons, names)} {c}    conf:({conf:.2g})")
    if a.find:
        j, v = a.find.split('=')
        hit = next((i for i, r in enumerate(rules, 1) if (names.index(j), v) in r[2] + r[4]), None)
        print(f"\nrules with confidence >= {a.minMetric} at this support: {len(rules)}")
        print(f"first rule mentioning {a.find}: rank {hit}" if hit else f"no rule mentions {a.find} at this support")


if __name__ == '__main__':
    main()
