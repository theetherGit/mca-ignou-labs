// customer_order.ts -- MCSL-222 Session 8, Q20
// Figure 1.18 (Customer places Order, Order contains Product, OrderLine
// association class) in TypeScript, no dependencies.
// Run: node customer_order.ts   (Node 22.18 or later strips the types itself)
"use strict";

// ------------------------------------------------------------- Product
class Product {
  readonly P_Name: string;
  readonly P_Manufacturer: string;
  readonly Product_ID: number;
  readonly UnitPrice: number;
  Units_in_Stock: number;

  constructor(name: string, maker: string, id: number, price: number, stock: number) {
    this.P_Name = name;
    this.P_Manufacturer = maker;
    this.Product_ID = id;
    this.UnitPrice = price;
    this.Units_in_Stock = stock;
  }
}

// ----------------------------------------------------------- OrderLine
// The association class: one object per (Order, Product) pair, holding the
// attributes that belong to the link and not to either end.
class OrderLine {
  readonly order: Order;
  readonly product: Product;
  readonly Quantity: number;
  readonly UnitSalePrice: number;

  constructor(order: Order, product: Product, qty: number, salePrice: number) {
    this.order = order;
    this.product = product;
    this.Quantity = qty;
    this.UnitSalePrice = salePrice;
  }

  lineTotal(): number { return this.Quantity * this.UnitSalePrice; }
}

// --------------------------------------------------------------- Order
class Order {
  readonly OrderDate: string;
  readonly ProductSoldBy: string;
  ProductOrderCost: number = 0.0;
  customer: Customer | null = null;   // back link of "places" (1..1)
  readonly lines: OrderLine[] = [];   // contains: Order (0..*) --> (1..*) Product

  constructor(date: string, soldBy: string) {
    this.OrderDate = date;
    this.ProductSoldBy = soldBy;
  }

  // Adds one Product to this Order through an OrderLine.
  contains(p: Product, qty: number, salePrice: number): boolean {
    if (qty <= 0 || qty > p.Units_in_Stock) {
      console.log(`  refused: only ${p.Units_in_Stock} x ${p.P_Name} in stock, asked for ${qty}`);
      return false;
    }
    this.lines.push(new OrderLine(this, p, qty, salePrice));
    p.Units_in_Stock -= qty;
    this.ProductOrderCost += qty * salePrice;
    return true;
  }
}

// ------------------------------------------------------------ Customer
class Customer {
  readonly C_Name: string;
  readonly C_Phone: string;
  readonly C_Address: string;
  readonly C_Pin: string;
  readonly C_Email: string;
  readonly orders: Order[] = []; // places: Customer (1..1) --> (0..*) Order

  constructor(name: string, phone: string, addr: string, pin: string, email: string) {
    this.C_Name = name;
    this.C_Phone = phone;
    this.C_Address = addr;
    this.C_Pin = pin;
    this.C_Email = email;
  }

  places(o: Order): void {
    this.orders.push(o);
    o.customer = this;
  }
}

// ---------------------------------------------------------------- main
function printOrder(o: Order): void {
  const who = o.customer ? o.customer.C_Name : "nobody";
  console.log(`Order dated ${o.OrderDate} sold by ${o.ProductSoldBy} for ${who}`);
  for (const l of o.lines) {
    console.log(`  ${l.product.P_Name.padEnd(12)}${String(l.Quantity).padStart(3)} x ` +
      `${l.UnitSalePrice.toFixed(2).padStart(9)} = ${l.lineTotal().toFixed(2).padStart(9)}`);
  }
  console.log(`  ProductOrderCost = ${o.ProductOrderCost.toFixed(2)}`);
}

function main(): void {
  const pen = new Product("Pen", "Cello", 101, 10.00, 500);
  const notebook = new Product("Notebook", "Classmate", 102, 45.00, 40);
  const stapler = new Product("Stapler", "Kangaro", 103, 120.00, 3);

  const asha = new Customer("Asha", "9876543210", "12 MG Road, Jaipur", "302001", "asha@example.com");

  const o1 = new Order("2026-09-01", "Store counter");
  const o2 = new Order("2026-09-15", "Online");
  asha.places(o1);
  asha.places(o2);

  o1.contains(pen, 20, 9.50);      // discounted sale price
  o1.contains(notebook, 5, 45.00);
  o2.contains(stapler, 2, 115.00);
  o2.contains(stapler, 2, 115.00); // refused: only 1 left

  for (const o of asha.orders) printOrder(o);

  console.log(`Stock left: pen ${pen.Units_in_Stock}, notebook ${notebook.Units_in_Stock}, stapler ${stapler.Units_in_Stock}`);
  console.log(`${asha.C_Name} has placed ${asha.orders.length} orders`);
}

main();
