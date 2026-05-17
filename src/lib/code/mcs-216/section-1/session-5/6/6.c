/*
 * strassen_complete.c
 * Strassen's Matrix Multiplication with Deterministic Operation Counting
 * Language: C11 | Layout: 1D Row-Major | Architecture: arm64/x86_64 compatible
 */

#include <stdio.h>
#include <stdlib.h>

/* Operation counter: tracks scalar arithmetic operations */
typedef struct { long mults; long adds; } OpCounter;

/* Row-major index helper: maps 2D (i,j) to 1D offset */
static inline size_t IDX(size_t i, size_t j, size_t n) { return i * n + j; }

/* Allocate zero-initialized n×n matrix (1D array) */
static double* alloc_mat(size_t n) {
    double* m = (double*)calloc(n * n, sizeof(double));
    if (!m) { fprintf(stderr, "Memory allocation failed\n"); exit(EXIT_FAILURE); }
    return m;
}

/* Element-wise addition with operation counting */
static void mat_add(const double* a, const double* b, double* c, size_t n, OpCounter* ctr) {
    for (size_t i = 0; i < n * n; i++) c[i] = a[i] + b[i];
    ctr->adds += (long)(n * n);
}

/* Element-wise subtraction with operation counting */
static void mat_sub(const double* a, const double* b, double* c, size_t n, OpCounter* ctr) {
    for (size_t i = 0; i < n * n; i++) c[i] = a[i] - b[i];
    ctr->adds += (long)(n * n);
}

/* Extract quadrant from parent matrix */
static void copy_quad(const double* src, double* dst, size_t src_n, size_t dst_n, size_t r, size_t c) {
    for (size_t i = 0; i < dst_n; i++)
        for (size_t j = 0; j < dst_n; j++)
            dst[IDX(i, j, dst_n)] = src[IDX(i + r, j + c, src_n)];
}

/* Merge 4 quadrants into full matrix */
static void merge_quads(double* C, const double* c11, const double* c12,
                        const double* c21, const double* c22, size_t n) {
    size_t m = n / 2;
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < m; j++) {
            C[IDX(i, j, n)]         = c11[IDX(i, j, m)];
            C[IDX(i, j + m, n)]     = c12[IDX(i, j, m)];
            C[IDX(i + m, j, n)]     = c21[IDX(i, j, m)];
            C[IDX(i + m, j + m, n)] = c22[IDX(i, j, m)];
        }
}

