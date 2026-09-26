#!/usr/bin/env python3
"""plot_cwnd.py -- MCSL-223 Session 9, Q24.

Reads cwnd.txt ("time cwnd" per line, written by dumbbell-rate2.cc) and
draws the congestion window against time with vertical markers at the two
UDP rate changes.

Usage:  python3 plot_cwnd.py [cwnd.txt] [cwnd.png]
Needs:  matplotlib  (pip install matplotlib)
"""

import sys

import matplotlib

matplotlib.use("Agg")  # write a file, no display needed
import matplotlib.pyplot as plt  # noqa: E402

RATE1_TIME, RATE1 = 20.0, "Rate1 = 500 kbit/s (half the bridge)"
RATE2_TIME, RATE2 = 30.0, "Rate2 = 1 Mbit/s (whole bridge)"


def read_trace(path):
    """Return two lists, time in seconds and cwnd in bytes."""
    times, cwnds = [], []
    with open(path) as f:
        for line in f:
            parts = line.split()
            if len(parts) == 2:
                times.append(float(parts[0]))
                cwnds.append(int(parts[1]))
    return times, cwnds


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else "cwnd.txt"
    out = sys.argv[2] if len(sys.argv) > 2 else "cwnd.png"
    times, cwnds = read_trace(src)
    if not times:
        sys.exit(f"{src}: no samples found")

    top = max(cwnds)
    plt.figure(figsize=(9, 5))
    plt.step(times, cwnds, where="post", lw=1.2, label="cwnd (bytes)")
    plt.axvline(RATE1_TIME, color="tab:orange", ls="--")
    plt.text(RATE1_TIME + 0.3, top * 0.95, RATE1, color="tab:orange")
    plt.axvline(RATE2_TIME, color="tab:red", ls="--")
    plt.text(RATE2_TIME + 0.3, top * 0.85, RATE2, color="tab:red")
    plt.xlabel("Time (s)")
    plt.ylabel("Congestion window (bytes)")
    plt.title("TCP cwnd on the 1 Mbit/s dumbbell bridge under UDP load")
    plt.grid(alpha=0.3)
    plt.legend(loc="upper left")
    plt.tight_layout()
    plt.savefig(out, dpi=120)
    print(f"wrote {out}: {len(times)} samples, max cwnd {top} bytes, last {cwnds[-1]} bytes")


if __name__ == "__main__":
    main()
