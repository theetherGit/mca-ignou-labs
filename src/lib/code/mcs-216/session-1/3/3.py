def matrix_multiply_4x4(A, B):
    C = [[0]*4 for _ in range(4)]
    outer_count = inner_count = mul_count = add_count = 0

    for i in range(4):
        outer_count += 1
        for j in range(4):
            for k in range(4):
                C[i][j] += A[i][k] * B[k][j]
                inner_count += 1
                mul_count += 1
                add_count += 1

    return C, outer_count, inner_count, mul_count, add_count

A = [[1,2,3,4], [5,6,7,8], [9,10,11,12], [13,14,15,16]]
B = [[1,0,0,1], [0,1,0,1], [0,0,1,1], [1,1,1,0]]

C, outer, inner, mul, add = matrix_multiply_4x4(A, B)

print("Result Matrix C:")
for row in C:
    print([f"{x:4}" for x in row])
print(f"\nOuter-most loop runs: {outer} times")
print(f"Inner-most loop runs: {inner} times")
print(f"Total Multiplications: {mul}")
print(f"Total Additions: {add}")
