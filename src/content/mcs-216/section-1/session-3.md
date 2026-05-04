---
title: Session 3
description: Task Scheduling Algorithms
section: MCS-216 Section 1
---

A task scheduling problem is formulated as an optimization problem which in which we need to determine the set of tasks from the given tasks that can ve accomplished withintheir deadlines along with their order of scheduling such that the profilt is maximum. So, this is a maximixation optimization problem with a constraint that tasks must be completed within their deadlines.

## Objective 

The main objectives of this session are to:
- Implement a task scheduling algorithm
- Test the algorithm on different problems instances
- Differentiate between various task scheduling approaches based on their performance and efficiency
  - Brute Force Approach
  - Efficient task scheduling algorithm

## Question 1

### Problem Statement

Apply a brute force approach to schedule three jobs J1, J2 and J3 with service times as 5,8,12 respectively. The actual service time units are not relevant to the problems. Make all possible job schedules , calculate the total times spent in jobs by the system. Find the optimal schedule (total time). If there are N jobs , what would be the total number of job schedules?

### Mathematical Logic

For a sequence of jobs `(J_a, J_b, J_c)` with service times `(t_a, t_b, t_c)`:
- `J_a` finishes at `t_a`
- `J_b` finishes at `t_a + t_b`
- `J_c` finishes at `t_a + t_b + t_c`

The total time spent in jobs by the system is the sum of the finishing times of all jobs, which can be calculated as:
```Total Time = (t_a) + (t_a + t_b) + (t_a + t_b + t_c) = 3*t_a + 2*t_b + t_c```

### Implementation

### Python
```python title="horners-method.py" showLineNumbers file=../../../lib/code/mcs-216/session-3/1/1.py 

```

### C Language
```c title="horners-method.c" showLineNumbers file=../../../lib/code/mcs-216/session-3/1/1.c 

```

### Rust
```rust title="horners-method.rs" showLineNumbers file=../../../lib/code/mcs-216/session-3/1/1.rs

```

## Question 2

### Problem Statement

Implement the task scheduling algorithm on your system to minimize the total amount of time spent in the system for the following problem:

| Job | Service Time |
| --- | --- |
| 1 | 5 |
| 2 | 10 |
| 3 | 7 |
|4 | 8 |

### Mathematical Logic

To minimize the total amount of time spent in the system, we can use the Shortest Job First (SJF) scheduling algorithm. This algorithm schedules jobs in order of their service times, starting with the shortest job first.
The total time spent in the system can be calculated as follows:
- Schedule the jobs in ascending order of their service times: J1 (5), J3 (7), J4 (8), J2 (10)
- Calculate the finishing times for each job:
  - J1 finishes at 5
  - J3 finishes at 5 + 7 = 12
  - J4 finishes at 12 + 8 = 20
  - J2 finishes at 20 + 10 = 30
- The total time spent in the system is the sum of the finishing times: 5 + 12 + 20 + 30 = 67

### Implementation

### Python
```python title="horners-method.py" showLineNumbers file=../../../lib/code/mcs-216/session-3/2/2.py 

``` 

### C Language
```c title="horners-method.c" showLineNumbers file=../../../lib/code/mcs-216/session-3/2/2.c 

```

### Rust
```rust title="horners-method.rs" showLineNumbers file=../../../lib/code/mcs-216/session-3/2/2.rs

```

## Question 3

### Problem Statement

Consider the following jobs, deadlines and profits. Implement the task scheduling algorithm with deadlines to maximize the total profits.

| Job | Deadline | Profits |
| --- | --- | --- |
| 1 | 3 | 50 |
| 2 | 4 | 20 |
| 3 | 5 | 70 |
| 4 | 3 | 15 |
| 5 | 2 | 10 |
| 6 | 1 | 47 |
| 7 | 1 | 60 |

### Mathematical Logic
To maximize the total profits while scheduling jobs with deadlines, we can use a greedy approach. We will sort the jobs based on their profits in descending order and then schedule them as late as possible before their deadlines.
1. Sort the jobs based on profits: J3 (70), J7 (60), J1 (50), J6 (47), J2 (20), J4 (15), J5 (10)
2. Schedule the jobs:
- J3 is scheduled at time 5 (profit 70)
- J7 is scheduled at time 4 (profit 60)
- J1 is scheduled at time 3 (profit 50)
- J6 is scheduled at time 2 (profit 47)
- J2 is scheduled at time 1 (profit 20)
- J4 and J5 cannot be scheduled as their deadlines have passed.
3. The total profit is the sum of the profits of the scheduled jobs: 70 + 60 + 50 + 47 + 20 = 247
4. The optimal schedule is: J2 (1), J6 (2), J1 (3), J7 (4), J3 (5) with a total profit of 247.

### Implementation

### Python
```python title="horners-method.py" showLineNumbers file=../../../lib/code/mcs-216/session-3/3/3.py 

```

### C Language
```c title="horners-method.c" showLineNumbers file=../../../lib/code/mcs-216/session-3/3/3.c 

```

### Rust
```rust title="horners-method.rs" showLineNumbers file=../../../lib/code/mcs-216/session-3/3/3.rs

```

## Conclusion
In this session, we have explored various task scheduling algorithms and their implementations. We have seen how to apply a brute force approach to schedule jobs and calculate the total time spent in the system. We also implemented the Shortest Job First (SJF) algorithm to minimize the total time spent in the system and a greedy approach to maximize profits while scheduling jobs with deadlines. These algorithms are fundamental in understanding how to efficiently manage tasks in various applications, such as operating systems, project management, and manufacturing processes.
