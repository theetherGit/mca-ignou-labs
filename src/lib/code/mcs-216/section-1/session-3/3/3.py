def solve_job_sequencing(jobs):
    # 1. Sort jobs by profit in descending order
    # (Job ID, Deadline, Profit)
    jobs.sort(key=lambda x: x[2], reverse=True)

    # 2. Find max deadline to size the timeline
    max_d = max(job[1] for job in jobs)

    # 3. Initialize slots (0 is ignored, using 1 to max_d)
    slots = [-1] * (max_d + 1)
    total_profit = 0
    count_jobs = 0

    for job_id, deadline, profit in jobs:
        # 4. Try to place job in the latest available slot from deadline down to 1
        for j in range(deadline, 0, -1):
            if slots[j] == -1:
                slots[j] = job_id
                total_profit += profit
                count_jobs += 1
                break

    # Filter out empty slots for the result
    scheduled_jobs = [slots[i] for i in range(1, max_d + 1) if slots[i] != -1]
    return scheduled_jobs, total_profit


# Data: (ID, Deadline, Profit)
job_data = [
    (1, 3, 50),
    (2, 4, 20),
    (3, 5, 70),
    (4, 3, 15),
    (5, 2, 10),
    (6, 1, 47),
    (7, 1, 60),
]
sequence, profit = solve_job_sequencing(job_data)

print(f"Scheduled Sequence: {sequence}")
print(f"Maximum Profit: {profit}")
