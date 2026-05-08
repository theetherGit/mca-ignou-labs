---
title: Session 9
description: Javascript Asynchronous Programming
section: MCS-216 Section 2

---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-9/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-9/2.svelte"
  import Question3 from "$lib/components/demo/mcs-216/section-2/session-9/3.svelte"
</script>

<PrintButton />

JavaScript is inherently a **single-threaded, synchronous language**, meaning it executes code line-by-line from top to bottom. However, modern web applications frequently require tasks that take time to complete (e.g., fetching data from a server, waiting for user input, or running timers). If JavaScript waited for these tasks to finish before moving to the next line, the entire browser UI would freeze. This session introduces **Asynchronous Programming**, which allows JavaScript to initiate a long-running task, continue executing other code, and handle the result later using **callbacks**. This session covers the foundational async patterns required for responsive, non-blocking web applications.

## Objectives
- Understand the difference between synchronous and asynchronous execution
- Master callback functions as the primary mechanism for async flow control
- Implement built-in async methods: `setTimeout()` and `setInterval()`
- Load external resources dynamically using `XMLHttpRequest`
- Solve real-world async navigation and timing exercises

## Synchronous vs. Asynchronous Execution

| Feature | Synchronous | Asynchronous |
|---------|-------------|--------------|
| Execution Flow | Blocks until task completes | Starts task, moves to next line immediately |
| UI Impact | Freezes browser during long tasks | Keeps UI responsive |
| Example | `console.log("Start"); console.log("End");` | `setTimeout(() => console.log("End"), 2000);` |

## Callback Functions

A **callback** is a function passed as an argument to another function. It is **not executed immediately**; instead, it's "called back" at a later time when the parent function completes its task.

```js
// Function that accepts a callback
function fetchData(callback) {
  // Simulate delay
  setTimeout(() => {
    const data = "User Data Loaded";
    callback(data); // Execute callback when ready
  }, 1000);
}

// Pass callback WITHOUT parentheses
fetchData((result) => console.log(result)); // Logs after 1 second
```

## Built-in Async Timer Methods

| Method | Syntax | Behavior |
|--------|--------|----------|
| `setTimeout()` | setTimeout(callback, delayInMs) | Executes callback once after `delay` |
| `setInterval()` | setInterval(callback, intervalInMs) | Executes callback repeatedly every `interval` |
| `clearTimeout()` / `clearInterval()` | clearInterval(timerID) | Stops the scheduled execution |

```js
// Example: Live Clock
function updateClock() {
  const now = new Date();
  document.getElementById('clock').textContent = now.toLocaleTimeString();
}
const clockTimer = setInterval(updateClock, 1000); // Runs every second
clearInterval(clockTimer); // Stops it
```

## Loading External Resources (`XMLHttpRequest`)

Before `fetch()` became standard, `XMLHttpRequest` (XHR) was the primary way to load external files asynchronously.

```js
const xhr = new XMLHttpRequest();
xhr.open("GET", "external.html", true); // true = async
xhr.onload = function() {
  if (xhr.status === 200) {
    document.getElementById('container').innerHTML = xhr.responseText;
  }
};
xhr.send(); // Triggers the request
```

## Best Practices & Common Pitfalls

| Pitfall | Best Practice |
|---------|---------------|
| Passing `callback()` with parentheses | Pass function reference only: `setTimeout(myFunc, 1000)` not `setTimeout(myFunc(), 1000)` |
| Assuming code after `setTimeout` runs later | `setTimeout` schedules execution; code immediately after it runs first |
| Forgetting to clear intervals | Always store `setInterval` ID and use `clearInterval()` to prevent memory leaks |
| Nesting callbacks deeply ("Callback Hell") | Keep nesting shallow; use named functions or modern `Promise`/`async-await` in production |
| Ignoring XHR `status` codes | Always check `xhr.status === 200` before processing `responseText` |

## Quick Guide

```js
// ⏱️ Timers
const timeoutID = setTimeout(() => console.log("Once"), 2000);
clearTimeout(timeoutID);

const intervalID = setInterval(() => console.log("Repeated"), 1000);
clearInterval(intervalID);

// 🔄 Callback Pattern
function asyncTask(param, callback) {
  // Do work...
  callback(result);
}
asyncTask("data", (res) => console.log(res));

// 🌐 XMLHttpRequest (Lab Requirement)
const xhr = new XMLHttpRequest();
xhr.open("GET", "file.html", true);
xhr.onload = () => { if(xhr.status===200) console.log(xhr.responseText); };
xhr.send();
```

## Question 1

### Problem Statement

Implement a clock in HTML which shows the live time in the format `HH:MM:SS`. Use the JavaScript `setInterval()` method and a callback function by displaying the system time every second.

### Demo

<Question1 />

### Code

```html title="time.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-9/1.html

```


#### HTML View

<iframe
  id="preview-1"
  title="demo-q-1"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-9/1.html">
</iframe>


## Question 2

### Problem Statement

Sometimes we use external resource files in our HTML page. The content of an external file cannot be used until loaded completely. This can be implemented with JavaScript Callback. Design a web page which loads an external HTML file on the event: `onLoad`. Hint: use the inbuilt class `XMLHttpRequest()` to use its functions: `open()`, `onLoad()` etc. to load an external HTML file.

### Demo

<Question2 />

### Code

```html title="request.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-9/2.html

```


```html title="external.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-9/external.html

```


#### HTML View

<iframe
  id="preview-2"
  title="demo-q-2"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-9/2.html">
</iframe>


## Question 3

### Problem Statement

The village crows own an old scalpel that they occasionally use on special missions say, to cut through screen doors or packaging. To be able to quickly track it down, every time the scalpel is moved to another nest, an entry is added to the storage of both the nest that had it and the nest that took it, under the name "scalpel", with its new location as the value.This means that finding the scalpel is a matter of following the breadcrumb trail of storage entries, until you find a nest where that
points at the nest itself.

Write an async function locateScalpel that does this, starting at the nest on which it runs. You can use the anyStorage function defined earlier to access storage in arbitrary nests. The scalpel has been going around long enough that you may assume that every nest has a "scalpel" entry in its data storage.

### Demo

<Question3 />

### Code

```html title="scalpel.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-9/3.html

```


#### HTML View

<iframe
  id="preview-3"
  title="demo-q-3"
  width="100%"
  height="250px"
  class="mt-5 rounded-xl"
  src="/preview/mcs-216/section-2/session-9/3.html">
</iframe>
