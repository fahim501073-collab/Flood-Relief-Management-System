#ifndef PRIORITY_H
#define PRIORITY_H

#include "../include/common.h"
#include <queue>
#include <vector>

struct AreaCompare {
    bool operator()(const Area& a, const Area& b) const {
        if (a.urgency != b.urgency) {
            return a.urgency < b.urgency;
        }

        return a.affectedPeople < b.affectedPeople;
    }
};

inline std::vector<Area> prioritizeAreas(
    const std::vector<Area>& areas
) {
    std::priority_queue<
        Area,
        std::vector<Area>,
        AreaCompare
    > pq;

    for (const auto& area : areas) {
        pq.push(area);
    }

    std::vector<Area> result;

    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }

    return result;
}

#endif
