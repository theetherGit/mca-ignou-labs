"""Expense Splitter: a console re-implementation of the group expense
portion of a bill-splitting app (Splitwise style), written from observed
behaviour only. Python 3, standard library, no persistence.

All money is kept in paise (integers) so equal splits round exactly the
way the original app does: the leftover paise go to the first members.
"""


def to_paise(text):
    """Convert a rupee string such as '1200.50' to an integer of paise."""
    rupees, _, paise = text.strip().partition(".")
    paise = (paise + "00")[:2]
    return int(rupees or 0) * 100 + int(paise)


def fmt(paise):
    """Format paise as a rupee string, e.g. 120050 -> '1200.50'."""
    sign = "-" if paise < 0 else ""
    paise = abs(paise)
    return f"{sign}{paise // 100}.{paise % 100:02d}"


def equal_split(total, names):
    """Split total paise equally; remainder paise go to the first names."""
    base, extra = divmod(total, len(names))
    return {n: base + (1 if i < extra else 0) for i, n in enumerate(names)}


def balances(members, expenses):
    """Net balance per member: positive = is owed, negative = owes."""
    net = {m: 0 for m in members}
    for e in expenses:
        net[e["paid_by"]] += e["amount"]
        for name, share in e["shares"].items():
            net[name] -= share
    return net


def settle(net):
    """Greedy settlement: repeatedly pay the largest creditor from the
    largest debtor. Returns a list of (from, to, paise) transactions."""
    debtors = sorted(((v, k) for k, v in net.items() if v < 0))
    creditors = sorted(((v, k) for k, v in net.items() if v > 0), reverse=True)
    result = []
    i = j = 0
    while i < len(debtors) and j < len(creditors):
        owed, debtor = debtors[i]
        due, creditor = creditors[j]
        pay = min(-owed, due)
        result.append((debtor, creditor, pay))
        debtors[i] = (owed + pay, debtor)
        creditors[j] = (due - pay, creditor)
        if debtors[i][0] == 0:
            i += 1
        if creditors[j][0] == 0:
            j += 1
    return result


def pick_member(members, prompt):
    """Ask for a member name until it matches one in the group."""
    while True:
        name = input(prompt).strip()
        if name in members:
            return name
        print(f"  no such member: {name}. Members: {', '.join(members)}")


def add_member(members):
    name = input("Member name: ").strip()
    if not name or name in members:
        print("  name is empty or already in the group")
        return
    members.append(name)
    print(f"  added {name}")


def add_expense(members, expenses):
    if len(members) < 2:
        print("  add at least two members first")
        return
    desc = input("Description: ").strip() or "expense"
    amount = to_paise(input("Amount (rupees): "))
    if amount <= 0:
        print("  amount must be positive")
        return
    paid_by = pick_member(members, "Paid by: ")
    mode = input("Split equally (e) or custom shares (c)? ").strip().lower()
    if mode == "c":
        shares = {}
        for m in members:
            shares[m] = to_paise(input(f"  share of {m}: ") or "0")
        if sum(shares.values()) != amount:
            print(f"  shares total {fmt(sum(shares.values()))}, "
                  f"expense is {fmt(amount)}. Expense not added.")
            return
        shares = {k: v for k, v in shares.items() if v}
    else:
        shares = equal_split(amount, members)
    expenses.append({"desc": desc, "amount": amount,
                     "paid_by": paid_by, "shares": shares})
    print(f"  added '{desc}' {fmt(amount)} paid by {paid_by}")


def show_expenses(expenses):
    if not expenses:
        print("  no expenses yet")
    for n, e in enumerate(expenses, 1):
        parts = ", ".join(f"{k} {fmt(v)}" for k, v in e["shares"].items())
        print(f"  {n}. {e['desc']:<14} {fmt(e['amount']):>9}  "
              f"paid by {e['paid_by']:<8} shares: {parts}")


def show_balances(members, expenses):
    for name, net in balances(members, expenses).items():
        if net > 0:
            print(f"  {name:<8} gets back {fmt(net)}")
        elif net < 0:
            print(f"  {name:<8} owes      {fmt(-net)}")
        else:
            print(f"  {name:<8} settled up")


def show_settlement(members, expenses):
    txns = settle(balances(members, expenses))
    if not txns:
        print("  everyone is settled up")
    for frm, to, paise in txns:
        print(f"  {frm} pays {to} {fmt(paise)}")
    print(f"  ({len(txns)} transaction(s))")


MENU = """
1 Add member   2 Add expense   3 List expenses
4 Balances     5 Settle up     0 Exit
"""


def main():
    members, expenses = [], []
    actions = {"1": lambda: add_member(members),
               "2": lambda: add_expense(members, expenses),
               "3": lambda: show_expenses(expenses),
               "4": lambda: show_balances(members, expenses),
               "5": lambda: show_settlement(members, expenses)}
    while True:
        print(MENU)
        try:
            choice = input("Choice: ").strip()
        except EOFError:
            break
        if choice == "0":
            break
        actions.get(choice, lambda: print("  unknown choice"))()
    print("Bye")


if __name__ == "__main__":
    main()
