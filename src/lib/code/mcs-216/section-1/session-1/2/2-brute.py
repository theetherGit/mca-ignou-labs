def brute_force_analysis(coeffs, x):
    n = len(coeffs) - 1 # The degree of the polynomial (6 in this case)
    total_sum = 0
    mult_count = 0
    add_count = 0

    # Loop through each coefficient and its index
    for i, coeff in enumerate(coeffs):
        # Calculate current power: e.g., for the first term (index 0), power is 6
        power = n - i

        # Calculate x^power by multiplying x, 'power' number of times
        current_pow_val = 1
        for _ in range(power):
            current_pow_val *= x
            mult_count += 1 # Tracking multiplications for powers

        # Multiply coefficient by the calculated power
        if power > 0:
            total_sum += coeff * current_pow_val
            mult_count += 1 # Tracking multiplication by coefficient
        else:
            # Constant term (x^0) has no power or coefficient multiplication
            total_sum += coeff

        # Every coefficient after the first one involves an addition operation
        if i > 0:
            add_count += 1

    return total_sum, mult_count, add_count

# P(x) = 6x^6 + 5x^5 + 4x^4 - 3x^3 + 2x^2 + 8x - 7
coeffs = [6, 5, 4, -3, 2, 8, -7]
res, m, a = brute_force_analysis(coeffs, 3)

print(f"Brute Force Result: {res}")
print(f"Total Multiplications: {m}")
print(f"Total Additions: {a}")
