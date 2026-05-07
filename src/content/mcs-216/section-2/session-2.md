---
title: Session 2
description: HTML Forms
section: MCS-216 Section 2
---

<script>
  import { Callout } from "@ethercorps/kit";
  import PrintButton from "$lib/components/print-button.svelte"
  import InfoIcon from "phosphor-svelte/lib/InfoIcon"

  import Question1Preview from "$lib/components/demo/mcs-216/section-2/session-2-1.svelte"
  import Question2Preview from "$lib/components/demo/mcs-216/section-2/session-2-2.svelte"
  import Question3Preview from "$lib/components/demo/mcs-216/section-2/session-2-3.svelte"
</script>

<PrintButton />

HTML Forms are a fundamental building block of interactive web development, designed to collect user input dynamically at runtime. In this session, you will gain a foundational understanding of how to create, structure, and implement HTML forms to gather information from users. The data entered through these forms is typically transmitted to a web server for processing, validation, and storage.

Forms are widely used to collect essential information such as usernames, passwords, contact details (e-mail IDs, mobile numbers), and other user preferences. This session introduces the core `<form>` container element and explores the various input controls it can hold, including:
- Text fields & text areas
- Radio buttons & checkboxes
- Submit & clickable buttons
- Labels for accessibility and clarity
- HTML5-specific input types (e.g., email, search, url, date, month, time)

<Callout type="tip" icon={InfoIcon} title="Suggestion">
    <!-- Space here -->
    Before trying the solutions provided for the exercises, try to solve them on your own. This will help you understand the concepts better and improve your problem-solving skills.<br/> <br />
    Also, Lab manual includes great examples before exercises, make sure to go through them as well.
    <!-- Space here -->
</Callout>

## Objective

After Completing this session, one should be able to:
- Understand the HTML form element
- use the form element in HTML
- use HTML to acquire user input and process it
- Create forms with basic elements like textboxes, checkboxes, radio buttons and submit buttons.
- Create forms using HTML5 elements like E-Mail address field and form validation

## Question 1

### Problem Statement

Create an HTML webpage, as shown in the figure [2.1]. The user can specify any expression as input. Use form element to collect the user data.

##### Figure 2.1 (Demo)
- Reference by question
- Working demo for preview

<Question1Preview />

### Code

```html title="form.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-2/1.html

```

## Question 2

### Problem Statement

Create a scrolling list that shows five items from the following list of PC processors: Intel i7, Motorola 68000, AMD Athlon , Intel 8088, AMD Ryzon, Intel Pentium MMX, Intel i3, Intel Pentium II, Intel Pentium III, Intel i5, Intel Celeron, PowerPC G3, PowerPC G4.

### Preview

<Question2Preview />

### Code

```html title="list-scroller.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-2/2.html

```

## Question 3

### Problem Statement

Design a webpage for a software company to accept on-line job applications. The
webpage must be designed to use form with elements:

- Position applied for (autofocus), name, nationality, date of birth (selected from an
auto picker), address (in a text area), telephone number and email (required).
- Educational history and qualifications.
- Work experience/employment/training in terms of employer history and number of years of experience selected from a slider. Set maximum years of experience to 10 years.
- Personal statement.
- Two referees including names, occupation, relationship, address, telephone.

### Preview

<Question3Preview />

### Code

```html title="job-portal.html" showLineNumbers file=../../../lib/code/mcs-216/section-2/session-2/3.html

```