/* Recursive Strassen implementation */
void strassen(const double* A, const double* B, double* C, size_t n, OpCounter* ctr) {
    if (n == 1) { C[0] = A[0] * B[0]; ctr->mults++; return; }

    size_t m = n / 2;
    /* Allocate quadrants & temporaries */
    double *a11=alloc_mat(m),*a12=alloc_mat(m),*a21=alloc_mat(m),*a22=alloc_mat(m);
    double *b11=alloc_mat(m),*b12=alloc_mat(m),*b21=alloc_mat(m),*b22=alloc_mat(m);
    double *m1=alloc_mat(m),*m2=alloc_mat(m),*m3=alloc_mat(m),*m4=alloc_mat(m);
    double *m5=alloc_mat(m),*m6=alloc_mat(m),*m7=alloc_mat(m);
    double *s1=alloc_mat(m),*s2=alloc_mat(m),*s3=alloc_mat(m),*s4=alloc_mat(m);
    double *s5=alloc_mat(m),*s6=alloc_mat(m),*s7=alloc_mat(m),*s8=alloc_mat(m);
    double *s9=alloc_mat(m),*s10=alloc_mat(m),*tmp=alloc_mat(m);

    /* Split inputs into quadrants */
    copy_quad(A,a11,n,m,0,0); copy_quad(A,a12,n,m,0,m);
    copy_quad(A,a21,n,m,m,0); copy_quad(A,a22,n,m,m,m);
    copy_quad(B,b11,n,m,0,0); copy_quad(B,b12,n,m,0,m);
    copy_quad(B,b21,n,m,m,0); copy_quad(B,b22,n,m,m,m);

    /* Strassen's 7 products */
    mat_add(a11,a22,s1,m,ctr); mat_add(b11,b22,s2,m,ctr); strassen(s1,s2,m1,m,ctr);
    mat_add(a21,a22,s3,m,ctr); strassen(s3,b11,m2,m,ctr);
    mat_sub(b12,b22,s4,m,ctr); strassen(a11,s4,m3,m,ctr);
    mat_sub(b21,b11,s5,m,ctr); strassen(a22,s5,m4,m,ctr);
    mat_add(a11,a12,s6,m,ctr); strassen(s6,b22,m5,m,ctr);
    mat_sub(a21,a11,s7,m,ctr); mat_add(b11,b12,s8,m,ctr); strassen(s7,s8,m6,m,ctr);
    mat_sub(a12,a22,s9,m,ctr); mat_add(b21,b22,s10,m,ctr); strassen(s9,s10,m7,m,ctr);

    /* Combine results into C quadrants */
    double *c11=alloc_mat(m),*c12=alloc_mat(m),*c21=alloc_mat(m),*c22=alloc_mat(m);
    mat_add(m1,m4,c11,m,ctr); mat_sub(c11,m5,tmp,m,ctr); mat_add(tmp,m7,c11,m,ctr);
    mat_add(m3,m5,c12,m,ctr); mat_add(m2,m4,c21,m,ctr);
    mat_sub(m1,m2,c22,m,ctr); mat_add(c22,m3,tmp,m,ctr); mat_add(tmp,m6,c22,m,ctr);

    merge_quads(C,c11,c12,c21,c22,n);

    /* Clean up all temporary allocations */
    free(a11);free(a12);free(a21);free(a22);free(b11);free(b12);free(b21);free(b22);
    free(m1);free(m2);free(m3);free(m4);free(m5);free(m6);free(m7);
    free(s1);free(s2);free(s3);free(s4);free(s5);free(s6);free(s7);free(s8);free(s9);free(s10);
    free(tmp);free(c11);free(c12);free(c21);free(c22);
}

/* Standard O(n^3) multiplication for baseline comparison */
void naive_mul(const double* A, const double* B, double* C, size_t n, OpCounter* ctr) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < n; k++) {
                sum += A[IDX(i, k, n)] * B[IDX(k, j, n)];
                ctr->mults += 1;
                if (k > 0) ctr->adds += 1;
            }
            C[IDX(i, j, n)] = sum;
        }
    }
}

/* Initialize matrix with deterministic values */
void init_matrix(double* m, size_t n) {
    for (size_t i = 0; i < n * n; i++) m[i] = (double)(i + 1);
}

/* ================= ENTRY POINT ================= */
int main(void) {
    printf("%-4s | %-14s | %-13s | %-11s | %-10s\n", "n", "Strassen Mults", "Strassen Adds", "Naive Mults", "Naive Adds");
    printf("%-70s\n", "----------------------------------------------------------------------");

    size_t sizes[] = {2, 4, 8, 16, 32, 64};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (size_t idx = 0; idx < num_sizes; idx++) {
        size_t n = sizes[idx];
        double* A = alloc_mat(n); init_matrix(A, n);
        double* B = alloc_mat(n); init_matrix(B, n);
        double* C_str = alloc_mat(n);
        double* C_naive = alloc_mat(n);

        OpCounter ctr_str = {0, 0};
        strassen(A, B, C_str, n, &ctr_str);

        OpCounter ctr_naive = {0, 0};
        naive_mul(A, B, C_naive, n, &ctr_naive);

        printf("%-4zu | %-14ld | %-13ld | %-11ld | %-10ld\n",
               n, ctr_str.mults, ctr_str.adds, ctr_naive.mults, ctr_naive.adds);

        free(A); free(B); free(C_str); free(C_naive);
    }
    return 0;
}
