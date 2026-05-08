---
title: Session 10
description: Javascript Cookies
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte";
  
  import Question1 from "$lib/components/demo/mcs-216/section-2/session-10/1.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-10/2.svelte"
  import Question3 from "$lib/components/demo/mcs-216/section-2/session-10/3.svelte"
  import Question4 from "$lib/components/demo/mcs-216/section-2/session-10/4.svelte"
</script>

<PrintButton />

Cookies are small text files stored on the user's client-side computer that allow web applications to "remember" information across page reloads or future visits. While modern web development often uses `localStorage` or `sessionStorage` for client-side persistence, cookies remain essential for session tracking, authentication tokens, and server-side state management because they are automatically sent with every HTTP request to the matching domain. Session 10 covers the complete lifecycle of cookies using the native `document.cookie` API, teaching you how to create, read, parse, modify, and delete them programmatically.

## Objectives
- Understand how cookies work and their role in web state management
- Create, read, update, and delete cookies using document.cookie
- Parse the raw cookie string to extract specific name=value pairs
- Implement practical exercises for user preference storage and session tracking

## What is a JavaScript Cookie?

- A cookie is a small piece of data stored as a name=value pair in the browser.
- Stored as plain text files on the client machine.
- Automatically included in Cookie HTTP headers for subsequent requests to the same domain/path.

## Cookie Structure & Attributes

```js
document.cookie = "username=JohnDoe; expires=Fri, 31 Dec 2026 23:59:59 GMT; path=/; domain=example.com; secure; samesite=strict";
```

| Attribute | Purpose |
|-----------|---------|
| `expires` / `max-age` |  Defines lifespan. If omitted, cookie is a session cookie (deleted when browser closes) |
| `path` | Scope of the cookie. `path=/` makes it available site-wide |
| `domain` | Host scope. Default is current domain |
| `secure` | Only sent over HTTPS |
| `samesite` |  CSRF protection (`Strict`, `Lax`, `None`) |

## The `document.cookie` API

| Operation | Syntax | Behavior |
|-----------|--------|----------|
|Create/Update | `document.cookie = "name=value; path=/"` | Appends or overwrites existing cookie with  same name |
| Read All | `let all = document.cookie` | Returns a single string: `"id=1; theme=dark; user=John"` |
| Delete | `document.cookie = "name=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/";` | Forces expiration to a past date |

> Important: `document.cookie` does not return an object or array. You must manually parse the string to extract specific values.

#### Parsing the Cookie String

```js
function getCookie(name) {
  const nameEQ = name + "=";
  const cookies = document.cookie.split(';');
  for(let i = 0; i < cookies.length; i++) {
    let c = cookies[i].trim();
    if (c.indexOf(nameEQ) === 0) return c.substring(nameEQ.length);
  }
  return null; // Not found
}
```

## Best Practices & Limitations

| Limitation | Workaround / Best Practice |
|------------|----------------------------|
| Size limit (~4KB per cookie) | Store only essential identifiers; use localStorage for bulk data |
| Sent with every request | Minimize cookie count & size for performance 
| Accessible via JS `(document.cookie)` | Never store passwords/sensitive data; use `HttpOnly` (server-set only) for security-critical cookies |
| Parsing overhead | Use helper functions or modern cookie libraries in production |

## Quick Guide

```js
// ✅ Set Cookie
function setCookie(name, value, days) {
  const d = new Date(); d.setTime(d.getTime() + (days * 24 * 60 * 60 * 1000));
  document.cookie = `${name}=${value};expires=${d.toUTCString()};path=/`;
}

// 🔍 Get Cookie
function getCookie(name) {
  const match = document.cookie.match(new RegExp('(^| )' + name + '=([^;]+)'));
  return match ? decodeURIComponent(match[2]) : null;
}

// 🗑️ Delete Cookie
function deleteCookie(name) {
  document.cookie = `${name}=;expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/;`;
}
```

## Question 1

### Problem Statement

Create an HTML web page, as shown below. The cookie will be set on pressing setCookie button and the stored cookie value will be displayed on pressing getCookie button.

> Note: Check lab manual for images

### Demo

<Question1 />

### Code

```html title="time.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-10/1.html

```


#### HTML View

<iframe
  id="preview-1"
  title="demo-q-1"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  loading="lazy"
  src="/preview/mcs-216/section-2/session-10/1.html">
</iframe>

## Question 2

### Problem Statement

Considering exercise 1, modify the web page to display the cookie's name-value pair separately as shown in figure below.

> Note: Check lab manual for images/figures

### Demo

<Question2 />

### Code

```html title="time.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-10/2.html

```


#### HTML View

<iframe
  id="preview-2"
  title="demo-q-2"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  loading="lazy"
  src="/preview/mcs-216/section-2/session-10/2.html">
</iframe>

## Question 3

### Problem Statement

A list of color is provided in the form of drop down list. The background color of the web page changes as per the selection of the color from the list by the user. At the same time the chosencoloris passed to the cookie. The cookie stores the last choice of a user in a browser which will be used on reloading the web page to display the same color as background color.

> Note: Check lab manual for images/figures

### Demo

<Question3 />

### Code

```html title="time.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-10/3.html

```


#### HTML View

<iframe
  id="preview-3"
  title="demo-q-3"
  width="100%"
  height="300px"
  class="mt-5 rounded-xl"
  loading="lazy"
  src="/preview/mcs-216/section-2/session-10/3.html">
</iframe>

## Question 4

### Problem Statement

Create an HTML web page, as shown below. The cookie1 and cookie2 will be set on pressing Set Cookie1or Set Cookie2 button and the stored cookie value will be displayed on pressing Get Cookie1 or Get Cookie2 button respectively. On the other hand selectively cookie can be deleted by pressing Delete Cookie1 or Delete Cookie2 button. Display all cookies button will show all the stored cookies.

> Note: Check lab manual for images/figures

### Demo

<Question4 />

### Code

```html title="time.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-10/4.html

```

#### HTML View

<iframe
  id="preview-4"
  title="demo-q-4"
  width="100%"
  height="400px"
  class="mt-5 rounded-xl"
  loading="lazy"
  src="/preview/mcs-216/section-2/session-10/4.html">
</iframe>
