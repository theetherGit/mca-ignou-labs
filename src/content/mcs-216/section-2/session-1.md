---
title: Session 1
description: Preliminaries
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />


Javascript is a high-level, interpreted programming language that is widely used for web development. It was created by Brendan Eich in 1995 and has since become one of the most popular programming languages in the world. JavaScript is primarily used for client-side scripting, allowing developers to create interactive and dynamic web pages. It can also be used on the server-side with environments like Node.js, Deno, Bun and Cloudflare Workers (don't mix with web workers).

In this session, we will introduce the basic JavsScript constructs, conditional statements amd control flow statements. Lab manual inlcudes good examples and exercises to practice these concepts.

<Callout type="note">
    <!--- space here --->
    Before trying the solutions provided for the exercises, try to solve them on your own. This will help you understand the concepts better and improve your problem-solving skills.<br/> <br />
    Also, Lab manual includes great examples before exercises, make sure to go through them as well.
    <!--- space here --->
</Callout>

## Objectives

The objectives of this session are to:
- Understand the basic JavaScript constructs
- Unserstand Conditional statements and control flow statements

## Arthimetic Operators

### Problem Statement

Q1: Write a JavaScript code to perform the two digit arithmetic operations: Addition, Subtraction, Multiplication and Division.

### Approach
To perform arithmetic operations on two digits, we can follow these steps:
- Define two variables to hold the digits we want to operate on.
- Use the arithmetic operators (`+`, `-`, `*`, `/`) to perform the desired operations.
- Print the results to the console.

### Code Implementation

```js title="arithmetic-operation.js" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-1/arithmetic-operation.js

```

### Explanation

- **Variables**: We use `const` (constant) because these values aren't changing during the script's execution. If you want to change them later, you would use `let`.

- **Arithmetic Operators**: JavaScript uses standard mathematical symbols: `+`, `-`, `*`, and `/`.

- **Console.log**: This is the standard method to print output to the debugging console.

- **Division Safety**: In computer science, "Division by Zero" is a common logical error. Including a conditional `if` check demonstrates good programming practice for your lab submission.

- **String Concatenation**: Using the `+` symbol between a string (text in quotes) and a variable allows us to combine them into a single readable sentence for the output.

## Pattern Printing

### Problem Statement
Q2: Write a JavaScript code to print 1 for 1 time 2 for 2 times, 3 for 3 times and so on up to 10.

### Approach

The goal is to create a visual pattern where each number `n` repeats itself `n` times on a single line. To achieve this, we need Nested Loops:

- **The Outer Loop** will act as a counter that moves from 1 to 10. This tells us which number we are currently processing.
- **The Inner Loop** will run based on the value of the outer loop. If the outer loop is at 5, the inner loop will execute 5 times to print the digit "5".
- We will collect the digits in a string for each row so they stay on the same line, then print that row before moving to the next number.

### Code Implementation

```js title="pattern-printing.js" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-1/pattern-printing.js

```

### Explanation

- **Nested Loop Logic**: Think of this like a clock. The outer loop is the "hour" hand (moving slowly), and the inner loop is the "minute" hand (completing a full cycle for every single step the hour hand takes).

- **Dynamic Range**: The inner loop condition `j <= i` is what makes the pattern triangular. Because the limit of the inner loop depends on the current value of the outer loop, the rows get progressively longer.

- **String Accumulation**: In JavaScript, `console.log()` automatically adds a new line. To get numbers like `2 2` on the same line, we must first build a string (`rowOutput`) and print it once the inner loop finishes its work for that row.

- **trim() Method**: We use `.trim()` at the end to remove the very last space of each row, ensuring the output is clean for your lab record.


## Portfolio Exercise

Q3: Discuss first with the group
