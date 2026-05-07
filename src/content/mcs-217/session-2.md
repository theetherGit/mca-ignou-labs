---
title: Session 2
description: Effort and Cost Estimation
section: MCS-217
---

<script>
  import PrintButton from "$lib/components/print-button.svelte"
</script>

<PrintButton />

## Problem Statement

Estimate the effort and cost required to build the above software ([session-1](https://syntax.theether.in/docs/mcs-217/section-1)). Use any estimation technique.

## Estimation of RRS

The different parameters for estimation of Railway Reservation project that need to be estimated includes:

- Project Size (in Lines of Code or Functional Points)
- Effort required to complete the project (in Person-months or Person-hours)
- Schedule (in calendar months)
- Cost (in dollars or local currency)

For this project we are assuming that this project requires **75KBLOC**.
On the basis of this size of the project we have to estimate the remaining estimations.

We will use the following method to estimate the effort and cost of the project.

### The Intermediate COCOMO Model

The intermediate model estimates software development effort in terms of size of the program and other related cost drivers parameters (product parameter, hardware parameter, resource parameter, and project parameter) of the project. The estimated effort and scheduled time are given by the relationship:

Effort (E) = a*(KLOC)b *EAF  MM

Scheduled Time (D) = c*(E)d  Months(M)

- E = Total effort required for the project in Man-Months (MM).
- D = Total time required for project development in Months (M).
- KLOC = The size of the code for the project in Kilo lines of code.
- a, b, c, d = The constant parameters for the software project.

The values of these constants for different categories are:

| Project | a | b | c | d |
|---------|---|---|---|---|
| Organic | 2.4 | 1.05 | 2.5 | 0.38 |
| Semidetached | 3.0 | 1.12 | 2.5 | 0.35 |
| Embedded | 3.6 | 1.20 | 2.5 | 0.32 |

> Developer having highly application experience: 0.82 (as per above table)
Developer having very low experience in programming: 1.14(as per above table)
Effort (E) = a*(KLOC)b *EAF = 3.0*(300)1.12 *0.9348 = 1668.07 MM
Scheduled Time (D) = c*(E)d  = 2.5*(1668.07)0.35 = 33.55 Months(M)

> EAF = It is an Effort Adjustment Factor, which is calculated by multiplying the parameter values of different cost driver parameters. For ideal, the value is 1.

> Example: For a given project was estimated with a size of 300 KLOC. Calculate the Effort, Scheduled time for development by considering developer having high application experience and very low experience in programming.

Developer having very low experience in programming: 1.14(as per above table)

Effort (E) = a*(KLOC)b *EAF = 3.0*(300)1.12 *0.9348 = 1668.07 MM
Scheduled Time (D) = c*(E)d  = 2.5*(1668.07)0.35 = 33.55 Months(M)

Given the estimated size of the project is: 300 KLOC

Developer having highly application experience: 0.82 (as per above table)

EAF = 0.82*1.14 = 0.9348

#### We are assuming that railway reservation project requires 75 KBLOC. On the basis of this size of the project we have to estimate the remaining estimations. We have the formula to estimate the schedule of the project.

Schedule in months = 3.0 * (effort-months)^(1/3)

Opinions vary as to whether 2.0 or 2.5 or even 4.0 should be used in place of the 3.0 value - only by trying it out will you see what works for you.

Of course, you must also keep in mind other important factors that affect the accuracy of your 
estimates, such as:

- The accuracy of all the estimate's input data (the old adage, "Garbage in, Garbage out", holds true)
- The accuracy of any estimate calculations (e.g., converting between Function Points and LOC has a certain margin of error)
- How closely the historical data or industry data used to calibrate the model matches the project you are estimating
- The predictability of your organization's software development process, and whether or not the actual project was carefully planned; monitored and controlled, and no major surprises occurred that caused unexpected delays

When they analyze the results, most people are startled by the consequences of different tradeoffs.  For example, the following tables provide 3 different estimate options for a 75 KBLOC project are:

#### Nominal Plan

| Management Metric | Planning Value | 
|-------------------|----------------|
| Effort (Staff months) | 40 | 
| Schedule (Calendar months) | 12.4 | 
| Cost | $605,868 | 
| Peak staff (People) | 4.8 |
| Average staff (people) | 3.2 |

#### Shortest Schedule – Plan

| Management Metric | Planning Value | 
|-------------------|----------------|
| Effort (Staff months) | 97 | 
| Schedule (Calendar months) | 10 | 
| Cost | $1,479,170 | 
| Peak staff (People) | 14.6 |
| Average staff (people) | 9.8 |

#### Least Cost – Plan

| Management Metric | Planning Value | 
|-------------------|----------------|
| Effort (Staff months) | 14 | 
| Schedule (Calendar months) | 16.2 | 
| Cost | $212,131 | 
| Peak staff (People) | 1.3 |
| Average staff (people) | 0.9 |
