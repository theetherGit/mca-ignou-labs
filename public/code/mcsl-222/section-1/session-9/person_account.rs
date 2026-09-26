// person_account.rs -- MCSL-222 Session 9, Q22
// Figure 1.17 (Person 1 has * BankAccount) in Rust 2021, standard library only, as a
// ONE-WAY association: Person knows its accounts, BankAccount knows nothing of Person.
// Ownership: BankAccount is an Rc<RefCell<BankAccount>> shared by main and Person.accounts; Person is a plain struct because nothing links back to it.
// Build: rustc -O --edition 2021 person_account.rs && ./person_account
#![allow(non_snake_case)] // attribute and operation names are kept exactly as in the figure

use std::cell::RefCell;
use std::rc::Rc;

type Ref<T> = Rc<RefCell<T>>;

// --------------------------------------------------------- BankAccount
struct BankAccount {
    Acc_No: String,
    Acc_Balance: f64,
}

impl BankAccount {
    fn new(no: &str, opening: f64) -> Ref<BankAccount> {
        Rc::new(RefCell::new(BankAccount { Acc_No: no.into(), Acc_Balance: opening }))
    }

    fn Credit(&mut self, amount: f64) {
        if amount <= 0.0 {
            println!("  refused: credit amount must be positive");
            return;
        }
        self.Acc_Balance += amount;
    }
    fn Withdraw(&mut self, amount: f64) {
        if amount <= 0.0 || amount > self.Acc_Balance {
            println!(
                "  refused: cannot withdraw {:.2} from {} (balance {:.2})",
                amount, self.Acc_No, self.Acc_Balance
            );
            return;
        }
        self.Acc_Balance -= amount;
    }
}

// -------------------------------------------------------------- Person
struct Person {
    Person_ID: String,
    Name: String,
    accounts: Vec<Ref<BankAccount>>, // has: Person (1) --> (*) BankAccount
}

impl Person {
    fn new(id: &str, name: &str) -> Person {
        Person { Person_ID: id.into(), Name: name.into(), accounts: Vec::new() }
    }

    fn addAccount(&mut self, a: &Ref<BankAccount>) {
        self.accounts.push(Rc::clone(a));
    }

    fn totalBalance(&self) -> f64 {
        self.accounts.iter().map(|a| a.borrow().Acc_Balance).sum()
    }
}

// ---------------------------------------------------------------- main
fn print_person(p: &Person) {
    println!("{} ({}) holds {} account(s)", p.Name, p.Person_ID, p.accounts.len());
    for a in &p.accounts {
        let a = a.borrow();
        println!("  {}  balance {:.2}", a.Acc_No, a.Acc_Balance);
    }
    println!("  total {:.2}", p.totalBalance());
}

fn main() {
    let mut asha = Person::new("P001", "Asha");
    let savings = BankAccount::new("SB-1001", 5000.00);
    let current = BankAccount::new("CA-2001", 12000.00);

    asha.addAccount(&savings);
    asha.addAccount(&current);

    println!("--- after addAccount ---");
    print_person(&asha);

    println!("--- Credit and Withdraw ---");
    savings.borrow_mut().Credit(1500.00);
    current.borrow_mut().Withdraw(2000.00);
    savings.borrow_mut().Withdraw(9000.00); // refused: more than balance
    current.borrow_mut().Credit(-50.00); // refused: not positive
    print_person(&asha);

    // One-way navigation: from an account there is no way back to Asha.
    // The line below would not compile, which is the point of the figure:
    // println!("{}", savings.borrow().owner.Name);
}
