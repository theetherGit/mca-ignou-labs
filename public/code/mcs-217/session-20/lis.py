"""Library Information System (LIS), Session 20.

Console program, Python 3 standard library only, JSON persistence in
lis_data.json next to this file. Implements the Must-have requirements
LIS-FR-1 to LIS-FR-8 recorded in Session 19:
  members, catalogue, search, issue (max 3 books, 14 days), return,
  fine at 2 rupees per day beyond 14 days, reservation queue, reports.
Dates are entered as YYYY-MM-DD; blank means today, so the librarian can
back-date an issue to demonstrate the fine rule.
"""
import json
import os
from datetime import date, timedelta

DATA_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                         "lis_data.json")
LOAN_DAYS = 14
FINE_PER_DAY = 2
MAX_BOOKS = 3

# ---------------------------------------------------------------- storage


def load():
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE) as f:
            return json.load(f)
    return {"members": {}, "books": {}, "loans": [], "next_member": 1,
            "next_book": 1}


def save(db):
    with open(DATA_FILE, "w") as f:
        json.dump(db, f, indent=1)


def ask_date(prompt):
    """Read a YYYY-MM-DD date; blank returns today."""
    while True:
        text = input(prompt).strip()
        if not text:
            return date.today()
        try:
            return date.fromisoformat(text)
        except ValueError:
            print("  use YYYY-MM-DD")


def fine_for(due, returned):
    """LIS-FR-6: 2 rupees per day after the due date, else 0."""
    late = (returned - date.fromisoformat(due)).days
    return max(0, late) * FINE_PER_DAY


def open_loan(db, acc):
    """The unreturned loan record of a book, or None."""
    for loan in db["loans"]:
        if loan["book"] == acc and loan["returned"] is None:
            return loan
    return None

# ------------------------------------------------------------- librarian


def add_book(db):
    """LIS-FR-2: add a title to the catalogue with a new accession number."""
    acc = f"B{db['next_book']:03d}"
    book = {"title": input("Title: ").strip(),
            "author": input("Author: ").strip(),
            "subject": input("Subject: ").strip(),
            "status": "available", "reserved_by": []}
    if not book["title"]:
        print("  title is required")
        return
    db["books"][acc] = book
    db["next_book"] += 1
    print(f"  added {acc}: {book['title']}")


def register_member(db):
    """LIS-FR-1: register a member and give a member id."""
    name = input("Name: ").strip()
    phone = input("Phone: ").strip()
    if not name or not phone.isdigit() or len(phone) != 10:
        print("  name required, phone must be 10 digits")
        return
    mid = f"M{db['next_member']:03d}"
    db["members"][mid] = {"name": name, "phone": phone,
                          "joined": date.today().isoformat()}
    db["next_member"] += 1
    print(f"  registered {mid}: {name}")


def issue_book(db):
    """LIS-FR-4: issue an available book to a member for 14 days."""
    mid = input("Member id: ").strip()
    acc = input("Accession no: ").strip()
    member, book = db["members"].get(mid), db["books"].get(acc)
    if not member or not book:
        print("  unknown member or book")
        return
    if book["status"] == "issued":
        print("  already issued; member may reserve it")
        return
    if book["reserved_by"] and book["reserved_by"][0] != mid:
        print(f"  held for reservation by {book['reserved_by'][0]}")
        return
    held = sum(1 for l in db["loans"]
               if l["member"] == mid and l["returned"] is None)
    if held >= MAX_BOOKS:
        print(f"  member already holds {MAX_BOOKS} books")
        return
    issued = ask_date("Issue date (blank = today): ")
    due = issued + timedelta(days=LOAN_DAYS)
    db["loans"].append({"book": acc, "member": mid, "issued":
                        issued.isoformat(), "due": due.isoformat(),
                        "returned": None, "fine": 0})
    book["status"] = "issued"
    if book["reserved_by"] and book["reserved_by"][0] == mid:
        book["reserved_by"].pop(0)
    print(f"  issued {acc} to {member['name']}, due {due}")


