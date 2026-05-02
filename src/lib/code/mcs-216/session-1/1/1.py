def gcd_with_stats(a, b):
    """
    Computes GCD and tracks modulo and assignment operations.
    """
    mod_count = 0
    assign_count = 0

    # Absolute values for mathematical consistency
    a, b = abs(a), abs(b)
    assign_count += 2

    while b:
        # Modulo operation
        remainder = a % b
        mod_count += 1

        # Assignment operations (a = b, b = remainder)
        a = b
        b = remainder
        assign_count += 2

    return a, mod_count, assign_count

# Input values
val_a, val_b = 15265, 15
result, mods, assigns = gcd_with_stats(val_a, val_b)

print(f"GCD({val_a}, {val_b}) = {result}")
print(f"Modulo Operations: {mods}")
print(f"Assignment Operations: {assigns}")
