#!/usr/bin/env python3
"""Apriori association-rule miner that behaves like weka.associations.Apriori.

Standard library only. Reads an ARFF file with nominal attributes (numeric
attributes are discretised into equal-width bins first, like WEKA's
unsupervised Discretize filter) and prints the same blocks WEKA prints.

Usage:
  python3 apriori.py FILE.arff [-N rules] [-C minMetric] [-T 0|1] [-D delta]
                     [-U upperBoundMinSupport] [-M lowerBoundMinSupport]
                     [-B bins] [-R attr,attr] [-I]

  -T 0 ranks by confidence (default), -T 1 by lift.  -I prints the large
  itemsets.  -R removes attributes by 1-based index before mining (like the
  Remove filter).  -B is the number of bins for numeric attributes.

Examples:
  python3 apriori.py contact-lenses.arff                   # WEKA defaults
  python3 apriori.py contact-lenses.arff -M 0.2 -U 0.2 -I  # one pass at 0.2
  python3 apriori.py iris-sample.arff -B 3 -M 0.3
"""
import argparse
import itertools
import re
from collections import Counter
from decimal import ROUND_HALF_UP, Decimal


def read_arff(path):
    """Return (relation, [(name, values-or-None)], rows). '?' marks missing."""
    relation, attrs, rows, in_data = "", [], [], False
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("%"):
                continue
            if in_data:
                rows.append([v.strip().strip("'\"") for v in line.split(",")])
                continue
            low = line.lower()
            if low.startswith("@relation"):
                relation = line.split(None, 1)[1].strip("'\"")
            elif low.startswith("@attribute"):
                m = re.match(r"@attribute\s+('[^']*'|\"[^\"]*\"|\S+)\s+(.*)", line, re.I)
                name, typ = m.group(1).strip("'\""), m.group(2).strip()
                if typ.startswith("{"):
                    attrs.append((name, [v.strip().strip("'\"") for v in typ.strip("{}").split(",")]))
                else:
                    attrs.append((name, None))  # numeric / real / integer
            elif low.startswith("@data"):
                in_data = True
    return relation, attrs, rows


def fmt(x, places=6):
    """WEKA's Utils.doubleToString: rounds half up, trailing zeros trimmed."""
    s = str(Decimal(repr(x)).quantize(Decimal(1).scaleb(-places), ROUND_HALF_UP)).rstrip("0").rstrip(".")
    return s if s not in ("", "-0") else "0"


def discretize(attrs, rows, bins):
    """Equal-width bins with WEKA's labels: '(-inf-c1]', '(c1-c2]', '(cn-inf)'."""
    for j, (name, values) in enumerate(attrs):
        if values is not None:
            continue
        nums = [float(r[j]) for r in rows if r[j] != "?"]
        lo, hi = min(nums), max(nums)
        width = (hi - lo) / bins
        cuts = [lo + i * width for i in range(1, bins)]
        labels = ["'(-inf-%s]'" % fmt(cuts[0])]
        labels += ["'(%s-%s]'" % (fmt(a), fmt(b)) for a, b in zip(cuts, cuts[1:])]
        labels.append("'(%s-inf)'" % fmt(cuts[-1]))
        for r in rows:
            if r[j] == "?":
                continue
            v, k = float(r[j]), 0
            while k < len(cuts) and v > cuts[k]:
                k += 1
            r[j] = labels[k]
        attrs[j] = (name, labels)
    return attrs, rows


def large_itemsets(trans, min_count):
    """Level-wise Apriori. Returns [L1, L2, ...] as dicts itemset -> count."""
    counts = Counter(i for t in trans for i in t)
    levels = [{frozenset([i]): c for i, c in counts.items() if c >= min_count}]
    while levels[-1]:
        prev = levels[-1]
        cands = set()
        for a, b in itertools.combinations(sorted(prev, key=sorted), 2):
            u = a | b
            if len(u) == len(a) + 1 and all(frozenset(s) in prev for s in itertools.combinations(u, len(a))):
                cands.add(u)
        # ponytail: O(|L|^2) join, fine for lab-sized files; prefix join if it ever matters
        counts = {c: sum(1 for t in trans if c <= t) for c in cands}
        levels.append({c: n for c, n in counts.items() if n >= min_count})
    return levels[:-1]


