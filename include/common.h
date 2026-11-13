
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

#endif
