#!/usr/bin/env python3
"""10-fold stratified cross-validation of five classifiers, standard library only.

NaiveBayes, IBk (k-NN, k = 1), an unpruned information-gain decision tree (ID3 with
J48-style binary splits on numeric attributes), Logistic regression (gradient descent)
and a linear SVM (Pegasos). For each one it prints accuracy, kappa, ROC area and the
confusion matrix in the layout WEKA uses, so the numbers can be checked against WEKA.
Run: python3 classify_cv.py student.arff employee.arff
"""
import math
import random
import sys
from collections import Counter


def load_arff(path):
    attrs, rows, data = [], [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith('%') or line.lower().startswith('@relation'):
            continue
        if line.lower().startswith('@attribute'):
            _, name, typ = line.split(None, 2)
            typ = typ.strip()
            nominal = None if typ.lower() in ('numeric', 'real', 'integer') else [v.strip() for v in typ.strip('{}').split(',')]
            attrs.append((name, nominal))
        elif line.lower() == '@data':
            data = True
        elif data:
            vals = [v.strip() for v in line.split(',')]
            rows.append([float(v) if a[1] is None else v for v, a in zip(vals, attrs)])
    return attrs, rows


def folds(rows, k=10, seed=1):
    """Stratified folds: shuffle, then a stable sort by class stripes each class across folds."""
    idx = list(range(len(rows)))
    random.Random(seed).shuffle(idx)
    idx.sort(key=lambda i: rows[i][-1])
    return [idx[f::k] for f in range(k)]


def ranges(attrs, rows):
    lo = {j: min(r[j] for r in rows) for j, a in enumerate(attrs[:-1]) if a[1] is None}
    hi = {j: max(r[j] for r in rows) for j, a in enumerate(attrs[:-1]) if a[1] is None}
    return lo, hi


def encoder(attrs, train):
    """Numeric attributes scaled to [0,1], nominal ones one-hot, plus a bias input."""
    lo, hi = ranges(attrs, train)

    def vec(row):
        v = [1.0]
        for j, (name, vals) in enumerate(attrs[:-1]):
            if vals is None:
                v.append((row[j] - lo[j]) / ((hi[j] - lo[j]) or 1))
            else:
                v.extend(1.0 if row[j] == x else 0.0 for x in vals)
        return v
    return vec


def entropy(rows):
    n = len(rows)
    return -sum(c / n * math.log2(c / n) for c in Counter(r[-1] for r in rows).values())


# ---- classifiers: each returns prob(row) -> {class: probability} ----

def naive_bayes(attrs, train):
    classes = attrs[-1][1]
    prior = Counter(r[-1] for r in train)
    stats = {}
    for j, (name, vals) in enumerate(attrs[:-1]):
        for c in classes:
            col = [r[j] for r in train if r[-1] == c]
            if vals is None:
                m = sum(col) / len(col) if col else 0.0
                sd = math.sqrt(sum((v - m) ** 2 for v in col) / max(len(col) - 1, 1)) if col else 1.0
                stats[j, c] = (m, sd or 1e-3)
            else:
                stats[j, c] = Counter(col)

    def prob(row):
        lp = {}
        for c in classes:
            s = math.log((prior[c] + 1) / (len(train) + len(classes)))
            for j, (name, vals) in enumerate(attrs[:-1]):
                if vals is None:
                    m, sd = stats[j, c]
                    s += -0.5 * ((row[j] - m) / sd) ** 2 - math.log(sd * math.sqrt(2 * math.pi))
                else:
                    s += math.log((stats[j, c][row[j]] + 1) / (prior[c] + len(vals)))  # Laplace
            lp[c] = s
        mx = max(lp.values())
        z = sum(math.exp(v - mx) for v in lp.values())
        return {c: math.exp(v - mx) / z for c, v in lp.items()}
    return prob


def knn(attrs, train, k=1):
    classes = attrs[-1][1]
    lo, hi = ranges(attrs, train)

    def dist(a, b):
        d = 0.0
        for j, (name, vals) in enumerate(attrs[:-1]):
            if vals is None:
                d += ((a[j] - b[j]) / ((hi[j] - lo[j]) or 1)) ** 2
            else:
                d += a[j] != b[j]
        return d

    def prob(row):
        near = sorted(train, key=lambda t: dist(row, t))[:k]
        cnt = Counter(t[-1] for t in near)
        return {c: cnt[c] / k for c in classes}
    return prob


def tree(attrs, train, min_leaf=2):
    """Unpruned tree on information gain; numeric attributes get one binary split per node."""
    classes = attrs[-1][1]

    def build(rows, used):
        counts = Counter(r[-1] for r in rows)
        if len(counts) == 1 or len(rows) < 2 * min_leaf:
            return counts
        h, best = entropy(rows), None
        for j, (name, vals) in enumerate(attrs[:-1]):
            if vals is not None:
                if j in used:
                    continue
                cands = [(None, {v: [r for r in rows if r[j] == v] for v in vals})]
            else:
                xs = sorted(set(r[j] for r in rows))
                cands = [((a + b) / 2, None) for a, b in zip(xs, xs[1:])]
                cands = [(t, {'<=': [r for r in rows if r[j] <= t], '>': [r for r in rows if r[j] > t]}) for t, _ in cands]
            for t, parts in cands:
                if any(0 < len(p) < min_leaf for p in parts.values()):
                    continue
                gain = h - sum(len(p) / len(rows) * entropy(p) for p in parts.values() if p)
                if best is None or gain > best[0] + 1e-12:
                    best = (gain, j, t, parts)
        if best is None or best[0] < 1e-9:
            return counts
        gain, j, t, parts = best
        kids = {v: build(p, used | ({j} if t is None else set())) for v, p in parts.items() if p}
        return (j, t, kids, counts)

    root = build(train, set())

    def prob(row):
        node = root
        while isinstance(node, tuple):
            j, t, kids, counts = node
            key = row[j] if t is None else ('<=' if row[j] <= t else '>')
            node = kids.get(key, counts)
        n = sum(node.values())
        return {c: node[c] / n for c in classes}
    prob.root = root
    return prob


def show_tree(attrs, node, depth=0):
    """Print a tree the way WEKA's J48 does: branch per line, leaf as class (n/errors)."""
    j, t, kids, counts = node
    for key, kid in kids.items():
        label = f"{attrs[j][0]} = {key}" if t is None else f"{attrs[j][0]} {key} {t:g}"
        if isinstance(kid, tuple):
            print('|   ' * depth + label)
            show_tree(attrs, kid, depth + 1)
        else:
            top, n = kid.most_common(1)[0], sum(kid.values())
            wrong = n - top[1]
            print('|   ' * depth + f"{label}: {top[0]} ({n}.0" + (f"/{wrong}.0)" if wrong else ")"))


def sigmoid(s):
    return 1 / (1 + math.exp(-max(-30.0, min(30.0, s))))


def logistic(attrs, train, epochs=3000, lr=0.5, ridge=1e-4):
    classes = attrs[-1][1]
    assert len(classes) == 2, "logistic here is two-class only"
    vec = encoder(attrs, train)
    X = [vec(r) for r in train]
    Y = [1.0 if r[-1] == classes[0] else 0.0 for r in train]
    w = [0.0] * len(X[0])
    for _ in range(epochs):
        g = [ridge * wi for wi in w]
        for x, y in zip(X, Y):
            e = sigmoid(sum(wi * xi for wi, xi in zip(w, x))) - y
            for i, xi in enumerate(x):
                g[i] += e * xi
        w = [wi - lr * gi / len(X) for wi, gi in zip(w, g)]

    def prob(row):
        p = sigmoid(sum(wi * xi for wi, xi in zip(w, vec(row))))
        return {classes[0]: p, classes[1]: 1 - p}
    prob.w = w
    return prob


def svm(attrs, train, epochs=300, C=1.0, seed=1):
    """Linear SVM trained with Pegasos (stochastic sub-gradient); WEKA's SMO uses a linear kernel by default too."""
    classes = attrs[-1][1]
    assert len(classes) == 2, "svm here is two-class only"
    vec = encoder(attrs, train)
    X = [vec(r) for r in train]
    Y = [1.0 if r[-1] == classes[0] else -1.0 for r in train]
    n, lam, t = len(X), 1 / (C * len(X)), 0
    w = [0.0] * len(X[0])
    rnd = random.Random(seed)
    for _ in range(epochs):
        order = list(range(n))
        rnd.shuffle(order)
        for i in order:
            t += 1
            eta = 1 / (lam * t)
            hinge = Y[i] * sum(wi * xi for wi, xi in zip(w, X[i])) < 1
            w = [(1 - eta * lam) * wi + (eta * Y[i] * xi if hinge else 0.0) for wi, xi in zip(w, X[i])]

    def prob(row):
        p = sigmoid(sum(wi * xi for wi, xi in zip(w, vec(row))))  # only for ranking in ROC
        return {classes[0]: p, classes[1]: 1 - p}
    return prob


# ---- evaluation ----

def kappa(cm, classes):
    n = sum(sum(r.values()) for r in cm.values())
    po = sum(cm[c][c] for c in classes) / n
    pe = sum(sum(cm[c].values()) * sum(cm[r][c] for r in classes) for c in classes) / n ** 2
    return (po - pe) / (1 - pe) if pe < 1 else 1.0


def auc(scores):
    """Mann-Whitney: share of (positive, negative) pairs ranked correctly; ties count half."""
    pos = [s for s, y in scores if y]
    neg = [s for s, y in scores if not y]
    if not pos or not neg:
        return float('nan')
    return sum((p > q) + 0.5 * (p == q) for p in pos for q in neg) / (len(pos) * len(neg))


def evaluate(attrs, rows, make):
    classes = attrs[-1][1]
    cm = {c: Counter() for c in classes}
    scores = []
    for f in folds(rows):
        test = set(f)
        prob = make(attrs, [r for i, r in enumerate(rows) if i not in test])
        for i in f:
            p = prob(rows[i])
            pred = max(classes, key=lambda c: p[c])
            cm[rows[i][-1]][pred] += 1
            scores.append((p[classes[0]], rows[i][-1] == classes[0]))
    return cm, kappa(cm, classes), auc(scores)


def report(name, attrs, rows, cm, k, a):
    classes = attrs[-1][1]
    n, correct = len(rows), sum(cm[c][c] for c in classes)
    print(f"=== {name} : 10-fold cross-validation ===")
    print(f"Correctly Classified Instances   {correct:4d}   {100 * correct / n:7.4f} %")
    print(f"Incorrectly Classified Instances {n - correct:4d}   {100 * (n - correct) / n:7.4f} %")
    print(f"Kappa statistic                  {k:.4f}")
    print(f"ROC Area ({classes[0]})            {a:.4f}")
    print("=== Confusion Matrix ===")
    letters = 'abcdefghijklmnopqrstuvwxyz'
    print('  ' + ' '.join(f"{letters[i]:>3}" for i in range(len(classes))) + '   <-- classified as')
    for i, c in enumerate(classes):
        print('  ' + ' '.join(f"{cm[c][d]:3d}" for d in classes) + f" | {letters[i]} = {c}")
    print()


MODELS = [('NaiveBayes', naive_bayes), ('IBk (k=1)', knn), ('Tree (ID3/J48, unpruned)', tree),
          ('Logistic', logistic), ('SVM (linear, C=1)', svm)]


def main(paths):
    for path in paths:
        attrs, rows = load_arff(path)
        print(f"##### {path}: {len(rows)} instances, {len(attrs)} attributes, class = {attrs[-1][0]} #####\n")
        full = tree(attrs, rows)
        print("=== Tree on the full training set ===")
        show_tree(attrs, full.root)
        print()
        summary = []
        for name, make in MODELS:
            cm, k, a = evaluate(attrs, rows, make)
            report(name, attrs, rows, cm, k, a)
            correct = sum(cm[c][c] for c in attrs[-1][1])
            summary.append((name, 100 * correct / len(rows), k, a))
        print(f"{'classifier':26} {'accuracy %':>10} {'kappa':>7} {'ROC area':>9}")
        for name, acc, k, a in summary:
            print(f"{name:26} {acc:10.2f} {k:7.4f} {a:9.4f}")
        print()


if __name__ == '__main__':
    # self-check: kappa for WEKA's J48 result on weather.nominal (5 4 / 3 2) is -0.0426
    check = {'yes': Counter({'yes': 5, 'no': 4}), 'no': Counter({'yes': 3, 'no': 2})}
    assert abs(kappa(check, ['yes', 'no']) + 0.0426) < 5e-4
    main(sys.argv[1:] or ['student.arff', 'employee.arff'])
