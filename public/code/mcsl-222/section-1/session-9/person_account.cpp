// person_account.cpp -- MCSL-222 Session 9, Q22
// Figure 1.17 (Person 1 has * BankAccount) implemented in C++17 as a ONE-WAY
// association: Person knows its accounts, BankAccount knows nothing of Person.
// Build: clang++ -std=c++17 -Wall -Wextra -o person_account person_account.cpp

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// --------------------------------------------------------- BankAccount
class BankAccount {
public:
    std::string Acc_No;
    double Acc_Balance;

    BankAccount(std::string no, double opening) : Acc_No(std::move(no)), Acc_Balance(opening) {}

    void Credit(double amount) {
        if (amount <= 0) {
            std::cout << "  refused: credit amount must be positive\n";
            return;
        }
        Acc_Balance += amount;
    }
    void Withdraw(double amount) {
        if (amount <= 0 || amount > Acc_Balance) {
            std::cout << "  refused: cannot withdraw " << amount << " from " << Acc_No
                      << " (balance " << Acc_Balance << ")\n";
            return;
        }
        Acc_Balance -= amount;
    }
};

// -------------------------------------------------------------- Person
class Person {
public:
    std::string Person_ID;
    std::string Name;
    std::vector<BankAccount*> accounts;  // has: Person (1) --> (*) BankAccount

    Person(std::string id, std::string name) : Person_ID(std::move(id)), Name(std::move(name)) {}

    void addAccount(BankAccount& a) { accounts.push_back(&a); }

    double totalBalance() const {
        double sum = 0;
        for (const BankAccount* a : accounts) sum += a->Acc_Balance;
        return sum;
    }
};

// ---------------------------------------------------------------- main
static void printPerson(const Person& p) {
    std::cout << p.Name << " (" << p.Person_ID << ") holds " << p.accounts.size()
              << " account(s)\n";
    for (const BankAccount* a : p.accounts)
        std::cout << "  " << a->Acc_No << "  balance " << std::fixed << std::setprecision(2)
                  << a->Acc_Balance << "\n";
    std::cout << "  total " << std::fixed << std::setprecision(2) << p.totalBalance() << "\n";
}

int main() {
    Person asha("P001", "Asha");
    BankAccount savings("SB-1001", 5000.00);
    BankAccount current("CA-2001", 12000.00);

    asha.addAccount(savings);
    asha.addAccount(current);

    std::cout << "--- after addAccount ---\n";
    printPerson(asha);

    std::cout << "--- Credit and Withdraw ---\n";
    savings.Credit(1500.00);
    current.Withdraw(2000.00);
    savings.Withdraw(9000.00);  // refused: more than balance
    current.Credit(-50.00);     // refused: not positive
    printPerson(asha);

    // One-way navigation: from an account there is no way back to Asha.
    // The line below would not compile, which is the point of the figure:
    // std::cout << savings.owner->Name;
    return 0;
}
