---
title: Getting Started
description: A quick guide to get started using Syntax Lab
section: Overview
---

<script>
	import { Callout } from "@ethercorps/kit";
</script>

This guide will help you set up your local environment and show you how to run the lab exercises across C, Python, and Rust. Whether you are working locally or need a quick online fix, we’ve got you covered.


## Local Environment Setup

Before running the code, ensure you have the necessary compilers and interpreters installed.

| Language | Requirement | Recommended Version | Check Command |
| -------- | ----------- | ------------------- | ------------- |
| C | GCC or Clang | GCC 11+ | gcc --version | 
| Python | Python 3 | 3.10+ | python3 --version |
| Rust |Rust & Cargo | Stable (1.70+) | rustc --version |

## How to Run Code Directly

### C (Compiled)
- Compile:
  ```sh
  gcc filename.c -o filename
  ```
- Execute: `./solution` (or `solution.exe` on `Windows`)

### Python (Interpreted)
- Execute:
  ```sh
  python3 solution.py
  ```

### Rust (Systems)
- Quick Run: 
  ```bash 
  rustc solution.rs && ./solution
  ```
- Modern Way: If using Cargo, just run 
  ```bash
  cargo run
  ```

## Online Playgrounds

If you are away from your main machine or having setup issues, use these highly reliable online environments:

- [GDB Online](https://www.onlinegdb.com/): Best for C and Python. It features a built-in debugger which is great for tracing logic during labs.

- [Rust Playground](https://play.rust-lang.org/?version=stable&mode=debug): The official "scratchpad" for Rust. It allows you to test code and even see the assembly/LLVM output.

- [Replit](https://replit.com/): A full collaborative IDE. You can create a "Repl" for any of the three languages and share the link with the group to debug together in real-time.

- [Programiz Online Compiler](https://www.programiz.com/): Very lightweight and fast for quick logic checks in C and Python.

## Official Reference Docs

0. **C Reference**: [cppreference.com (C section)](https://en.cppreference.com/c) — The gold standard for C syntax and standard libraries.

0. **Python Docs**: [docs.python.org](https://doc.rust-lang.org/book/) — Excellent for looking up built-in functions and library modules.

0. **Rust Book**: [doc.rust-lang.org/book/](https://doc.rust-lang.org/book/) — Known as "The Book," it is the best way to understand Rust's unique ownership model.

0. **GNOU MCA Portal**: [eGyanKosh](https://egyankosh.ac.in/) — For your official MCS-216 and MCS-217 course material and lab manuals.

## Quick Tips for Success

- **Terminal Pro-Tip**: Use the `Tab` key to auto-complete file names in your terminal. It saves time and prevents typos.

- **Consistent Formatting**: We recommend using the **Zed** or **VS Code** editor. Using a consistent editor helps us troubleshoot each other's code much faster.

- **Errors are Teachers**: In **Rust** and *C*, the compiler error usually tells you exactly what is wrong. Read the full error message before asking for help!
