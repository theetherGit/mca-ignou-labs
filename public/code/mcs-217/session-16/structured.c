/*
 * structured.c
 * Same bank balance program as unstructured.c, rewritten with only
 * sequence, selection (if, switch) and iteration (while). Every function
 * has one entry and one exit. No goto, no flags carried across blocks.
 */
#include <stdio.h>

#define NOTE_BIG   500
#define NOTE_SMALL 200

static int balance = 0;

/*
 * Finds how many 500 and 200 notes add up to amount.
 * Returns 1 and fills *big, *small when possible, else returns 0.
 */
static int split_notes(int amount, int *big, int *small)
{
    int found = 0;
    int fives = amount / NOTE_BIG;

    while (!found && fives >= 0) {
        int rest = amount - fives * NOTE_BIG;
        if (rest % NOTE_SMALL == 0) {
            *big = fives;
            *small = rest / NOTE_SMALL;
            found = 1;
        }
        fives--;
    }
    return found;
}

/* Returns 0 on success, -1 bad amount, -2 insufficient funds, -3 no notes */
static int withdraw(int amount)
{
    int status = 0;
    int big = 0;
    int small = 0;

    if (amount <= 0) {
        status = -1;
    } else if (amount > balance) {
        status = -2;
    } else if (!split_notes(amount, &big, &small)) {
        status = -3;
    } else {
        balance -= amount;
        printf("Paid %d as %d x %d and %d x %d\n",
               amount, big, NOTE_BIG, small, NOTE_SMALL);
    }
    return status;
}

static void deposit(int amount)
{
    if (amount <= 0) {
        printf("Invalid amount\n");
    } else {
        balance += amount;
        printf("Deposited %d\n", amount);
    }
}

static void report_withdraw(int result)
{
    switch (result) {
    case -1:
        printf("Invalid amount\n");
        break;
    case -2:
        printf("Insufficient balance\n");
        break;
    case -3:
        printf("Amount cannot be paid in 500 and 200 notes\n");
        break;
    default:
        break;
    }
}

int main(void)
{
    int running = 1;
    int choice;
    int amount;

    while (running) {
        printf("\n1 Deposit  2 Withdraw  3 Balance  4 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            running = 0;
        } else {
            switch (choice) {
            case 1:
                printf("Amount: ");
                if (scanf("%d", &amount) != 1) {
                    running = 0;
                } else {
                    deposit(amount);
                }
                break;
            case 2:
                printf("Amount: ");
                if (scanf("%d", &amount) != 1) {
                    running = 0;
                } else {
                    report_withdraw(withdraw(amount));
                }
                break;
            case 3:
                printf("Balance: %d\n", balance);
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
        }
    }
    printf("Bye\n");
    return 0;
}
