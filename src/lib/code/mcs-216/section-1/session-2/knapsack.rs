#[derive(Debug)]
struct Item {
    p: f64,
    w: f64,
    ratio: f64,
}

fn solve_knapsack(profits: &[f64], weights: &[f64], mut capacity: f64) -> f64 {
    let mut items: Vec<Item> = profits
        .iter()
        .zip(weights.iter())
        .map(|(&p, &w)| Item { p, w, ratio: p / w })
        .collect();

    // Sort by ratio descending
    // partial_cmp is used because f64 doesn't implement total ordering
    items.sort_by(|a, b| b.ratio.partial_cmp(&a.ratio).unwrap());

    let mut total_profit = 0.0;

    for item in items {
        if capacity <= 0.0 {
            break;
        }

        if item.w <= capacity {
            capacity -= item.w;
            total_profit += item.p;
        } else {
            // Take fraction
            total_profit += item.p * (capacity / item.w);
            capacity = 0.0;
        }
    }
    total_profit
}

fn main() {
    let p3 = vec![12.0, 10.0, 8.0, 11.0, 14.0, 7.0, 9.0];
    let w3 = vec![4.0, 6.0, 5.0, 7.0, 3.0, 1.0, 6.0];
    let capacity = 15.0;

    println!("Result Q3: {:.2}", solve_knapsack(&p3, &w3, capacity));
}
