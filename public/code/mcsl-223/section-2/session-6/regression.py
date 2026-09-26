#!/usr/bin/env python3
"""Simple linear regression by hand on a two-column numeric ARFF file.
Prints every intermediate sum so the slope and intercept can be checked on paper,
then the same error measures WEKA reports (correlation, MAE, RMSE).
Run: python3 regression.py study_marks.arff
"""
import math
import sys


def load_xy(path):
    rows, data = [], False
    for line in open(path):
        line = line.strip()
        if not line or line.startswith('%'):
            continue
        if line.lower() == '@data':
            data = True
        elif data:
            rows.append([float(v) for v in line.split(',')])
    return [r[0] for r in rows], [r[1] for r in rows]


def main(path):
    x, y = load_xy(path)
    n = len(x)
    xbar, ybar = sum(x) / n, sum(y) / n
    print(f"{'x':>4} {'y':>4} {'x-xbar':>7} {'y-ybar':>7} {'product':>8} {'(x-xbar)^2':>10}")
    sxy = sxx = syy = 0.0
    for xi, yi in zip(x, y):
        dx, dy = xi - xbar, yi - ybar
        sxy += dx * dy
        sxx += dx * dx
        syy += dy * dy
        print(f"{xi:4.0f} {yi:4.0f} {dx:7.2f} {dy:7.2f} {dx * dy:8.2f} {dx * dx:10.2f}")
    b1 = sxy / sxx
    b0 = ybar - b1 * xbar
    pred = [b0 + b1 * xi for xi in x]
    mae = sum(abs(p - yi) for p, yi in zip(pred, y)) / n
    rmse = math.sqrt(sum((p - yi) ** 2 for p, yi in zip(pred, y)) / n)
    r = sxy / math.sqrt(sxx * syy)
    print()
    print(f"n = {n}   x-bar = {xbar:.2f}   y-bar = {ybar:.2f}")
    print(f"Sxy = {sxy:.2f}   Sxx = {sxx:.2f}   Syy = {syy:.2f}")
    print(f"slope     b1 = Sxy / Sxx        = {b1:.4f}")
    print(f"intercept b0 = y-bar - b1 x-bar = {b0:.4f}")
    print(f"model: y = {b1:.4f} * x + {b0:.4f}")
    print()
    print(f"Correlation coefficient   {r:.4f}")
    print(f"Mean absolute error       {mae:.4f}")
    print(f"Root mean squared error   {rmse:.4f}")
    print()
    print(f"{'x':>4} {'actual':>6} {'predicted':>9} {'error':>6}")
    for xi, yi, p in zip(x, y, pred):
        print(f"{xi:4.0f} {yi:6.0f} {p:9.2f} {yi - p:6.2f}")
    print(f"prediction for x = 11: {b0 + b1 * 11:.2f}")
    # self-check: least-squares residuals always sum to zero
    assert abs(sum(yi - p for yi, p in zip(y, pred))) < 1e-9


if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else 'study_marks.arff')
