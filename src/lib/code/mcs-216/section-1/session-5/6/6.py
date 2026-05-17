# 6.py
# Strassen's Matrix Multiplication with Deterministic Operation Counting
# Language: Python 3.x | Complexity: O(n^2.807) mults, O(n^2.807) adds
# Run: python3 6.py

class OpCounter:
    """Tracks scalar multiplications and additions/subtractions."""
    def __init__(self):
        self.mults = 0
        self.adds = 0

def add_mat(A, B, n, ctr):
    """Element-wise addition: C = A + B. n is the actual size of A and B."""
    C = [[A[i][j] + B[i][j] for j in range(n)] for i in range(n)]
    ctr.adds += n * n
    return C

def sub_mat(A, B, n, ctr):
    """Element-wise subtraction: C = A - B. n is the actual size of A and B."""
    C = [[A[i][j] - B[i][j] for j in range(n)] for i in range(n)]
    ctr.adds += n * n
    return C

def strassen(A, B, n, ctr):
    """Recursive Strassen multiplication. Base case: n=1."""
    if n == 1:
        ctr.mults += 1
        return [[A[0][0] * B[0][0]]]

    mid = n // 2

    # Extract quadrants (all are mid x mid)
    A11 = [row[:mid] for row in A[:mid]]
    A12 = [row[mid:] for row in A[:mid]]
    A21 = [row[:mid] for row in A[mid:]]
    A22 = [row[mid:] for row in A[mid:]]
    B11 = [row[:mid] for row in B[:mid]]
    B12 = [row[mid:] for row in B[:mid]]
    B21 = [row[:mid] for row in B[mid:]]
    B22 = [row[mid:] for row in B[mid:]]

    # 7 recursive products
    # FIX: All add_mat/sub_mat calls now correctly use `mid`, not `n`
    M1 = strassen(add_mat(A11, A22, mid, ctr), add_mat(B11, B22, mid, ctr), mid, ctr)
    M2 = strassen(add_mat(A21, A22, mid, ctr), B11, mid, ctr)
    M3 = strassen(A11, sub_mat(B12, B22, mid, ctr), mid, ctr)
    M4 = strassen(A22, sub_mat(B21, B11, mid, ctr), mid, ctr)
    M5 = strassen(add_mat(A11, A12, mid, ctr), B22, mid, ctr)
    M6 = strassen(sub_mat(A21, A11, mid, ctr), add_mat(B11, B12, mid, ctr), mid, ctr)
    M7 = strassen(sub_mat(A12, A22, mid, ctr), add_mat(B21, B22, mid, ctr), mid, ctr)

    # Combine quadrants into result
    # FIX: All helper calls correctly use `mid`
    C11 = add_mat(sub_mat(add_mat(M1, M4, mid, ctr), M5, mid, ctr), M7, mid, ctr)
    C12 = add_mat(M3, M5, mid, ctr)
    C21 = add_mat(M2, M4, mid, ctr)
    C22 = add_mat(sub_mat(add_mat(M1, M3, mid, ctr), M2, mid, ctr), M6, mid, ctr)

    # Merge into full n x n matrix
    C = [[0]*n for _ in range(n)]
    for i in range(mid):
        for j in range(mid):
            C[i][j] = C11[i][j]
            C[i][j+mid] = C12[i][j]
            C[i+mid][j] = C21[i][j]
            C[i+mid][j+mid] = C22[i][j]
    return C

def naive_multiply(A, B, n, ctr):
    """Standard O(n^3) multiplication for baseline comparison."""
    C = [[0]*n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                ctr.mults += 1
                if k > 0: ctr.adds += 1
                C[i][j] += A[i][k] * B[k][j]
    return C

def init_matrix(n):
    """Deterministic initialization for reproducible grading."""
    return [[(i * n + j + 1) for j in range(n)] for i in range(n)]

if __name__ == "__main__":
    print(f"{'n':<4} | {'Strassen Mults':<14} | {'Strassen Adds':<13} | {'Naive Mults':<11} | {'Naive Adds':<10}")
    print("-" * 85)

    sizes = [2, 4, 8, 16, 32, 64]
    for n in sizes:
        A = init_matrix(n)
        B = init_matrix(n)

        ctr_str = OpCounter()
        C_str = strassen(A, B, n, ctr_str)

        ctr_naive = OpCounter()
        C_naive = naive_multiply(A, B, n, ctr_naive)

        print(f"{n:<4} | {ctr_str.mults:<14} | {ctr_str.adds:<13} | {ctr_naive.mults:<11} | {ctr_naive.adds:<10}")
