---
title: Session 7
description: Javascript Error Handling
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-7/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-7/2.svelte"
  import Question3 from "$lib/components/demo/mcs-216/section-2/session-7/3.svelte"
  import Question4 from "$lib/components/demo/mcs-216/section-2/session-7/4.svelte"
</script>

<PrintButton />

During script execution, errors are inevitable. They can stem from syntax mistakes, invalid user input, network failures, or unforeseen runtime conditions. Without proper error handling, a single failure can crash an entire application or leave users with broken interfaces. This session introduces JavaScript's structured error-handling mechanisms, enabling developers to gracefully catch, diagnose, and recover from runtime exceptions while keeping applications stable and user-friendly.

## Objectives

- Understand the `try...catch...finally` execution flow
- Implement custom `error` throwing using the `throw` statement
- Utilize JavaScript's built-in `Error` object to diagnose failures
- Apply nested `try...catch` blocks for complex validation scenarios
- Practice robust error handling through hands-on lab exercises

## Error Handling Syntax

JavaScript uses a structured block system to manage exceptions:

```js
try {
  // Code that might throw an error
} catch(error) {
  // Executes ONLY if an error occurs in try
  // `error` is an instance of the built-in Error object
} finally {
  // ALWAYS executes, regardless of success or failure
  // Ideal for cleanup, closing connections, resetting UI
}
```

### Execution Flow
1. `try` block runs.
2. If **no error** → skips `catch` → runs `finally`.
3. If **error occurs** → jumps to `catch` → runs `catch` → runs `finally`.

## The `throw` Statement
Allows you to create custom errors or re-throw caught errors:

```js
throw "Email cannot be empty";      // Throws a string
throw 404;                          // Throws a number
throw new Error("Custom validation failed"); // Throws an Error object (recommended)
```

## Built-in `Error` Object
When an error is caught, JavaScript provides an error object with two key properties:

| Property | Description |
|----------|-------------|
| error.name | Type of error (e.g., "TypeError", "ReferenceError") |
| error.message | Human-readable description of what went wrong |

## Error Types

| Error Name | Trigger Condition |
| ---------- | ----------------- |
| SyntaxError | Invalid JS syntax (e.g., missing brackets, 2 = x) |
| ReferenceError | Accessing an undeclared variable |
| TypeError | Invalid operation on a value type (e.g., "abc".toUpperCase on undefined) |
| RangeError | Number outside valid range (e.g., invalid array length) |
| EvalError | Error inside eval() function |
| URIError | Malformed URI in encoding/decoding functions |

## Nested `try...catch` Blocks

For complex validation, you can nest blocks to handle errors at different levels:
```js
try {
  // Outer validation
  try {
    // Inner risky operation
    JSON.parse(invalidJSON);
  } catch(innerErr) {
    console.warn("Inner failed:", innerErr.message);
    throw new Error("Data parsing failed"); // Re-throw to outer catch
  }
} catch(outerErr) {
  console.error("Outer caught:", outerErr.message);
} finally {
  console.log("Cleanup complete");
}
```

## Best Practices & Common Pitfalls

| Pitfall | Best Practice |
| ------- | ------------- |
| Empty catch `{}` blocks | Always log or handle the error; never silently swallow failures |
| Throwing non-Error values | Use throw new Error("msg") for consistent stack traces |
| Overusing try...catch for control flow | Use conditionals (if/else) for expected logic; reserve try...catch for true exceptions | 
| Ignoring finally for cleanup | Use finally to reset UI states, close streams, or hide loading spinners |
| Assuming all errors are recoverable | Some errors (e.g., SyntaxError) should be fixed at development time, not caught at runtime |

## Quick Guide

```js
// 🔍 Basic Error Handling
try { riskyOperation(); }
catch(err) { console.error(err.name, err.message); }
finally { console.log("Runs no matter what"); }

// 🚀 Custom Error
if (!userInput) throw new TypeError("Input is missing");

// 🔄 Retry Logic (Lab Exercise 4 pattern)
function safeMultiply(a, b) {
  while (true) {
    try { return primitiveMultiply(a, b); }
    catch (e) { if (e instanceof MultiplicatorUnitFailure) continue; else throw e; }
  }
}
```

## Question 1

### Problem Statement

Write an HTML code using JavaScript to add two numbers taken as input from user
and display the result of division operation on them i.e. a/b. If an error occurs, show
the error. Use error handling concepts in JavaScript.

### Preview

<Question1 />

### Code

```html title="add-division.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-7/1.html

```

#### HTML View

<iframe
  id="inlineFrameExample"
  title="Inline Frame Example"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-7/1.html">
</iframe>

## Question 2

### Problem Statement

A teacher has created a gradeLabs function that verifies if student programming labs work. This function loops over an array of JavaScript objects that should contain a student property and runLab property. The runLab property is expected to be a function containing the student's code. The runLab function is called and the result is compared to the expected result. If the result and expected result don't match, then the
lab is considered a failure.

### Demo 

<Question2 />

### Code

```html title="grade-lab.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-7/2.html

```

#### HTML View

<iframe
  id="inlineFrameExample"
  title="Inline Frame Example"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-7/2.html">
</iframe>

## Question 3

### Problem Statement

There is an array of animals. The user is asked to enter the index for the animal they want to see.
1. If the user enters an index that does NOT contain an animal, the code will throw a
TypeError when name is referenced on an undefined value.
2. Update the above program to print out the index the user entered. We want this
message to be printed EVERY time the code runs

### Demo 

<Question3 />

### Code

```html title="animals.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-7/3.html

```

#### HTML View

<iframe
  id="inlineFrameExample"
  title="Inline Frame Example"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-7/3.html">
</iframe>

## Question 4

### Problem Statement

Assume you have a function `primitiveMultiply` that in 20 percent of cases multiplies two numbers and in the other 80 percent of cases raises an exception of type `MultiplicatorUnitFailure`. Write a function that wraps this clunky function and just keeps trying until a call succeeds, after which it returns the result.
Make sure you handle only the exceptions you are trying to handle.

### Demo 

<Question4 />

### Code

```html title="primitive-multiplyn.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-7/4.html

```

#### HTML View

<iframe
  id="inlineFrameExample"
  title="Inline Frame Example"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-7/4.html">
</iframe>
