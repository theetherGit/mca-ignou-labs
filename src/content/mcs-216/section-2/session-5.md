---
title: Session 5
description: JavaScript HTML DOM Events and Event Listener
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-5/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-5/2.svelte"
  import Question3 from "$lib/components/demo/mcs-216/section-2/session-5/3.svelte"
  import Question4 from "$lib/components/demo/mcs-216/section-2/session-5/4.svelte"
</script>

<PrintButton />

In Session 4, you learned how to access and manipulate HTML elements using the DOM. Session 5 builds upon this foundation by introducing DOM Events, which enable web pages to react dynamically to user actions and browser occurrences. Events are the bridge between static HTML and interactive JavaScript, allowing scripts to execute in response to triggers like mouse clicks, page loads, keyboard input, or form submissions.

This session shifts focus from inline event attributes (e.g., `onclick="func()"`) to the modern, standardized Event Listener API. You will learn how to attach, manage, and remove event handlers using `addEventListener()` and `removeEventListener()`, understand event propagation (bubbling vs. capturing), and implement multiple independent listeners on a single element. By the end of this session, you will be able to design responsive, event-driven web interfaces while maintaining clean separation between HTML structure and JavaScript behavior.


## Objectives

- Understand common HTML DOM events and their triggers
- Attach event handlers using `addEventListener()` without overwriting existing ones
- Control event propagation using the `useCapture` parameter (bubbling vs. capturing)
- Remove event listeners dynamically using `removeEventListener()`
- Implement practical event-driven interactions through hands-on exercises

## DOM Events

DOM events are signals that something has occurred in the browser or with a specific HTML element. JavaScript can listen for these signals and execute code when they fire.

| Event Category | Common Examples | Trigger |
|----------------|-----------------|---------|
| Mouse | `click`, `dblclick`, `mouseover`, `mouseout`, `mousedown`, `mouseup` | User interacts with pointing device|
| Keyboard | `keydown`, `keyup`, `keypress` | User presses/releases keys |
| Form/Input | `change`, `input`, `submit`, `focus`, `blur` | User modifies or submits form data |
| Window/Document | `load`, `DOMContentLoaded`, `resize`, `scroll` | Page lifecycle or viewport changes |
| Media/Image | `load` (on `<img>`), `play`, `pause` | Resource state changes |

## Event Handling Evolution

| Approach | Syntax | <span style="display: inline-block; width:300px">Pros</span> | <span style="display: inline-block; width:300px">Cons</span> |
|----------|--------|------|------|
| Inline HTML | `<button onclick="myFunc()">` | Quick to write | Mixes HTML & JS, hard to maintain, overwrites if duplicated |
| DOM Property | `btn.onclick = myFunc;` | Simple separation | Only allows one handler per event type (overwrites previous) |
| Event Listener | `btn.addEventListener("click", myFunc);` | Recommended: supports multiple handlers, clean separation, modern standard | Slightly more verbose |

## Syntax & Parameters

### addEventListener()

```js
element.addEventListener(event, function, useCapture);
```

| Parameter | Description |
|:---------:|-------------|
| `event` | String name of the event (e.g., "`click`", "`load`", "`change`") |
| `function` | Callback to execute when event fires (named function or anonymous) | 
| `useCapture` | Optional Boolean. `false` = Bubbling (default), `true` = Capturing |

**Key Advantage**: Unlike `.onclick =`, `addEventListener` does not overwrite existing handlers. You can attach multiple listeners to the same element for the same event.

```js
// Multiple listeners on one button
btn.addEventListener("click", firstAction);
btn.addEventListener("click", secondAction); // Both will run!
```

### removeEventListener()

Dynamically detaches a previously attached listener. Crucial: The function reference passed to removeEventListener must be the exact same function used in addEventListener. Anonymous functions cannot be removed directly.

