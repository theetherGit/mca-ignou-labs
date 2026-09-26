# person_account.py -- MCSL-222 Session 9, Q22
# Figure 1.17 (Person 1 has * BankAccount) in Python 3, standard library only, as a
# ONE-WAY association: Person knows its accounts, BankAccount knows nothing of Person.
# Run: python3 person_account.py
from __future__ import annotations

from dataclasses import dataclass, field


# --------------------------------------------------------- BankAccount
@dataclass(eq=False)
class BankAccount:
    Acc_No: str
    Acc_Balance: float

    def Credit(self, amount: float) -> None:
        if amount <= 0:
            print("  refused: credit amount must be positive")
            return
        self.Acc_Balance += amount

    def Withdraw(self, amount: float) -> None:
        if amount <= 0 or amount > self.Acc_Balance:
            print(f"  refused: cannot withdraw {amount:.2f} from {self.Acc_No} "
                  f"(balance {self.Acc_Balance:.2f})")
            return
        self.Acc_Balance -= amount


# -------------------------------------------------------------- Person
@dataclass(eq=False)
class Person:
    Person_ID: str
    Name: str
    accounts: list[BankAccount] = field(default_factory=list)  # has: Person (1) --> (*) BankAccount

    def addAccount(self, a: BankAccount) -> None:
        self.accounts.append(a)

    def totalBalance(self) -> float:
        return sum(a.Acc_Balance for a in self.accounts)


# ---------------------------------------------------------------- main
def printPerson(p: Person) -> None:
    print(f"{p.Name} ({p.Person_ID}) holds {len(p.accounts)} account(s)")
    for a in p.accounts:
        print(f"  {a.Acc_No}  balance {a.Acc_Balance:.2f}")
    print(f"  total {p.totalBalance():.2f}")


def main() -> None:
    asha = Person("P001", "Asha")
    savings = BankAccount("SB-1001", 5000.00)
    current = BankAccount("CA-2001", 12000.00)

    asha.addAccount(savings)
    asha.addAccount(current)

    print("--- after addAccount ---")
    printPerson(asha)

    print("--- Credit and Withdraw ---")
    savings.Credit(1500.00)
    current.Withdraw(2000.00)
    savings.Withdraw(9000.00)  # refused: more than balance
    current.Credit(-50.00)     # refused: not positive
    printPerson(asha)

    # One-way navigation: from an account there is no way back to Asha.
    # The line below would raise AttributeError, which is the point of the figure:
    # print(savings.owner.Name)


if __name__ == "__main__":
    main()
