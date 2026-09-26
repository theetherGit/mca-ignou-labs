def right_to_left(base, exp):
    """Computes base^exp using Right-to-Left binary exponentiation."""
    result = 1
    running_square = base
    loops, multiplications = 0, 0

    temp_exp = exp
    while temp_exp > 0:
        loops += 1
        # If the bit is 1, multiply the result by current square
        if temp_exp % 2 == 1:
            result *= running_square
            multiplications += 1

        # Square the base for the next bit
        if temp_exp > 1:
            running_square *= running_square
            multiplications += 1

        temp_exp //= 2
    print(f"After processing bit: result={result}")
    return loops, multiplications


def left_to_right(base, exp):
    """Computes base^exp using Left-to-Right binary exponentiation."""
    result = 1
    loops, multiplications = 0, 0

    # Process bits from the Most Significant Bit to the Least
    binary_str = bin(exp)[2:]
    for bit in binary_str:
        loops += 1
        # Always square the result
        result *= result
        multiplications += 1

        # If the bit is 1, multiply by the original base
        if bit == "1":
            result *= base
            multiplications += 1
    print(f"After processing bit: result={result}")
    return loops, multiplications


def run_all():
    problems = [(4, 512), (3, 31)]
    for b, e in problems:
        print(f"--- Problem: {b}^{e} ---")

        r_loops, r_mults = right_to_left(b, e)
        print(f"R2L Method: Loops={r_loops}, Multiplications={r_mults}")

        l_loops, l_mults = left_to_right(b, e)
        print(f"L2R Method: Loops={l_loops}, Multiplications={l_mults}\n")


if __name__ == "__main__":
    run_all()
