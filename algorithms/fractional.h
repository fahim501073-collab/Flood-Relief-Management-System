3.algorithms/fractional.h

#ifndef FRACTIONAL_H
#define FRACTIONAL_H

#include "../include/common.h"
#include <algorithm>
#include <vector>

struct FractionalResult {
    double totalValue{};
    double usedWeight{};
};

inline FractionalResult fractionalKnapsack(
    double capacity,
    std::vector<FractionalItem> items
) {
    FractionalResult result;

    if (capacity <= 0) {
        return result;
    }

    items.erase(
        std::remove_if(
            items.begin(),
            items.end(),
            [](const FractionalItem& item) {
                return item.weight <= 0 || item.value < 0;
            }
        ),
        items.end()
    );

    std::sort(
        items.begin(),
        items.end(),
        [](const FractionalItem& a,
           const FractionalItem& b) {
            return (a.value / a.weight) >
                   (b.value / b.weight);
        }
    );

    for (const auto& item : items) {
        if (result.usedWeight >= capacity) {
            break;
        }

        double remaining =
            capacity - result.usedWeight;

        double fraction =
            std::min(1.0, remaining / item.weight);

        result.totalValue += item.value * fraction;
        result.usedWeight += item.weight * fraction;
    }

    return result;
}

#endif
