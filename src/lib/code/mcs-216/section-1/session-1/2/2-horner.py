def horner_rule_analysis(coeffs, x):
    # n is the degree (length of coeffs - 1)
    # result starts as the first coefficient (6 in this case)
    result = coeffs[0]

    mult_count = 0
    add_count = 0
    loop_count = 0

    # The loop starts from the second coefficient to the last
    for i in range(1, len(coeffs)):
        loop_count += 1

        # Every step involves 1 multiplication and 1 addition
        result = (result * x) + coeffs[i]

        mult_count += 1
        add_count += 1

    return result, mult_count, add_count, loop_count

# P(x) = 6x^6 + 5x^5 + 4x^4 - 3x^3 + 2x^2 + 8x - 7
coeffs = [6, 5, 4, -3, 2, 8, -7]
x_val = 3

res, m, a, lp = horner_rule_analysis(coeffs, x_val)

print(f"Result: {res}")
print(f"(a) Multiplications: {m}, Additions: {a}")
print(f"(b) Loop Iterations: {lp}")
