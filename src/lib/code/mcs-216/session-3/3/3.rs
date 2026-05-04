#[derive(Debug)]
struct Job {
    id: i32,
    deadline: usize,
    profit: i32,
}

fn main() {
    let mut jobs = vec![
        Job {
            id: 1,
            deadline: 3,
            profit: 50,
        },
        Job {
            id: 2,
            deadline: 4,
            profit: 20,
        },
        Job {
            id: 3,
            deadline: 5,
            profit: 70,
        },
        Job {
            id: 4,
            deadline: 3,
            profit: 15,
        },
        Job {
            id: 5,
            deadline: 2,
            profit: 10,
        },
        Job {
            id: 6,
            deadline: 1,
            profit: 47,
        },
        Job {
            id: 7,
            deadline: 1,
            profit: 60,
        },
    ];

    // Sort by profit descending
    jobs.sort_by(|a, b| b.profit.cmp(&a.profit));

    let max_deadline = jobs.iter().map(|j| j.deadline).max().unwrap_or(0);
    let mut slots = vec![0; max_deadline + 1]; // 0 indicates an empty slot
    let mut total_profit = 0;
    let mut sequence = Vec::new();

    for job in jobs {
        // Find a free slot for this job (from deadline backwards)
        for t in (1..=job.deadline).rev() {
            if slots[t] == 0 {
                slots[t] = job.id;
                total_profit += job.profit;
                sequence.push(job.id);
                break;
            }
        }
    }

    println!("Max Profit: {}", total_profit);
    println!("Scheduled Jobs (in order of assignment): {:?}", sequence);
}