def rules_from(levels, n, min_metric, metric_type):
    """All rules X ==> Y from every large itemset, kept when metric >= min_metric.
    Generation order matches WEKA: itemsets in attribute order, consequents of
    size 1 first, then size 2, ... (this fixes the tie order in the output)."""
    supp = {k: v for lev in levels for k, v in lev.items()}
    out = []
    for lev in levels[1:]:
        for iset in sorted(lev, key=sorted):
            items = sorted(iset)
            for size in range(1, len(items)):
                for cons in itertools.combinations(items, size):
                    cons = frozenset(cons)
                    prem = iset - cons
                    nxy, nx, ny = supp[iset], supp[prem], supp[cons]
                    conf = nxy / nx
                    lift = conf / (ny / n)
                    lev_ = nxy / n - (nx / n) * (ny / n)
                    conv = (nx * (n - ny) / n) / (nx - nxy + 1)  # WEKA adds 1 to the denominator
                    metric = conf if metric_type == 0 else lift
                    if metric >= min_metric - 1e-9:
                        out.append((prem, cons, nx, nxy, conf, lift, lev_, conv))
    return out


def item_str(attrs, item):
    j, vi = item
    return f"{attrs[j][0]}={attrs[j][1][vi]}"


def main():
    p = argparse.ArgumentParser()
    p.add_argument("file")
    p.add_argument("-N", type=int, default=10, help="numRules")
    p.add_argument("-C", type=float, default=0.9, help="minMetric")
    p.add_argument("-T", type=int, default=0, help="metricType 0=confidence 1=lift")
    p.add_argument("-D", type=float, default=0.05, help="delta")
    p.add_argument("-U", type=float, default=1.0, help="upperBoundMinSupport")
    p.add_argument("-M", type=float, default=0.1, help="lowerBoundMinSupport")
    p.add_argument("-B", type=int, default=10, help="bins for numeric attributes")
    p.add_argument("-R", default="", help="1-based attribute indices to remove")
    p.add_argument("-I", action="store_true", help="outputItemSets")
    a = p.parse_args()

    relation, attrs, rows = read_arff(a.file)
    if a.R:
        drop = {int(i) - 1 for i in a.R.split(",")}
        attrs = [x for j, x in enumerate(attrs) if j not in drop]
        rows = [[v for j, v in enumerate(r) if j not in drop] for r in rows]
    attrs, rows = discretize(attrs, rows, a.B)
    # items are (attribute index, value index) so ordering follows the ARFF declaration
    trans = [frozenset((j, attrs[j][1].index(v)) for j, v in enumerate(r) if v != "?") for r in rows]
    n = len(trans)

    metric_name = ["confidence", "lift"][a.T]
    print("=== Run information ===\n")
    print(f"Scheme:       weka.associations.Apriori -N {a.N} -T {a.T} -C {a.C} -D {a.D} -U {a.U} -M {a.M} -S -1.0 -c -1")
    print(f"Relation:     {relation}")
    print(f"Instances:    {n}")
    print(f"Attributes:   {len(attrs)}")
    for name, _ in attrs:
        print(f"              {name}")
    print("=== Associator model (full training set) ===\n\n\nApriori\n=======\n")

    # WEKA: start at upper - delta, lower the support each cycle until numRules
    # rules pass minMetric or the lower bound is reached.
    min_support, cycles = round(a.U - a.D, 10), 0
    if min_support < a.M:
        min_support = a.M
    while True:
        need = int(min_support * n + 0.5)
        levels = large_itemsets(trans, need)
        rules = rules_from(levels, n, a.C, a.T)
        cycles += 1
        nxt = round(min_support - a.D, 10)
        if len(rules) >= a.N or nxt < a.M - 1e-9 or nxt <= 0:
            break
        min_support = nxt

    print(f"Minimum support: {fmt(min_support, 2)} ({need} instances)")
    print(f"Minimum metric <{metric_name}>: {fmt(a.C, 2)}")
    print(f"Number of cycles performed: {cycles}\n")
    print("Generated sets of large itemsets:\n")
    for k, lev in enumerate(levels, 1):
        print(f"Size of set of large itemsets L({k}): {len(lev)}\n")
        if a.I:
            print(f"Large Itemsets L({k}):")
            for iset in sorted(lev, key=sorted):
                print(" ".join(item_str(attrs, i) for i in sorted(iset)), lev[iset])
            print()

    # rank: metric descending, then support descending, then generation order
    key = (lambda r: (-r[4], -r[3])) if a.T == 0 else (lambda r: (-r[5], -r[3]))
    rules.sort(key=key)
    print("Best rules found:\n")
    for i, (prem, cons, nx, nxy, conf, lift, lev_, conv) in enumerate(rules[: a.N], 1):
        lhs = " ".join(item_str(attrs, x) for x in sorted(prem))
        rhs = " ".join(item_str(attrs, x) for x in sorted(cons))
        m = [f"conf:({fmt(conf, 2)})", f"lift:({fmt(lift, 2)})",
             f"lev:({fmt(lev_, 2)}) [{int(round(lev_ * n, 6))}]", f"conv:({fmt(conv, 2)})"]
        m[a.T] = "<" + m[a.T] + ">"
        print(f"{i:2d}. {lhs} {nx} ==> {rhs} {nxy}    {' '.join(m)}")


if __name__ == "__main__":
    main()
