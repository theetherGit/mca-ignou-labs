/*
 * unreliable.c
 * Reads N integers, prints their mean, then prints the value at a
 * requested index. Correct for well-formed input. Not reliable: it
 * trusts every value the user types.
 */
#include <stdio.h>

#define CAPACITY 10

int main(void)
{
    int values[CAPACITY];
    int n;
    int i;
    int index;
    int sum = 0;

    printf("How many values: ");
    scanf("%d", &n);                 /* return value ignored, n unchecked */

    for (i = 0; i < n; i++) {        /* writes past values[9] when n > 10 */
        printf("Value %d: ", i + 1);
        scanf("%d", &values[i]);
    }

    for (i = 0; i < n; i++) {
        sum += values[i];            /* int overflow for large values */
    }
    printf("Mean: %d\n", sum / n);   /* divides by zero when n is 0 */

    printf("Index to look up (0 to %d): ", n - 1);
    scanf("%d", &index);
    printf("values[%d] = %d\n", index, values[index]);  /* no range check */

    return 0;
}
