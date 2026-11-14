4.algorithms/knapsack01.h


#ifndef KNAPSACK01_H
#define KNAPSACK01_H

#include "../include/common.h"
#include <algorithm>
#include <vector>

struct KnapsackResult {
    int totalValue{};
    int totalWeight{};
    std::vector<std::string> selectedItems;
};

inline KnapsackResult knapsack01(
    int capacity,
    const std::vector<KnapsackItem>& items
) {
    KnapsackResult result;

    if (capacity <= 0) {
        return result;
    }

    int n = static_cast<int>(items.size());

    std::vector<std::vector<int>> dp(
        n + 1,
        std::vector<int>(capacity + 1, 0)
    );

    for (int i = 1; i <= n; i++) {
        const auto& item = items[i - 1];

        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];

            if (item.weight > 0 &&
                item.weight <= w &&
                item.value >= 0) {

                dp[i][w] = std::max(
                    dp[i][w],
                    item.value +
                    dp[i - 1][w - item.weight]
                );
            }
        }
    }

    result.totalValue = dp[n][capacity];

    int remaining = capacity;

    for (int i = n; i >= 1; i--) {
        if (dp[i][remaining] !=
            dp[i - 1][remaining]) {

            const auto& item = items[i - 1];

            result.selectedItems.push_back(item.name);
            result.totalWeight += item.weight;

            remaining -= item.weight;
        }
    }

    std::reverse(
        result.selectedItems.begin(),
        result.selectedItems.end()
    );

    return result;
}

#endif