def return_book(db):
    """LIS-FR-5 and LIS-FR-6: return a book and charge any fine."""
    acc = input("Accession no: ").strip()
    loan = open_loan(db, acc)
    if not loan:
        print("  that book is not issued")
        return
    returned = ask_date("Return date (blank = today): ")
    fine = fine_for(loan["due"], returned)
    loan["returned"], loan["fine"] = returned.isoformat(), fine
    book = db["books"][acc]
    book["status"] = "available"
    print(f"  returned {acc}; due was {loan['due']}, fine Rs {fine}")
    if book["reserved_by"]:
        who = db["members"][book["reserved_by"][0]]["name"]
        print(f"  reserved: keep aside for {book['reserved_by'][0]} ({who})")


def reports(db):
    """LIS-FR-8: books on loan, overdue list, fines collected."""
    today = date.today()
    print("  Books on loan:")
    for l in db["loans"]:
        if l["returned"] is None:
            flag = "OVERDUE" if date.fromisoformat(l["due"]) < today else ""
            print(f"    {l['book']} {db['books'][l['book']]['title']:<28}"
                  f" {l['member']} due {l['due']} {flag}")
    total = sum(l["fine"] for l in db["loans"])
    print(f"  Fines collected: Rs {total}")
    print(f"  Members: {len(db['members'])}, titles: {len(db['books'])}")

# ---------------------------------------------------------------- member


def search(db):
    """LIS-FR-3: search by any part of title, author or subject."""
    q = input("Search text: ").strip().lower()
    hits = [(acc, b) for acc, b in db["books"].items()
            if q in (b["title"] + b["author"] + b["subject"]).lower()]
    if not hits:
        print("  no matching books")
    for acc, b in hits:
        print(f"  {acc} {b['title']:<28} {b['author']:<18} {b['status']}")


def reserve(db, mid):
    """LIS-FR-7: queue for a book that is currently issued."""
    acc = input("Accession no: ").strip()
    book = db["books"].get(acc)
    if not book:
        print("  unknown book")
    elif book["status"] != "issued":
        print("  book is available, ask the librarian to issue it")
    elif mid in book["reserved_by"] or open_loan(db, acc)["member"] == mid:
        print("  you already hold or reserved this book")
    else:
        book["reserved_by"].append(mid)
        print(f"  reserved; you are number {len(book['reserved_by'])}")


def my_books(db, mid):
    """LIS-FR-5 support: what a member holds and the fine if returned now."""
    today = date.today()
    for l in db["loans"]:
        if l["member"] == mid and l["returned"] is None:
            print(f"  {l['book']} {db['books'][l['book']]['title']} "
                  f"due {l['due']} fine now Rs {fine_for(l['due'], today)}")
    print(f"  total fines paid so far: Rs "
          f"{sum(l['fine'] for l in db['loans'] if l['member'] == mid)}")

# ------------------------------------------------------------------ menus


def run_menu(title, actions):
    """Print a numbered menu until the user picks 0. Saves after each."""
    while True:
        print(f"\n{title}: " + "  ".join(f"{i} {name}" for i, (name, _) in
                                         enumerate(actions, 1)) + "  0 Back")
        choice = input("Choice: ").strip()
        if choice == "0":
            return
        if choice.isdigit() and 1 <= int(choice) <= len(actions):
            actions[int(choice) - 1][1]()
            save(DB)
        else:
            print("  unknown choice")


def librarian_menu():
    run_menu("Librarian", [("Add book", lambda: add_book(DB)),
                           ("Register member", lambda: register_member(DB)),
                           ("Issue", lambda: issue_book(DB)),
                           ("Return", lambda: return_book(DB)),
                           ("Reports", lambda: reports(DB))])


def member_menu():
    mid = input("Member id: ").strip()
    if mid not in DB["members"]:
        print("  unknown member id")
        return
    print(f"  welcome {DB['members'][mid]['name']}")
    run_menu("Member", [("Search", lambda: search(DB)),
                        ("Reserve", lambda: reserve(DB, mid)),
                        ("My books", lambda: my_books(DB, mid))])


DB = load()

if __name__ == "__main__":
    try:
        run_menu("LIS", [("Librarian", librarian_menu),
                         ("Member", member_menu)])
    except EOFError:
        pass
    save(DB)
    print("Data saved to", os.path.basename(DATA_FILE))
