def minimize_total_time(jobs):
    # Sort jobs by service time (index 1 of the tuple)
    jobs.sort(key=lambda x: x[1])

    current_time = 0
    total_spent = 0
    sequence = []

    for job_id, service_time in jobs:
        current_time += service_time  # Time when this specific job finishes
        total_spent += current_time  # Add this finish time to the system total
        sequence.append(str(job_id))

    print(f"Optimal Sequence: {' -> '.join(sequence)}")
    print(f"Total Time Spent in System: {total_spent}")


# Input: (Job ID, Service Time)
job_list = [(1, 5), (2, 10), (3, 7), (4, 8)]
minimize_total_time(job_list)
