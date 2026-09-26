/*
 * unstructured.c
 * Menu-driven bank balance: deposit, withdraw, show balance, exit.
 * Withdrawals are paid out in 500 and 200 rupee notes only.
 * Works, but the control flow is built from goto, flags and early returns.
 */
#include <stdio.h>

int balance = 0;
int flag = 0;      /* 0 = nothing, 1 = notes found, 2 = error already printed */

/* Returns 0 on success, -1 bad amount, -2 insufficient funds, -3 no notes */
int withdraw(int amount)
{
    int fives, twos;
    if (amount <= 0)
        return -1;
    if (amount > balance)
        return -2;
    flag = 0;
    for (fives = amount / 500; fives >= 0; fives--) {
        for (twos = 0; twos * 200 <= amount; twos++) {
            if (fives * 500 + twos * 200 == amount) {
                flag = 1;
                goto found;
            }
        }
    }
found:
    if (flag != 1)
        return -3;
    balance -= amount;
    printf("Paid %d as %d x 500 and %d x 200\n", amount, fives, twos);
    return 0;
}

int main(void)
{
    int choice, amount, result;
menu:
    printf("\n1 Deposit  2 Withdraw  3 Balance  4 Exit\nChoice: ");
    if (scanf("%d", &choice) != 1)
        goto quit;
    if (choice == 1)
        goto deposit;
    if (choice == 2)
        goto withdraw;
    if (choice == 3)
        goto show;
    if (choice == 4)
        goto quit;
    printf("Invalid choice\n");
    goto menu;
deposit:
    printf("Amount: ");
    if (scanf("%d", &amount) != 1)
        goto quit;
    flag = 0;
    if (amount <= 0) {
        printf("Invalid amount\n");
        flag = 2;
    }
    if (flag == 2)
        goto menu;
    balance += amount;
    printf("Deposited %d\n", amount);
    goto menu;
withdraw:
    printf("Amount: ");
    if (scanf("%d", &amount) != 1)
        goto quit;
    result = withdraw(amount);
    if (result == -1)
        printf("Invalid amount\n");
    if (result == -2)
        printf("Insufficient balance\n");
    if (result == -3)
        printf("Amount cannot be paid in 500 and 200 notes\n");
    goto menu;
show:
    printf("Balance: %d\n", balance);
    goto menu;
quit:
    printf("Bye\n");
    return 0;
}
