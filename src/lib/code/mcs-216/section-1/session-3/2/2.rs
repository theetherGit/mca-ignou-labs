#[derive(Debug)]
struct Job {
    id: i32,
    service_time: i32,
}

fn main() {
    let mut jobs = vec![
        Job {
            id: 1,
            service_time: 5,
        },
        Job {
            id: 2,
            service_time: 10,
        },
        Job {
            id: 3,
            service_time: 7,
        },
        Job {
            id: 4,
            service_time: 8,
        },
    ];

    // Sort jobs by service_time ascending
    jobs.sort_by_key(|j| j.service_time);

    let mut finish_time = 0;
    let mut total_system_time = 0;
    let mut sequence = Vec::new();

    for job in jobs {
        finish_time += job.service_time; // Cumulative time for this job
        total_system_time += finish_time; // Total time spent across all jobs
        sequence.push(job.id.to_string());
    }

    println!("Optimal Sequence: {}", sequence.join(" -> "));
    println!("Total Time Spent in System: {}", total_system_time);
}
