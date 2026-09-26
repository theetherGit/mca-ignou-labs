// customer_order.cpp -- MCSL-222 Session 8, Q20
// Figure 1.18 (Customer places Order, Order contains Product, OrderLine
// association class) implemented in C++17.
// Build: clang++ -std=c++17 -Wall -Wextra -o customer_order customer_order.cpp

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Order;
class Product;

// ------------------------------------------------------------- Product
class Product {
public:
    std::string P_Name;
    std::string P_Manufacturer;
    int Product_ID;
    double UnitPrice;
    int Units_in_Stock;

    Product(std::string name, std::string maker, int id, double price, int stock)
        : P_Name(std::move(name)), P_Manufacturer(std::move(maker)), Product_ID(id),
          UnitPrice(price), Units_in_Stock(stock) {}
};

// ----------------------------------------------------------- OrderLine
// The association class: one object per (Order, Product) pair, holding the
// attributes that belong to the link and not to either end.
class OrderLine {
public:
    Order* order;
    Product* product;
    int Quantity;
    double UnitSalePrice;

    double lineTotal() const { return Quantity * UnitSalePrice; }
};

// --------------------------------------------------------------- Order
class Order {
public:
    std::string OrderDate;
    std::string ProductSoldBy;
    double ProductOrderCost = 0.0;
    class Customer* customer = nullptr;  // back link of "places" (1..1)
    std::vector<OrderLine> lines;        // contains: Order (0..*) --> (1..*) Product

    Order(std::string date, std::string soldBy)
        : OrderDate(std::move(date)), ProductSoldBy(std::move(soldBy)) {}

    // Adds one Product to this Order through an OrderLine.
    bool contains(Product& p, int qty, double salePrice) {
        if (qty <= 0 || qty > p.Units_in_Stock) {
            std::cout << "  refused: only " << p.Units_in_Stock << " x " << p.P_Name
                      << " in stock, asked for " << qty << "\n";
            return false;
        }
        lines.push_back(OrderLine{this, &p, qty, salePrice});
        p.Units_in_Stock -= qty;
        ProductOrderCost += qty * salePrice;
        return true;
    }
};

// ------------------------------------------------------------ Customer
class Customer {
public:
    std::string C_Name;
    std::string C_Phone;
    std::string C_Address;
    std::string C_Pin;
    std::string C_Email;
    std::vector<Order*> orders;  // places: Customer (1..1) --> (0..*) Order

    Customer(std::string name, std::string phone, std::string addr, std::string pin,
             std::string email)
        : C_Name(std::move(name)), C_Phone(std::move(phone)), C_Address(std::move(addr)),
          C_Pin(std::move(pin)), C_Email(std::move(email)) {}

    void places(Order& o) {
        orders.push_back(&o);
        o.customer = this;
    }
};

// ---------------------------------------------------------------- main
static void printOrder(const Order& o) {
    std::cout << "Order dated " << o.OrderDate << " sold by " << o.ProductSoldBy
              << " for " << (o.customer ? o.customer->C_Name : "nobody") << "\n";
    for (const OrderLine& l : o.lines)
        std::cout << "  " << std::left << std::setw(12) << l.product->P_Name
                  << std::right << std::setw(3) << l.Quantity << " x "
                  << std::fixed << std::setprecision(2) << std::setw(9) << l.UnitSalePrice
                  << " = " << std::setw(9) << l.lineTotal() << "\n";
    std::cout << "  ProductOrderCost = " << std::fixed << std::setprecision(2)
              << o.ProductOrderCost << "\n";
}

int main() {
    Product pen("Pen", "Cello", 101, 10.00, 500);
    Product notebook("Notebook", "Classmate", 102, 45.00, 40);
    Product stapler("Stapler", "Kangaro", 103, 120.00, 3);

    Customer asha("Asha", "9876543210", "12 MG Road, Jaipur", "302001", "asha@example.com");

    Order o1("2026-09-01", "Store counter");
    Order o2("2026-09-15", "Online");
    asha.places(o1);
    asha.places(o2);

    o1.contains(pen, 20, 9.50);       // discounted sale price
    o1.contains(notebook, 5, 45.00);
    o2.contains(stapler, 2, 115.00);
    o2.contains(stapler, 2, 115.00);  // refused: only 1 left

    for (const Order* o : asha.orders) printOrder(*o);

    std::cout << "Stock left: pen " << pen.Units_in_Stock << ", notebook "
              << notebook.Units_in_Stock << ", stapler " << stapler.Units_in_Stock << "\n";
    std::cout << asha.C_Name << " has placed " << asha.orders.size() << " orders\n";
    return 0;
}
