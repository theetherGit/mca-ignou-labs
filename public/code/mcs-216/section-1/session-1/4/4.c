#include <stdio.h>

// Struct to hold our operation metrics
typedef struct {
    int loops;
    int mults;
} Metrics;

Metrics right_to_left(unsigned long long base, unsigned int exp) {
    Metrics m = {0, 0};
    unsigned long long res = 1;
    while (exp > 0) {
        m.loops++;
        if (exp & 1) {
            res *= base;
            m.mults++;
        }
        if (exp > 1) {
            base *= base;
            m.mults++;
        }
        exp >>= 1;
    }
    return m;
}

Metrics left_to_right(unsigned long long base, unsigned int exp) {
    Metrics m = {0, 0};
    unsigned long long res = 1;
    int msb = 0;

    // Find highest bit position
    for (int i = 31; i >= 0; i--) {
        if ((exp >> i) & 1) {
            msb = i;
            break;
        }
    }

    for (int i = msb; i >= 0; i--) {
        m.loops++;
        res *= res;
        m.mults++;
        if ((exp >> i) & 1) {
            res *= base;
            m.mults++;
        }
    }
    return m;
}

int main() {
    unsigned long long bases[] = {4, 3};
    unsigned int exps[] = {512, 31};

    for (int i = 0; i < 2; i++) {
        printf("--- Problem: %llu^%u ---\n", bases[i], exps[i]);

        Metrics r = right_to_left(bases[i], exps[i]);
        printf("R2L Method: Loops=%d, Multiplications=%d\n", r.loops, r.mults);

        Metrics l = left_to_right(bases[i], exps[i]);
        printf("L2R Method: Loops=%d, Multiplications=%d\n\n", l.loops, l.mults);
    }
    return 0;
}
