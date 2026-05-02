def get_gcd(a, b):
    """
    Computes the GCD using the iterative Euclidean Algorithm.
    Works for any integer size in Python 3.
    """
    # Ensure we work with absolute values to handle negative inputs
    a, b = abs(a), abs(b)

    # Loop until the remainder (b) becomes 0
    while b != 0:
        # a % b calculates the remainder of a divided by b
        # We update a to be the previous b, and b to be the remainder
        a, b = b, a % b

    # When b is 0, a contains the GCD
    return a

# Example usage:
num1, num2 = 270, 192
print(f"GCD of {num1} and {num2} is: {get_gcd(num1, num2)}")
