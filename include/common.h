#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Area {
    int id;
    string name;
    int affectedPeople;
    int urgency;
};

struct Supply {
    string name;
    double weight;
    double value;
    int quantity;
};

struct Activity {
    string name;
    int startTime;
    int endTime;
};

// Divisible relief item (rice, water, ...) used by the fractional knapsack.
struct FractionalItem {
    string name;
    double weight;
    double value;
};

// Indivisible relief item (tent, boat, ...) used by the 0/1 knapsack.
// Weight and value are whole numbers because the DP table is indexed by weight.
struct KnapsackItem {
    string name;
    int weight;
    int value;
};

#endif
