# customer_order.py -- MCSL-222 Session 8, Q20
# Figure 1.18 (Customer places Order, Order contains Product, OrderLine
# association class) in Python 3, standard library only.
# Run: python3 customer_order.py
# eq=False keeps identity comparison, so the two-way Customer/Order links
# cannot recurse through a field-by-field ==.
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional


# ------------------------------------------------------------- Product
@dataclass(eq=False)
class Product:
    P_Name: str
    P_Manufacturer: str
    Product_ID: int
    UnitPrice: float
    Units_in_Stock: int


# ----------------------------------------------------------- OrderLine
# The association class: one object per (Order, Product) pair, holding the
# attributes that belong to the link and not to either end.
@dataclass(eq=False)
class OrderLine:
    order: Order
    product: Product
    Quantity: int
    UnitSalePrice: float

    def lineTotal(self) -> float:
        return self.Quantity * self.UnitSalePrice


# --------------------------------------------------------------- Order
@dataclass(eq=False)
class Order:
    OrderDate: str
    ProductSoldBy: str
    ProductOrderCost: float = 0.0
    customer: Optional[Customer] = None                    # back link of "places" (1..1)
    lines: list[OrderLine] = field(default_factory=list)  # contains: Order (0..*) --> (1..*) Product

    # Adds one Product to this Order through an OrderLine.
    def contains(self, p: Product, qty: int, salePrice: float) -> bool:
        if qty <= 0 or qty > p.Units_in_Stock:
            print(f"  refused: only {p.Units_in_Stock} x {p.P_Name} in stock, asked for {qty}")
            return False
        self.lines.append(OrderLine(self, p, qty, salePrice))
        p.Units_in_Stock -= qty
        self.ProductOrderCost += qty * salePrice
        return True


# ------------------------------------------------------------ Customer
@dataclass(eq=False)
class Customer:
    C_Name: str
    C_Phone: str
    C_Address: str
    C_Pin: str
    C_Email: str
    orders: list[Order] = field(default_factory=list)  # places: Customer (1..1) --> (0..*) Order

    def places(self, o: Order) -> None:
        self.orders.append(o)
        o.customer = self


# ---------------------------------------------------------------- main
def printOrder(o: Order) -> None:
    who = o.customer.C_Name if o.customer else "nobody"
    print(f"Order dated {o.OrderDate} sold by {o.ProductSoldBy} for {who}")
    for l in o.lines:
        print(f"  {l.product.P_Name:<12}{l.Quantity:>3} x {l.UnitSalePrice:>9.2f} = {l.lineTotal():>9.2f}")
    print(f"  ProductOrderCost = {o.ProductOrderCost:.2f}")


def main() -> None:
    pen = Product("Pen", "Cello", 101, 10.00, 500)
    notebook = Product("Notebook", "Classmate", 102, 45.00, 40)
    stapler = Product("Stapler", "Kangaro", 103, 120.00, 3)

    asha = Customer("Asha", "9876543210", "12 MG Road, Jaipur", "302001", "asha@example.com")

    o1 = Order("2026-09-01", "Store counter")
    o2 = Order("2026-09-15", "Online")
    asha.places(o1)
    asha.places(o2)

    o1.contains(pen, 20, 9.50)       # discounted sale price
    o1.contains(notebook, 5, 45.00)
    o2.contains(stapler, 2, 115.00)
    o2.contains(stapler, 2, 115.00)  # refused: only 1 left

    for o in asha.orders:
        printOrder(o)

    print(f"Stock left: pen {pen.Units_in_Stock}, notebook {notebook.Units_in_Stock}, "
          f"stapler {stapler.Units_in_Stock}")
    print(f"{asha.C_Name} has placed {len(asha.orders)} orders")


if __name__ == "__main__":
    main()
