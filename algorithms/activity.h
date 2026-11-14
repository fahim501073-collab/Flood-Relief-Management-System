2.algorithms/activity.h

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "../include/common.h"
#include <algorithm>
#include <vector>

inline std::vector<Activity> selectActivities(
    std::vector<Activity> activities
) {
    std::sort(
        activities.begin(),
        activities.end(),
        [](const Activity& a, const Activity& b) {
            return a.endTime < b.endTime;
        }
    );

    std::vector<Activity> selected;

    int lastEndTime = -1;

    for (const auto& activity : activities) {
        if (activity.startTime >= 0 &&
            activity.endTime > activity.startTime &&
            (selected.empty() ||
             activity.startTime >= lastEndTime)) {

            selected.push_back(activity);
            lastEndTime = activity.endTime;
        }
    }

    return selected;
}

#endif