```js
// ✅ Correct: Named function
function showAlert() { alert("Hello"); }
btn.addEventListener("click", showAlert);
btn.removeEventListener("click", showAlert);

// ❌ Incorrect: Anonymous functions are unique instances
btn.addEventListener("click", function() { alert("Hello"); });
// btn.removeEventListener("click", function() { alert("Hello"); }); // Won't work!
```

## Event Propagation

When nested elements have event listeners, the browser must decide the execution order. This is called **event propagation**.

| Mode | Order of Execution | `useCapture` Value |
| ---- | ------------------ | ------------------ |
| **Bubbling** (Default) | Innermost element → Outermost parent | `false` |
| **Capturing** | Outermost parent → Innermost element | `true` |

### Example

```html
<div id="outer">
  <p id="inner">Click me</p>
</div>
```
- If `<p>` is clicked with bubbling: `<p>` handler runs first, then `<div>` handler.
- If `<p>` is clicked with capturing: `<div>` handler runs first, then `<p>` handler.

## Best Practices & Common Pitfalls

| Pitfall | Best Practice |
| ------- | ------------- |
| Using inline `onclick` in modern projects | Use `addEventListener()` for separation of concerns |
| Attaching listeners inside loops without caching | Cache elements: `const btn = document.getElementById("x")`; then attach once |
| Forgetting event type strings must be lowercase | Use "`click`" not "`Click`" or "`onclick`" |
| Passing anonymous functions to `removeEventListener` | Always use named functions or store references if removal is needed |
| Ignoring `preventDefault()` on form/button clicks | Use `event.preventDefault()` to stop default browser actions when needed |

## Quick Guide

```js
// 🔗 Add Listener
el.addEventListener("click", myFunction);

// 🗑️ Remove Listener
el.removeEventListener("click", myFunction);

// 🌊 Control Propagation
el.addEventListener("click", myFunction, false); // Bubbling (default)
el.addEventListener("click", myFunction, true);  // Capturing

// 📦 Anonymous function with parameters
el.addEventListener("click", function() { myCustomFunc(a, b); });

// 🛑 Stop default behavior (e.g., form submission, link navigation)
el.addEventListener("submit", function(e) { e.preventDefault(); });
```

<Callout type="tip" title="Suggestion">
    <!-- Space here -->
    See Examples in Lab manual. It covers all the main methods mentioned above.
    <!-- Space here -->
</Callout>


<Callout type="warning" title="Alert">
    <!-- Space here -->
    If you see a alert message on screen after a scroll to question 2 please ignore that. It's part of it.
    <!-- Space here -->
</Callout>

## Question 1

### Problem Statement

Design an HTML page as shown in figure(refer to lab manual). Implement the event "on button click display data" using HTML DOM events.

Before click on submit button: <br />
Figure 1: _Text with button but no time text_

After click on submit button: <br />
Figure 2: _Show Date & Time below submit button_

### Preview (Working)

<Question1 />

### Code

```html title="date.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-5/1.html

```

## Question 2

### Problem Statement

Design an HTML page to shown that, when this page is loaded it must check the cookies status of the user's browser and dispay a message accordingly in the popup box i.e if cookies are enabled show: "Cookies are enabled" and if not then show: "Cookies are disabled". Implement the event "on load" using HTML DOM events

### Preview (Working)

<Question2 />

### Code

```html title="color-change.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-5/2.html

```

## Question 3

### Problem Statement

Whenever user input a text in the text box in any case (i.e. upper or lower case), automatically it should be converted to uppercase. Design an HTML page to implement above functionality using HTML DOM event "onchange".

### Preview (Working)

<Question3 />

### Code

```html title="onchange.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-5/3.html

```

## Question 4

### Problem Statement

Design HTML page to implement HTML DOM events by changing an image on the following events: onmouseover, onmouseout, onmousedown, and onmouseup Events.

### Preview (Working)

<Question4 />

### Code

```html title="image-mouse-event.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-5/4.html

```
