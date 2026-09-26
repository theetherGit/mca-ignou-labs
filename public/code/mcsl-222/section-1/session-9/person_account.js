// person_account.js -- MCSL-222 Session 9, Q22
// Figure 1.17 (Person 1 has * BankAccount) in Node.js, no dependencies, as a
// ONE-WAY association: Person knows its accounts, BankAccount knows nothing of Person.
// Run: node person_account.js
"use strict";

// --------------------------------------------------------- BankAccount
class BankAccount {
  constructor(no, opening) {
    this.Acc_No = no;
    this.Acc_Balance = opening;
  }

  Credit(amount) {
    if (amount <= 0) {
      console.log("  refused: credit amount must be positive");
      return;
    }
    this.Acc_Balance += amount;
  }
  Withdraw(amount) {
    if (amount <= 0 || amount > this.Acc_Balance) {
      console.log(`  refused: cannot withdraw ${amount.toFixed(2)} from ${this.Acc_No} (balance ${this.Acc_Balance.toFixed(2)})`);
      return;
    }
    this.Acc_Balance -= amount;
  }
}

// -------------------------------------------------------------- Person
class Person {
  constructor(id, name) {
    this.Person_ID = id;
    this.Name = name;
    this.accounts = []; // has: Person (1) --> (*) BankAccount
  }

  addAccount(a) { this.accounts.push(a); }

  totalBalance() { return this.accounts.reduce((sum, a) => sum + a.Acc_Balance, 0); }
}

// ---------------------------------------------------------------- main
function printPerson(p) {
  console.log(`${p.Name} (${p.Person_ID}) holds ${p.accounts.length} account(s)`);
  for (const a of p.accounts) console.log(`  ${a.Acc_No}  balance ${a.Acc_Balance.toFixed(2)}`);
  console.log(`  total ${p.totalBalance().toFixed(2)}`);
}

function main() {
  const asha = new Person("P001", "Asha");
  const savings = new BankAccount("SB-1001", 5000.00);
  const current = new BankAccount("CA-2001", 12000.00);

  asha.addAccount(savings);
  asha.addAccount(current);

  console.log("--- after addAccount ---");
  printPerson(asha);

  console.log("--- Credit and Withdraw ---");
  savings.Credit(1500.00);
  current.Withdraw(2000.00);
  savings.Withdraw(9000.00); // refused: more than balance
  current.Credit(-50.00);    // refused: not positive
  printPerson(asha);

  // One-way navigation: from an account there is no way back to Asha.
  // The line below would throw (owner is undefined), which is the point of the figure:
  // console.log(savings.owner.Name);
}

main();
