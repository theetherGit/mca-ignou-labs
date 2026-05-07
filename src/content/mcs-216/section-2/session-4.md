---
title: Session 4
description: JavaScript HTML DOM
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-4/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-4/2.svelte"
  import Question3 from "$lib/components/demo/mcs-216/section-2/session-4/3.svelte"
</script>

<PrintButton />

The **Document Object Model (DOM)** is a W3C-standard, language-independent interface that allows programs and scripts to dynamically access, modify, add, or remove the content, structure, and style of a web document. While the W3C DOM is categorized into Core DOM (all document types), XML DOM, and **HTML DOM**, this session focuses specifically on the HTML DOM, which is the standard model for HTML documents.

When a browser loads an HTML page, it automatically parses the markup and constructs a hierarchical **DOM tree**. This tree represents the document's structure through parent-child node relationships, where:

- The entire document is a `document` node
- Every HTML tag is an `element` node
- Text inside elements is a `text` node
- HTML comments are `comment` nodes

The HTML DOM bridges static HTML with dynamic JavaScript by treating every element, attribute, and piece of content as a **JavaScript object**. This object-oriented representation enables developers to:

- ✅ Access or locate any element using IDs, tag names, or class names
- ✅ Modify element content (innerHTML), attributes, and CSS styles on-the-fly
- ✅ Dynamically create, append, or remove HTML elements
- ✅ React to user interactions through DOM events (clicks, inputs, loads, etc.)

By leveraging the HTML DOM, you can transform static web pages into highly interactive, real-time applications without requiring page reloads. This session introduces the core DOM programming interface, node navigation techniques, and practical methods for manipulating HTML content and styles using JavaScript.

## Objective

After completing this session one should be able to:
- Add, Modify or delete the existing content of HTML elements.
- Modify a CSS style in the HTML page.
- React to existing HTML DOM events in page.

##  DOM Tree (Node Types)
When a browser parses HTML, it builds a node tree:

| Node Type | Description | Example |
|-----------|-------------|---------|
| `document` | Root node of the entire page | `document` |
| `element` | HTML tags | `<div>`, `<p>`, `<img>` |
| `text` | Content inside elements | `"Hello World"` inside `<p>` |
| `attribute` | Element attributes (treated as nodes in legacy DOM) | `id="btn"`, `src="img.jpg"` |
| `comment` | HTML comments | `<!-- hidden -->` |

### Parent-Child-Sibling Relationships

- `<html>` → parent of `<head>` & `<body>`
- `<body>` → parent of `<h1>` & `<p>`
- `<h1>` & `<p>` → siblings

## Accessing Elements (DOM Methods)

| Method | Returns | Best For |
|--------|---------|----------|
| `document.getElementById("id")` | Single element | Fastest & most reliable |
| `document.getElementsByClassName("class")` | HTMLCollection (Live) | Multiple elements sharing a class |
| `document.getElementsByTagName("tag")` | HTMLCollection (Live) | All elements of a specific tag |
| `document.querySelector("selector")` | First matching element | Modern, CSS-like selectors |
| `document.querySelectorAll("selector")` | NodeList (static) | All matching elements |

## Modifying Element

### Content 

```js
element.innerHTML = "<b>New HTML</b>";   // Parses HTML (risk of XSS if user input)
element.textContent = "Plain text only";  // Safer, faster, ignores HTML tags
element.innerText = "Visible text only";  // Respects CSS styling (e.g., hidden elements)
```

### Attributes

```js
// Direct property (works for standard attributes)
img.src = "new.jpg";
link.href = "https://example.com";

// Universal method (works for custom/data attributes)
element.setAttribute("data-role", "admin");
let val = element.getAttribute("data-role");
```

### Styles

```js
// JS uses camelCase for multi-word CSS properties
element.style.backgroundColor = "lightblue";
element.style.fontSize = "18px";
element.style.marginLeft = "20px";
```

## Create & Append Element

```js
let newP = document.createElement("p");          // <p></p>
let txt = document.createTextNode("Hello DOM");  // "Hello DOM"
newP.appendChild(txt);                           // <p>Hello DOM</p>
document.body.appendChild(newP);                 // Adds to end of <body>
```

## Insert at Specific Position

```js
let parent = document.getElementById("container");
let reference = document.getElementById("refItem");
parent.insertBefore(newP, reference); // Inserts newP before reference
```

## Remove Elements

```js
// Modern (recommended)
element.remove(); 

// Legacy (manual's syntax)
parent.removeChild(childElement);
```

<Callout type="tip" title="Suggestion">
    <!-- Space here -->
    See Example 1 in Lab manual. It covers all the main methods mentioned above.
    <!-- Space here -->
</Callout>


## Question 1

### Problem Statement

Design an HTML page using JavaScript as shown below. When Try button is pressed, the Full Name should be shown below the Try button.<br />
(Hint: Use concatenation to get Full Name). <br />
(Please refer to images in lab manual)

### Preview (Working)

<Question1 />

### Code

```html title="button-on-click.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-4/1.html

```

## Question 2

### Problem Statement

Modify the below snippet of the code to change the src attribute of the image element to "pqr.jpg" using  HTML DOM.

```html 
<img id="pic" src="old.jpg">
<script>
//Write your code here.
</script>
```

### Preview (Working)

<Question2 />

### Code

```html title="image-change.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-4/2.html

```

## Question 3

### Problem Statement

Write the JavaScript code to change the color of the HTML element h2 to green, on click the change color button.


### Preview (Working)

<Question3 />

### Code

```html title="color-change.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-4/3.html

```
