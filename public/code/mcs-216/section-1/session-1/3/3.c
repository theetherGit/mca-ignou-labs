#include <stdio.h>

int main() {
    int A[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    int B[4][4] = {{1,0,0,1}, {0,1,0,1}, {0,0,1,1}, {1,1,1,0}};
    int C[4][4] = {0};

    int outer_count = 0, inner_count = 0;
    int mul_count = 0, add_count = 0;

    for (int i = 0; i < 4; i++) {
        outer_count++;
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
                inner_count++;
                mul_count++;
                add_count++; // accumulation
            }
        }
    }

    printf("Result Matrix C:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) printf("%4d ", C[i][j]);
        printf("\n");
    }
    printf("\nOuter-most loop runs: %d times\n", outer_count);
    printf("Inner-most loop runs: %d times\n", inner_count);
    printf("Total Multiplications: %d\n", mul_count);
    printf("Total Additions: %d\n", add_count);
    return 0;
}
