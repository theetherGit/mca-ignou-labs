/*
 * matrix_multiply.c
 * MCS-217 Session 7: multiplication of two matrices using pointers.
 *
 * Each matrix is stored as one contiguous block of rows * cols ints
 * (row-major order). Element (i, j) lives at *(m + i * cols + j).
 * No arr[i][j] indexing is used anywhere; every access goes through
 * pointer arithmetic.
 *
 * Build: gcc -Wall -Wextra -o matrix_multiply matrix_multiply.c
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 100

/* Read one positive dimension. Returns 0 on failure. */
static int read_dim(const char *label, int *out)
{
    printf("%s", label);
    if (scanf("%d", out) != 1) {
        printf("Error: dimension must be an integer.\n");
        return 0;
    }
    if (*out < 1 || *out > MAX_DIM) {
        printf("Error: dimension must be between 1 and %d.\n", MAX_DIM);
        return 0;
    }
    return 1;
}

/* Allocate rows * cols ints and fill them from stdin, row by row.
   Returns NULL if allocation or input fails. */
int *read_matrix(const char *name, int rows, int cols)
{
    int *m = malloc((size_t)rows * (size_t)cols * sizeof(int));
    int *p;
    int i, j;

    if (m == NULL) {
        printf("Error: out of memory.\n");
        return NULL;
    }
    printf("Enter %d x %d elements of matrix %s, row by row:\n", rows, cols, name);
    p = m;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", p) != 1) {
                printf("Error: element (%d,%d) is not an integer.\n", i + 1, j + 1);
                free(m);
                return NULL;
            }
            p++;                       /* next element in row-major order */
        }
    }
    return m;
}

/* C = A x B where A is r1 x c1 and B is c1 x c2. C must hold r1 * c2 ints.
   Only pointer arithmetic is used to walk the three matrices. */
void multiply(const int *a, const int *b, int *c, int r1, int c1, int c2)
{
    int i, j, k;
    const int *arow;   /* start of row i of A */
    const int *bp;     /* walks down column j of B */
    int *cp = c;       /* walks C in row-major order */
    long sum;

    for (i = 0; i < r1; i++) {
        arow = a + i * c1;
        for (j = 0; j < c2; j++) {
            sum = 0;
            bp = b + j;                        /* B(0, j) */
            for (k = 0; k < c1; k++) {
                sum += (long)*(arow + k) * *bp; /* A(i,k) * B(k,j) */
                bp += c2;                       /* down one row in B */
            }
            *cp = (int)sum;
            cp++;
        }
    }
}

/* Print a rows x cols matrix, one row per line. */
void print_matrix(const char *title, const int *m, int rows, int cols)
{
    const int *p = m;
    int i, j;

    printf("%s (%d x %d):\n", title, rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%6d", *p);
            p++;
        }
        printf("\n");
    }
}

/* Release a matrix. Safe to call with NULL. */
void free_matrix(int *m)
{
    free(m);
}

int main(void)
{
    int r1, c1, r2, c2;
    int *a = NULL, *b = NULL, *c = NULL;

    if (!read_dim("Rows of A: ", &r1) || !read_dim("Columns of A: ", &c1) ||
        !read_dim("Rows of B: ", &r2) || !read_dim("Columns of B: ", &c2))
        return 1;

    if (c1 != r2) {
        printf("Error: columns of A (%d) must equal rows of B (%d). "
               "Multiplication not possible.\n", c1, r2);
        return 1;
    }

    a = read_matrix("A", r1, c1);
    if (a == NULL)
        return 1;
    b = read_matrix("B", r2, c2);
    if (b == NULL) {
        free_matrix(a);
        return 1;
    }
    c = malloc((size_t)r1 * (size_t)c2 * sizeof(int));
    if (c == NULL) {
        printf("Error: out of memory.\n");
        free_matrix(a);
        free_matrix(b);
        return 1;
    }

    multiply(a, b, c, r1, c1, c2);

    print_matrix("Matrix A", a, r1, c1);
    print_matrix("Matrix B", b, r2, c2);
    print_matrix("Product A x B", c, r1, c2);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
    return 0;
}
