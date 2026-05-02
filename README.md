# Syntax Lab: MCA Lab Companion

Welcome to **Syntax Lab**, a digital handbook and deep-dive resource designed for IGNOU's **MCS-216** (DAA and Web Design) and **MCS-217** (Software Engineering) courses.

This project bridges the gap between academic requirements and modern software engineering practices by providing multi-language implementations and deep conceptual explanations.

## 🚀 Key Features

- **Polyglot Implementation**: Every logic-based problem is implemented in:
  - **Python**: For rapid prototyping and readability.
  - **C**: For low-level memory and hardware interaction (Primary for IGNOU).
  - **Rust**: For exploring modern memory safety and performance.
- **Deep Explanations**: We break down underlying logic, memory management, and algorithmic complexity.
- **Example-Driven Learning**: Real-world scenarios to help retain abstract concepts for exams and viva-voce.

## 🛠️ Local Environment Setup

To run the lab exercises locally, ensure you have the following installed:

| Language | Requirement | Recommended Version | Check Command |
| -------- | ----------- | ------------------- | ------------- |
| **C** | GCC or Clang | GCC 11+ | `gcc --version` | 
| **Python** | Python 3 | 3.10+ | `python3 --version` |
| **Rust** | Rust & Cargo | Stable (1.70+) | `rustc --version` |

### How to Run Code Directly

- **C**: `gcc filename.c -o solution && ./solution`
- **Python**: `python3 solution.py`
- **Rust**: `rustc solution.rs && ./solution` (or `cargo run`)

## 💻 Site Development

This site is built with SvelteKit and Velite.

### Prerequisites

- [Node.js](https://nodejs.org/) (Latest LTS)
- [pnpm](https://pnpm.io/)

### Installation

```bash
pnpm install
```

### Development Server

```bash
pnpm dev
```

### Building for Production

```bash
pnpm build
```

## ⚠️ Important Notice for Students

1. **Academic Integrity**: Use these resources to understand logic. Do not copy-paste code directly into lab journals.
2. **Exam Focus**: Ensure proficiency in C and Python, as they are the primary languages required by IGNOU.
3. **Viva-Voce**: Pay attention to the "Deep Explanation" sections in the documentation to prepare for oral exams.

## 📚 Official References

- [C Reference](https://en.cppreference.com/c)
- [Python Docs](https://docs.python.org/3/)
- [Rust Book](https://doc.rust-lang.org/book/)
- [IGNOU eGyanKosh](https://egyankosh.ac.in/)

---
Built with ❤️ by [The Ether](https://theether.in)
