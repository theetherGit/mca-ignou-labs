fn calculate_total_time(sequence: &Vec<(&str, i32)>) -> i32 {
    let mut current_time = 0;
    let mut total_time = 0;
    for &(_, time) in sequence {
        current_time += time; // Finish time of current job
        total_time += current_time; // Cumulative sum
    }
    total_time
}

fn permute(jobs: &mut Vec<(&str, i32)>, start: usize, best: &mut (i32, Vec<String>)) {
    if start == jobs.len() {
        let time = calculate_total_time(jobs);
        if time < best.0 {
            best.0 = time;
            best.1 = jobs.iter().map(|(id, _)| id.to_string()).collect();
        }
        return;
    }
    for i in start..jobs.len() {
        jobs.swap(start, i); // Swap to create new permutation
        permute(jobs, start + 1, best);
        jobs.swap(start, i); // Backtrack
    }
}

fn main() {
    let mut jobs = vec![("J1", 5), ("J2", 8), ("J3", 12)];
    let mut best = (i32::MAX, vec![]);
    permute(&mut jobs, 0, &mut best);
    println!("Optimal Schedule: {:?} Total Time: {}", best.1, best.0);
}
