/*
 * reliable.c
 * Same task as unreliable.c: read N integers, print their mean, print the
 * value at a requested index. Every input is checked before it is used,
 * so the program either prints a correct answer or a clear error message.
 */
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10

/* Reads one int from stdin into *out. Returns 1 on success, 0 on failure. */
static int read_int(const char *prompt, int *out)
{
    printf("%s", prompt);
    return scanf("%d", out) == 1;
}

int main(void)
{
    int values[CAPACITY];
    int n;
    int i;
    int index;
    long long sum = 0;               /* cannot overflow for 10 int values */
    char prompt[40];

    if (!read_int("How many values: ", &n)) {
        printf("Error: count is not a number\n");
        return EXIT_FAILURE;
    }
    if (n < 1 || n > CAPACITY) {
        printf("Error: count must be between 1 and %d\n", CAPACITY);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        snprintf(prompt, sizeof prompt, "Value %d: ", i + 1);
        if (!read_int(prompt, &values[i])) {
            printf("Error: value %d is not a number\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < n; i++) {
        sum += values[i];
    }
    printf("Mean: %lld\n", sum / n); /* n >= 1 here, never divides by zero */

    snprintf(prompt, sizeof prompt, "Index to look up (0 to %d): ", n - 1);
    if (!read_int(prompt, &index)) {
        printf("Error: index is not a number\n");
        return EXIT_FAILURE;
    }
    if (index < 0 || index >= n) {
        printf("Error: index %d is out of range 0 to %d\n", index, n - 1);
        return EXIT_FAILURE;
    }
    printf("values[%d] = %d\n", index, values[index]);

    return EXIT_SUCCESS;
}
