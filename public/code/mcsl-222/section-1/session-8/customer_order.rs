// customer_order.rs -- MCSL-222 Session 8, Q20
// Figure 1.18 (Customer places Order, Order contains Product, OrderLine
// association class) in Rust 2021, standard library only.
// Ownership: Rc<RefCell<T>> for Product, Order and Customer; Customer holds Rc links to its orders and Order holds a Weak back link to its customer (1..1), so the two-way "places" link is not an Rc cycle.
// Build: rustc -O --edition 2021 customer_order.rs && ./customer_order
#![allow(non_snake_case)] // attribute names are kept exactly as in the figure
#![allow(dead_code)] // attributes the figure lists (phone, e-mail, manufacturer, ...) that main never reads

use std::cell::RefCell;
use std::rc::{Rc, Weak};

type Ref<T> = Rc<RefCell<T>>;

fn new_ref<T>(x: T) -> Ref<T> {
    Rc::new(RefCell::new(x))
}

// ------------------------------------------------------------- Product
struct Product {
    P_Name: String,
    P_Manufacturer: String,
    Product_ID: i32,
    UnitPrice: f64,
    Units_in_Stock: i32,
}

impl Product {
    fn new(name: &str, maker: &str, id: i32, price: f64, stock: i32) -> Ref<Product> {
        new_ref(Product {
            P_Name: name.into(),
            P_Manufacturer: maker.into(),
            Product_ID: id,
            UnitPrice: price,
            Units_in_Stock: stock,
        })
    }
}

// ----------------------------------------------------------- OrderLine
// The association class: one object per (Order, Product) pair, holding the
// attributes that belong to the link and not to either end.
struct OrderLine {
    order: Weak<RefCell<Order>>,
    product: Ref<Product>,
    Quantity: i32,
    UnitSalePrice: f64,
}

impl OrderLine {
    fn lineTotal(&self) -> f64 {
        f64::from(self.Quantity) * self.UnitSalePrice
    }
}

// --------------------------------------------------------------- Order
struct Order {
    OrderDate: String,
    ProductSoldBy: String,
    ProductOrderCost: f64,
    customer: Option<Weak<RefCell<Customer>>>, // back link of "places" (1..1)
    lines: Vec<OrderLine>,                     // contains: Order (0..*) --> (1..*) Product
}

impl Order {
    fn new(date: &str, sold_by: &str) -> Ref<Order> {
        new_ref(Order {
            OrderDate: date.into(),
            ProductSoldBy: sold_by.into(),
            ProductOrderCost: 0.0,
            customer: None,
            lines: Vec::new(),
        })
    }

    // Adds one Product to this Order through an OrderLine. Takes the order's
    // Rc so the line can keep a back link to it.
    fn contains(this: &Ref<Order>, p: &Ref<Product>, qty: i32, salePrice: f64) -> bool {
        let stock = p.borrow().Units_in_Stock;
        if qty <= 0 || qty > stock {
            println!("  refused: only {} x {} in stock, asked for {}", stock, p.borrow().P_Name, qty);
            return false;
        }
        let mut o = this.borrow_mut();
        o.lines.push(OrderLine {
            order: Rc::downgrade(this),
            product: Rc::clone(p),
            Quantity: qty,
            UnitSalePrice: salePrice,
        });
        p.borrow_mut().Units_in_Stock -= qty;
        o.ProductOrderCost += f64::from(qty) * salePrice;
        true
    }
}

// ------------------------------------------------------------ Customer
struct Customer {
    C_Name: String,
    C_Phone: String,
    C_Address: String,
    C_Pin: String,
    C_Email: String,
    orders: Vec<Ref<Order>>, // places: Customer (1..1) --> (0..*) Order
}

impl Customer {
    fn new(name: &str, phone: &str, addr: &str, pin: &str, email: &str) -> Ref<Customer> {
        new_ref(Customer {
            C_Name: name.into(),
            C_Phone: phone.into(),
            C_Address: addr.into(),
            C_Pin: pin.into(),
            C_Email: email.into(),
            orders: Vec::new(),
        })
    }

    fn places(this: &Ref<Customer>, o: &Ref<Order>) {
        this.borrow_mut().orders.push(Rc::clone(o));
        o.borrow_mut().customer = Some(Rc::downgrade(this));
    }
}

// ---------------------------------------------------------------- main
fn print_order(o: &Order) {
    let who = o
        .customer
        .as_ref()
        .and_then(Weak::upgrade)
        .map(|c| c.borrow().C_Name.clone())
        .unwrap_or_else(|| "nobody".to_string());
    println!("Order dated {} sold by {} for {}", o.OrderDate, o.ProductSoldBy, who);
    for l in &o.lines {
        println!(
            "  {:<12}{:>3} x {:>9.2} = {:>9.2}",
            l.product.borrow().P_Name,
            l.Quantity,
            l.UnitSalePrice,
            l.lineTotal()
        );
    }
    println!("  ProductOrderCost = {:.2}", o.ProductOrderCost);
}

fn main() {
    let pen = Product::new("Pen", "Cello", 101, 10.00, 500);
    let notebook = Product::new("Notebook", "Classmate", 102, 45.00, 40);
    let stapler = Product::new("Stapler", "Kangaro", 103, 120.00, 3);

    let asha = Customer::new("Asha", "9876543210", "12 MG Road, Jaipur", "302001", "asha@example.com");

    let o1 = Order::new("2026-09-01", "Store counter");
    let o2 = Order::new("2026-09-15", "Online");
    Customer::places(&asha, &o1);
    Customer::places(&asha, &o2);

    Order::contains(&o1, &pen, 20, 9.50); // discounted sale price
    Order::contains(&o1, &notebook, 5, 45.00);
    Order::contains(&o2, &stapler, 2, 115.00);
    Order::contains(&o2, &stapler, 2, 115.00); // refused: only 1 left

    for o in &asha.borrow().orders {
        print_order(&o.borrow());
    }

    println!(
        "Stock left: pen {}, notebook {}, stapler {}",
        pen.borrow().Units_in_Stock,
        notebook.borrow().Units_in_Stock,
        stapler.borrow().Units_in_Stock
    );
    println!("{} has placed {} orders", asha.borrow().C_Name, asha.borrow().orders.len());
}
