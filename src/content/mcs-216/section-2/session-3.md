---
title: Session 3
description: Cascading Styling Sheet (CSS)
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte"
  import Question1HomePage from "$lib/components/demo/mcs-216/section-2/session-3/1-timetable/index.svelte"
  import Question2 from "$lib/components/demo/mcs-216/section-2/session-3/2-personal/personal-info.svelte"
</script>

<PrintButton />

CSS (Cascading Style Sheets) is a core web technology designed to separate the visual presentation and layout of a webpage from its structural HTML content. In web development, maintaining a consistent look and feel across multiple pages is essential for user familiarity and professional design. CSS streamlines this process, especially in collaborative environments where teams of developers need to apply uniform styling across large projects without duplicating design code.

This session introduces how CSS enables developers to efficiently style and layout web pages. Key capabilities covered include controlling:

- Typography & text formatting (fonts, colors, sizes, spacing)
- Page layout & structure (multi-column arrangements, positioning)
- Visual enhancements & animations (decorative features, transitions)

## Objective

After Completing this session, one should be able to:
- Create CSS for a webpage
- Embed CSS inline and external into an HTML code.

## Methods to implement CSS in HTML

There are three methods to implement CSS in HTML: Inline, Internal and External CSS.

### Internal CSS

- **What it is**: CSS rules defined directly within a single HTML document.
- **Where it goes**: Placed inside the `<head>` tag section using `<style>` tags.
- **Scope**: Applies globally to all elements within that specific HTML page only.
- **Example**:
  ```html
  <head>
    <style>
      body { background-color: green; }
      h1 { margin-left: 20px; color: red; }
    </style>
  </head>
  ```
- Best for: Styling a single page when you don't want to create a separate file.

### Inline CSS

- **What it is**: CSS applied directly to a specific HTML element.
- **Where it goes**: Added as a `style` attribute directly inside the opening tag of the element.
- **Scope**: Element-specific. It only affects the exact tag it's attached to.
- **Example**:
  ```html
  <h2 style="text-align: right; color: red;">This is a heading</h2>
  <p style="text-align: justify; color: green;">This is a paragraph.</p>
  ```

- **Best for**: Quick, one-off styling. However, it's not recommended for large projects as it mixes content with presentation and reduces maintainability.

###  External CSS

- **What it is**: CSS written in a completely separate file with a .css extension.
- **Where it goes**: Linked to the HTML document using the `link>` tag inside the `<head>` section.
- **Scope**: Can be attached to multiple HTML pages, ensuring a consistent look across an entire website.
- **Example**:
  ```html title="file.html"
  <head>
    <link rel="stylesheet" href="external-css.css">
  </head>
  ```

  ```css title="external-css.css"
  body { background-color: lightblue; }
  h2 { color: navy; margin-left: 20px; }
  ```

### Cascading Priority

When multiple styles are applied to the same element, the browser follows a cascading priority rule to determine which style wins. From highest to lowest priority:

- Inline style (Highest priority → overrides everything)
- External & Internal style sheets (Equal priority; whichever loads last usually wins)
- Browser default styles (Lowest priority)

> Example: If an external stylesheet sets `h2 { color: blue; }` but you add `style="color: red;"` directly to that `<h2>` tag, the text will render red because inline styles take precedence.

## Question 1

### Problem Statement

Create an HTML website to display the time table of all the 4 years of B. Tech. (even semester of each year).It should contain a home page where link to each year's time table is listed. On click to any year time table a new web page should be open displaying the corresponding time table. Apply the following effects on the table using CSS:

- Common to all:
  - Display day names (Mon, Tue etc...) in bold format with the first
  letter in the dayname in uppercase.
  - Display lunch slightly in bigger font other than the remaining text.
- Specific to each year:
  - For 1st year
    - Apply blue as the background colour and white for the colour of
    the text in the table header.
  - For 2nd year
    - Apply green as the background colour and white for the colour of
    the text in the table header.
  - For 3rd year
    - Apply purple as the background colour and white for the colour
    of the text in the table header.
  - For 4th year
    - Apply yellow as the background colour and black for the colour
    of the text in the table header.

### Solution

### File Structure

```sh
📂 B.Tech_Timetable/
 ├── index.html          (Home Page)
 ├── year1.html          (1st Year Timetable)
 ├── year2.html          (2nd Year Timetable)
 ├── year3.html          (3rd Year Timetable)
 ├── year4.html          (4th Year Timetable)
 └── style.css           (External CSS File)
```

### Code Files

### Homepage

```html title="index.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/index.html

```

### Ist Year

```html title="year1.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/year1.html

```

### IInd Year

```html title="year2.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/year2.html

```

### IIIrd Year

```html title="year3.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/year3.html

```

### IVth Year

```html title="year4.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/year4.html

```

### Common Style Sheet

```css title="year4.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/B.Tech_Timetable/style.css

```


### Preview (Working)

<Question1HomePage />


## Question 2


### Problem Statement

Create an HTML webpage to show personal information i.e. name, class, qualifications, photo,address etc. Make use of tables as when possible. Apply the following styleinformation using CSS:

- Display the heading of the page in Arial font and with font size of 18px.
- Align all the field names like Name, Class, Photo etc to left in the table.
- Apply yellow color as background colour in left side cells contains field names like Name, Class etc...
- Set college logo as background image to the web page.

### File Structure

```sh
📂 PersonalInfo/
 ├── index.html
 ├── style.css
 ├── college-logo.png   (Replace with your actual logo file)
 └── student-photo.jpg  (Replace with your actual photo file)
```

### Code Files

### Homepage

```html title="index.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/personal-info/index.html

```

### Style Sheet

```css title="style.css" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-3/personal-info/style.css

```

### Preview (Working)

<Question2 />
