# Fractional Knapsack in Python
def get_max_value(profits, weights, capacity):
    # Calculate profit/weight ratio and keep track of original index
    items = []
    for i in range(len(profits)):
        items.append(
            {
                "id": i + 1,
                "profit": profits[i],
                "weight": weights[i],
                "ratio": profits[i] / weights[i],
            }
        )

    # Sort items by ratio in descending order (Greedy Strategy)
    items.sort(key=lambda x: x["ratio"], reverse=True)

    total_value = 0.0
    for item in items:
        if capacity > 0 and capacity >= item["weight"]:
            # Take the full item
            capacity -= item["weight"]
            total_value += item["profit"]
        elif capacity > 0:
            # Take a fraction of the item to fill remaining capacity
            total_value += item["profit"] * (capacity / item["weight"])
            capacity = 0
            break

    return total_value


# Solving Question 1
p1, w1, c1 = [15, 5, 20, 8, 7, 20, 6], [3, 4, 6, 8, 2, 2, 3], 18
print(f"Result Q1: {get_max_value(p1, w1, c1):.2f}")
