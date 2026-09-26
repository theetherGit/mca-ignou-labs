/*
 * good_quality.c
 * Reads the marks of N students, prints the class average, the highest
 * marks, the grade of every student and the grade of the class average.
 *
 * Coding standard followed:
 *   - constants in UPPER_CASE, functions and variables in lower_snake_case
 *   - one task per function, main() only coordinates
 *   - four-space indentation, braces on every block
 *   - every function has a comment saying what it does and returns
 */
#include <stdio.h>

#define MAX_STUDENTS 100

/* Grade boundaries (marks out of 100). Change here, nowhere else. */
#define GRADE_A_MIN 90
#define GRADE_B_MIN 75
#define GRADE_C_MIN 60
#define GRADE_D_MIN 40

/* Reads marks for `count` students into `marks`. Returns nothing. */
static void read_marks(int marks[], int count)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("Marks of student %d: ", i + 1);
        scanf("%d", &marks[i]);
    }
}

/* Returns the arithmetic mean of `count` marks. Caller ensures count > 0. */
static float average_marks(const int marks[], int count)
{
    int i;
    int total = 0;

    for (i = 0; i < count; i++) {
        total += marks[i];
    }
    return (float) total / count;
}

/* Returns the largest value among `count` marks. */
static int highest_marks(const int marks[], int count)
{
    int i;
    int highest = marks[0];

    for (i = 1; i < count; i++) {
        if (marks[i] > highest) {
            highest = marks[i];
        }
    }
    return highest;
}

/* Maps a mark (or an average) to a letter grade. One place for the rule. */
static char grade_of(float marks)
{
    if (marks >= GRADE_A_MIN) {
        return 'A';
    }
    if (marks >= GRADE_B_MIN) {
        return 'B';
    }
    if (marks >= GRADE_C_MIN) {
        return 'C';
    }
    if (marks >= GRADE_D_MIN) {
        return 'D';
    }
    return 'F';
}

int main(void)
{
    int marks[MAX_STUDENTS];
    int count;
    int i;
    float average;

    printf("Enter number of students: ");
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_STUDENTS) {
        printf("Number of students must be between 1 and %d\n", MAX_STUDENTS);
        return 1;
    }

    read_marks(marks, count);
    average = average_marks(marks, count);

    printf("Average marks: %.2f\n", average);
    printf("Highest marks: %d\n", highest_marks(marks, count));

    for (i = 0; i < count; i++) {
        printf("Student %d: %d -> %c\n", i + 1, marks[i], grade_of(marks[i]));
    }
    printf("Class average grade: %c\n", grade_of(average));

    return 0;
}
