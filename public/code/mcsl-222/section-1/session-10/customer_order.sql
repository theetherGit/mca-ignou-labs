-- customer_order.sql -- MCSL-222 Session 10, Q23
-- Figure 1.18 (Customer, Order, Product, OrderLine) mapped to MySQL tables.
-- Run: mysql -u root -p < customer_order.sql

DROP DATABASE IF EXISTS customer_order;
CREATE DATABASE customer_order;
USE customer_order;

-- Rule 1: class -> table, attribute -> column, one surrogate primary key per table.
CREATE TABLE Customer (
    customer_id  INT AUTO_INCREMENT PRIMARY KEY,
    C_Name       VARCHAR(100) NOT NULL,
    C_Phone      VARCHAR(15),
    C_Address    VARCHAR(200),
    C_Pin        CHAR(6),
    C_Email      VARCHAR(100) UNIQUE
);

-- Product_ID already identifies a product in the figure, so it is the key.
CREATE TABLE Product (
    Product_ID      INT PRIMARY KEY,
    P_Name          VARCHAR(100) NOT NULL,
    P_Manufacturer  VARCHAR(100),
    UnitPrice       DECIMAL(10, 2) NOT NULL,
    Units_in_Stock  INT NOT NULL DEFAULT 0
);

-- Rule 2: one-to-many (Customer 1..1 places 0..* Order) -> foreign key on the
-- many side. NOT NULL because the multiplicity at Customer is exactly 1.
-- "Order" is a reserved word in SQL, so the table is named Orders.
CREATE TABLE Orders (
    order_id          INT AUTO_INCREMENT PRIMARY KEY,
    OrderDate         DATE NOT NULL,
    ProductSoldBy     VARCHAR(100),
    ProductOrderCost  DECIMAL(10, 2),
    customer_id       INT NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES Customer (customer_id)
);

-- Rule 3: many-to-many with an association class (Order 0..* contains 1..*
-- Product, OrderLine) -> junction table whose primary key is the pair of
-- foreign keys, plus the association-class attributes as columns.
CREATE TABLE OrderLine (
    order_id       INT NOT NULL,
    Product_ID     INT NOT NULL,
    Quantity       INT NOT NULL CHECK (Quantity > 0),
    UnitSalePrice  DECIMAL(10, 2) NOT NULL,
    PRIMARY KEY (order_id, Product_ID),
    FOREIGN KEY (order_id)   REFERENCES Orders (order_id) ON DELETE CASCADE,
    FOREIGN KEY (Product_ID) REFERENCES Product (Product_ID)
);

-- Sample rows (same data as the C++ program of Session 8, Q20)
INSERT INTO Customer (C_Name, C_Phone, C_Address, C_Pin, C_Email) VALUES
    ('Asha', '9876543210', '12 MG Road, Jaipur', '302001', 'asha@example.com'),
    ('Ravi', '9123456780', '4 FC Road, Pune',    '411004', 'ravi@example.com');

INSERT INTO Product (Product_ID, P_Name, P_Manufacturer, UnitPrice, Units_in_Stock) VALUES
    (101, 'Pen',      'Cello',     10.00, 500),
    (102, 'Notebook', 'Classmate', 45.00,  40),
    (103, 'Stapler',  'Kangaro',  120.00,   3);

INSERT INTO Orders (OrderDate, ProductSoldBy, ProductOrderCost, customer_id) VALUES
    ('2026-09-01', 'Store counter', 415.00, 1),
    ('2026-09-15', 'Online',        230.00, 1),
    ('2026-09-20', 'Online',         90.00, 2);

INSERT INTO OrderLine (order_id, Product_ID, Quantity, UnitSalePrice) VALUES
    (1, 101, 20,   9.50),
    (1, 102,  5,  45.00),
    (2, 103,  2, 115.00),
    (3, 102,  2,  45.00);

-- Walk the whole figure: Customer -> Orders -> OrderLine -> Product
SELECT c.C_Name,
       o.order_id,
       o.OrderDate,
       p.P_Name,
       ol.Quantity,
       ol.UnitSalePrice,
       ol.Quantity * ol.UnitSalePrice AS line_total
FROM Customer c
JOIN Orders    o  ON o.customer_id = c.customer_id
JOIN OrderLine ol ON ol.order_id   = o.order_id
JOIN Product   p  ON p.Product_ID  = ol.Product_ID
ORDER BY o.order_id, p.Product_ID;

-- Check that the stored ProductOrderCost agrees with the sum of its lines
SELECT o.order_id,
       o.ProductOrderCost,
       SUM(ol.Quantity * ol.UnitSalePrice) AS computed_cost
FROM Orders o
JOIN OrderLine ol ON ol.order_id = o.order_id
GROUP BY o.order_id, o.ProductOrderCost
ORDER BY o.order_id;
