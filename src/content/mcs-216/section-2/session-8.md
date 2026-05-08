---
title: Session 8
description: Javascript Classes
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-8/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-8/2.svelte"
</script>

<PrintButton />

JavaScript Classes, introduced in ES6, provide a clean, syntactic sugar over JavaScript's prototype-based inheritance, enabling true object-oriented programming (OOP) patterns. While JavaScript has always supported objects and prototypes, classes offer a familiar, template-driven approach to defining blueprints for objects with shared properties and methods. This session shifts focus from procedural scripting to OOP design, covering class declarations, constructors, instantiation, getters/setters, and inheritance.

## Objectives

- Understand OOP architecture in JavaScript 
- Define classes and instantiate objects with methods
- Implement getters and setters for controlled property access
- Apply inheritance using extends and super
- Solve hands-on exercises modeling real-world entities (library books, products)

## What is a JavaScript Class?

- A class is a template/blueprint for creating objects.
- It encapsulates data (properties) and behavior (methods).
- Under the hood, classes still use JavaScript’s prototype chain, but the syntax is more readable and maintainable.

## Class Declarations vs. Expressions

| Type | Syntax | Hoisting/Scope |
|------|--------|----------------|
| **Declaration** | `class MyClass {}` | Not hoisted. Must be defined before use. Global/module scope. |
| **Expression** | `const MyClass = class {}` | Runs immediately. Scope limited to assignment. Can be named or unnamed. |

##  Constructor & Instantiation
- The constructor() method runs automatically when a new object is created. 
- Used to initialize instance properties. 
- Objects are instantiated using the new keyword.

```js
class Bike {
  constructor(make, year) {
    this.make = make;
    this.year = year;
  }
  getAge() {
    return new Date().getFullYear() - this.year;
  }
}
const myBike = new Bike("Honda", 2021);
console.log(myBike.getAge()); // e.g., 5
```

## Getters & Setters

- Allow controlled access and validation for internal properties.
- Syntax uses get and set keywords.

> Important: Getter/setter names must not match the internal property name to avoid infinite recursion.

```js
class User {
  constructor(name) { this._name = name; }
  get name() { return this._name; }
  set name(val) { 
    if (val.length > 0) this._name = val.toUpperCase(); 
  }
}
```

##  Inheritance (`extends` & `super`)
- Child classes inherit properties/methods from parent classes using `extends`.
- `super()` **must** be called in the child constructor before accessing `this`.
- Enables code reuse, method overriding, and polymorphism.

```js
class Animal {
  constructor(name) { this.name = name; }
  speak() { return `${this.name} makes a sound.`; }
}
class Dog extends Animal {
  constructor(name, breed) {
    super(name); // Calls parent constructor
    this.breed = breed;
  }
  speak() { return `${this.name} barks!`; } // Overrides parent method
}
```

## Best Practices & Common Pitfalls

| Pitfall | Best Practice |
|---------|---------------|
| Forgetting `super()` in derived constructor | Always call `super()` first in child class constructors |
| Naming **getters/setters** identical to properties | Use `_property` internally to prevent infinite recursion |
| Treating classes like functions | Classes are not hoisted; define before use |
| Overusing deep inheritance chains | Prefer composition when relationships aren't strict `is-a` |

## Quick Guide

```js
// 🔹 Basic Class
class Product {
  constructor(id, name) { this.id = id; this.name = name; }
  getInfo() { return `${this.id}: ${this.name}`; }
}

// 🔹 Getters & Setters
class User {
  constructor(age) { this._age = age; }
  get age() { return this._age; }
  set age(val) { if(val >= 0) this._age = val; }
}

// 🔹 Inheritance
class Student extends User {
  constructor(age, grade) { super(age); this.grade = grade; }
  status() { return `${this.age}yo, Grade ${this.grade}`; }
}
```

## Question 1

### Problem Statement

Let us assume you need to organize a library of some electronic manuals and novels for a particular company. For each book, you need to store following information:
- The title
- The author
- The copyright date
- The ISBN
- The number of pages
- The number of times the book has been checked out.
- Whether the book has been discarded

Company wants to perform certain actions when the any book is outdated. The manual books must be exited after 5 years while a novel book should be exited if its checked out time crossed 100.

**Task 1**.Construct three classes that hold the information needed by company. One class should be a **Book** class and two child classes of the Book class called **Manual** and **Novel**. Each class will contain two methods. One will be a constructor. The other one will either be in charge of disposal of the book or updating the property related to the number of times a book has been checked out.

**Task 2**: Create an object of the Novel class and Manual class with some valid details.

**Task 3**: Write the method to count the duration of a manual book and checkout time
for novel book so that they can be discarded based on the duration.

### Requirements
- Create `Book` base class + `Manual` & `Novel` child classes
- Store: title, author, copyright date, ISBN, pages, checkout count, discarded status
- Manual: discard if age > 5 years
- Novel: discard if checkouts > 100
- Each class: 1 constructor + 1 method (disposal or checkout update)
- Create objects & implement duration/checkout tracking

### Demo

<Question1 />

### Code

```html title="library.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-8/1.html

```


#### HTML View

<iframe
  id="preview"
  title="demo-q-1"
  width="100%"
  height="350px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-8/1.html">
</iframe>


## Question 2

### Problem Statement

Create a `product` with properties: ID, Name, Description and Price. The create function for this object called `displayProductDetails()`. This function when invoked should display the name, description and discounted price of the product. For the calculation of discounted price you need to create another function `CalculateDisc(percentage)`. The discount percentage would be given by user.

### Requirements

- Create `product` object with: ID, Name, Description, Price
- Method `displayProductDetails()` → shows name, description, discounted price
- Method `CalculateDisc(percentage)` → computes discounted price
- Discount percentage provided by user

### Demo

<Question2 />

### Code

```html title="product.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-8/2.html

```


#### HTML View

<iframe
  id="preview-2"
  title="demo-q-2"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-8/2.html">
</iframe>
