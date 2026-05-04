from itertools import permutations


def solve_brute_force(jobs):
    # jobs is a list of tuples: (name, time)
    all_configs = list(permutations(jobs))
    best_time = float("inf")
    best_seq = None

    for config in all_configs:
        current_finish_time = 0
        total_system_time = 0

        # Calculate completion time for each job in this specific order
        for name, time in config:
            current_finish_time += time
            total_system_time += current_finish_time

        print(
            f"Schedule {'-'.join([j[0] for j in config])}: Total Time = {total_system_time}"
        )

        # Track the minimum time found
        if total_system_time < best_time:
            best_time = total_system_time
            best_seq = config

    print(f"\nOptimal: {'-'.join([j[0] for j in best_seq])} with Time: {best_time}")


job_list = [("J1", 5), ("J2", 8), ("J3", 12)]
solve_brute_force(job_list)
