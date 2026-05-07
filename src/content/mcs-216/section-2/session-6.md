---
title: Session 6
description: HTML DOM Navigation
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  
  import Question4 from "$lib/components/demo/mcs-216/section-2/session-6/4.svelte"
</script>

<PrintButton />

HTML DOM interprets an HTML document as a hierarchical tree of nodes. This session focuses on DOM Navigation, which allows JavaScript to traverse this tree using parent-child-sibling relationships. Additionally, this session covers dynamic DOM Manipulation: creating, inserting, and removing HTML elements programmatically without page reloads.

## Objectives

- Navigate between DOM nodes using built-in relationship properties
- Dynamically create and attach new HTML elements to the document
- Remove existing elements or child nodes from the DOM tree
- Implement interactive UI updates through hands-on DOM exercises

## DOM Navigation Properties

Every DOM node exposes properties to access its relatives in the tree:

| Property | Description | Example |
|----------|-------------|---------|
| `parentNode` | Returns the direct parent node | `el.parentNode` |
| `childNodes` | Returns a `NodeList` of all direct children | `el.childNodes[0]` |
| `firstChild` / `lastChild` | Returns the first/last child node | `el.firstChild` |
| `nextSibling` / `previousSibling` | Returns adjacent sibling nodes | `el.nextSibling` |

### Important Notes:
- `childNodes` includes **text nodes** (whitespace counts as a node). To skip them, use `children` or check `nodeType === 1`.
- `nodeValue` extracts the text content of a text node.
- `nodeName` returns the tag name in **UPPERCASE** (e.g., `DIV`, `P`).

```js
// Example: Accessing text inside <h3 id="heading1">Hello</h3>
let h3 = document.getElementById("heading1");
console.log(h3.firstChild.nodeValue); // "Hello"
console.log(h3.nodeName);             // "H3"
```

## Creating & Adding Elements

- **Create Element**: `document.createElement("tag")`
- **Create Text Node**: `document.createTextNode("text")`
- **Attach Text to Element**: `element.appendChild(textNode)`
- **Insert into DOM**:
  - `parent.appendChild(newEl)` -> Adds as **last child**
  - `parent.insertBefore(newEl, referenceEl)` -> Inserts **before** a specific child

## Removing Elements

| Method | Usage | Behavior |
|--------|-------|----------|
| `element.remove()` | Modern, direct | Removes the element itself |
| `parent.removeChild(child)` |  Legacy | Removes a specific child from its parent |

## Question 1

### Problem Statement

Which function on the document object should be used to retrieve a HTML element uniquely?

### Answer

```js
document.getElementById(id)
```

> Note: `document.querySelector("#id")` also works, but `getElementById` is faster and specifically designed for unique ID retrieval.

## Question 2

### Problem Statement

Which JavaScript function can be used to dynamically add a event listener to a HTML element?

### Answer

```js
element.addEventListener(eventType, callbackFunction)
```
OR 
```js
parentElement.insertBefore(newElement, referenceElement)
```

## Question 3

### Problem Statement

Which method should be used to add a new HTML child element?

### Answer

```js
parentElement.appendChild(newElement)
```
OR
```js
parentElement.insertBefore(newElement, referenceElement)
```


## Question 4

### Problem Statement

USe the DOM API, create a product page which shows the prices of a laptop and a cell phone. You may use paragraph tag to wrap these elements. When the user clicks on add button, you should able to add TV with price details and when you click on delete button then cell phone details will be deleted.

### Preview (Working)

<Question4 />

### Code

```html title="product-page.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-6/4.html

```
