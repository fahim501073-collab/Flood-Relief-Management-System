
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/common.h"
#include "algorithms/priority.h"
#include "algorithms/graph.h"
#include "algorithms/activity.h"
#include "algorithms/fractional.h"
#include "algorithms/knapsack01.h"
#include "algorithms/coin_change.h"

using namespace std;

namespace {

const int TRUCK_CAPACITY = 80;

struct Road {
    string source;
    string destination;
    int distance;
};

// Remove extra spaces
string trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");

    if (first == string::npos)
        return "";

    const size_t last = value.find_last_not_of(" \t\r\n");

    return value.substr(first, last - first + 1);
}

// Split CSV line
vector<string> splitCsv(const string& line) {
    vector<string> fields;
    string field;
    stringstream input(line);

    while (getline(input, field, ',')) {
        fields.push_back(trim(field));
    }

    if (!line.empty() && line.back() == ',')
        fields.push_back("");

    return fields;
}

// Convert string to integer
bool parseInt(const string& text, int& number) {
    try {
        size_t used = 0;
        string cleaned = trim(text);

        number = stoi(cleaned, &used);

        return used == cleaned.size();
    }
    catch (...) {
        return false;
    }
}

// Section heading
void printHeader(const string& title) {
    cout << "\n============================================================\n";
    cout << "  " << title << '\n';
    cout << "============================================================\n";
}

// Load affected areas
bool loadAreas(vector<Area>& areas) {
    ifstream file("data/areas.csv");

    if (!file.is_open())
        return false;

    areas.clear();

    string line;
    getline(file, line);

    int id = 0;

    while (getline(file, line)) {
        if (trim(line).empty())
            continue;

        vector<string> fields = splitCsv(line);

        if (fields.size() < 5)
            continue;

        int affectedPeople = 0;
        int urgency = 0;

        if (!parseInt(fields[3], affectedPeople) ||
            !parseInt(fields[4], urgency))
            continue;

        if (affectedPeople < 0 || urgency < 1 || urgency > 5)
            continue;

        string fullName =
            fields[0] + " - " +
            fields[1] + " - " +
            fields[2];

        areas.push_back({
            id++,
            fullName,
            affectedPeople,
            urgency
        });
    }

    return true;
}

// Load relief items
bool loadItems(
    vector<FractionalItem>& fractionalItems,
    vector<KnapsackItem>& indivisibleItems
) {
    ifstream file("data/items.csv");

    if (!file.is_open())
        return false;

    fractionalItems.clear();
    indivisibleItems.clear();

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (trim(line).empty())
            continue;

        vector<string> fields = splitCsv(line);

        if (fields.size() < 3)
            continue;

        int weight = 0;
        int value = 0;

        if (!parseInt(fields[1], weight) ||
            !parseInt(fields[2], value))
            continue;

        if (fields[0].empty() || weight <= 0 || value < 0)
            continue;

        fractionalItems.push_back({
            fields[0],
            static_cast<double>(weight),
            static_cast<double>(value)
        });

        indivisibleItems.push_back({
            fields[0],
            weight,
            value
        });
    }

    return true;
}

// Load road network
bool loadRoads(vector<Road>& roads) {
    ifstream file("data/roads.csv");

    if (!file.is_open())
        return false;

    roads.clear();

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (trim(line).empty())
            continue;

        vector<string> fields = splitCsv(line);

        if (fields.size() < 3)
            continue;

        int distance = 0;

        if (fields[0].empty() ||
            fields[1].empty() ||
            !parseInt(fields[2], distance) ||
            distance < 0)
            continue;

        roads.push_back({
            fields[0],
            fields[1],
            distance
        });
    }

    return true;
}

// Load activity data
bool loadActivities(vector<Activity>& activities) {
    ifstream file("data/activities.csv");

    if (!file.is_open())
        return false;

    activities.clear();

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (trim(line).empty())
            continue;

        vector<string> fields = splitCsv(line);

        if (fields.size() < 3)
            continue;

        int start = 0;
        int finish = 0;

        if (fields[0].empty() ||
            !parseInt(fields[1], start) ||
            !parseInt(fields[2], finish))
            continue;

        if (start < 0 || finish <= start || finish > 24)
            continue;

        activities.push_back({
            fields[0],
            start,
            finish
        });
    }

    return true;
}

// 1. View Affected Areas
void viewAffectedAreas(const vector<Area>& areas) {
    printHeader("AFFECTED AREAS");

    if (areas.empty()) {
        cout << "No area data found. Check data/areas.csv.\n";
        return;
    }

    cout << left << setw(48) << "Priority Area"
         << right << setw(18) << "Affected People"
         << setw(12) << "Priority" << '\n';

    cout << string(78, '-') << '\n';

    long long total = 0;

    for (const Area& area : areas) {
        cout << left << setw(48) << area.name
             << right << setw(18) << area.affectedPeople
             << setw(12) << (to_string(area.urgency) + "/5")
             << '\n';

        total += area.affectedPeople;
    }

    cout << string(78, '-') << '\n';

    cout << "Total affected people (demo data): "
         << total << '\n';
}

// 2. Prioritize Relief Distribution
void prioritizeRelief(const vector<Area>& areas) {
    printHeader("PRIORITIZE RELIEF DISTRIBUTION - PRIORITY QUEUE");

    vector<Area> prioritized = prioritizeAreas(areas);

    if (prioritized.empty()) {
        cout << "No area data found. Check data/areas.csv.\n";
        return;
    }

    cout << left << setw(8) << "Rank"
         << setw(48) << "Priority Area"
         << right << setw(16) << "Affected People"
         << setw(12) << "Priority" << '\n';

    cout << string(84, '-') << '\n';

    int rank = 1;

    for (const Area& area : prioritized) {
        cout << left << setw(8) << rank++
             << setw(48) << area.name
             << right << setw(16) << area.affectedPeople
             << setw(12) << (to_string(area.urgency) + "/5")
             << '\n';
    }

    cout << "\nHigher urgency is ranked first; "
         << "affected population breaks ties.\n";
}

// 3. Find Shortest Relief Route
void findShortestRoutes(const vector<Area>& areas) {
    printHeader("SHORTEST RELIEF ROUTE - DIJKSTRA'S ALGORITHM");

    vector<Road> roads;

    if (!loadRoads(roads)) {
        cout << "Could not open data/roads.csv.\n";
        return;
    }

    if (roads.empty()) {
        cout << "No road data found in data/roads.csv.\n";
        return;
    }

    vector<string> nodeNames;
    unordered_map<string, int> nodeIds;

    auto getNodeId = [&](const string& name) {
        auto found = nodeIds.find(name);

        if (found != nodeIds.end())
            return found->second;

        int id = static_cast<int>(nodeNames.size());

        nodeNames.push_back(name);
        nodeIds[name] = id;

        return id;
    };

    const int source = getNodeId("Central Relief Hub");

    for (const Road& road : roads) {
        getNodeId(road.source);
        getNodeId(road.destination);
    }

    for (const Area& area : areas) {
        getNodeId(area.name);
    }

    Graph graph(static_cast<int>(nodeNames.size()));

    int loadedRoads = 0;

    for (const Road& road : roads) {
        if (graph.addRoad(
            nodeIds[road.source],
            nodeIds[road.destination],
            road.distance
        )) {
            ++loadedRoads;
        }
    }

    vector<int> distances = graph.dijkstra(source);

    const int INF = numeric_limits<int>::max();

    vector<pair<int, string>> results;
    vector<string> unreachable;

    for (const Area& area : areas) {
        int id = nodeIds[area.name];

        if (distances[id] == INF)
            unreachable.push_back(area.name);
        else
            results.push_back({distances[id], area.name});
    }

    sort(results.begin(), results.end());

    cout << "Starting point: Central Relief Hub\n\n";

    cout << left << setw(52) << "Destination"
         << right << "Shortest Distance\n";

    cout << string(72, '-') << '\n';

    for (const auto& result : results) {
        cout << left << setw(52) << result.second
             << right << result.first << " km\n";
    }

    for (const string& name : unreachable) {
        cout << left << setw(52) << name
             << right << "No connected route\n";
    }

    cout << "\nRoad connections loaded: "
         << loadedRoads << '\n';

    cout << "Note: Distances are illustrative project data, "
         << "not verified live road distances.\n";
}

// 4. Select Relief Activities
void selectReliefActivities(const vector<Activity>& activities) {
    printHeader("SELECT RELIEF ACTIVITIES - GREEDY ACTIVITY SELECTION");

    vector<Activity> selected = selectActivities(activities);

    if (selected.empty()) {
        cout << "No compatible activities found. "
             << "Check data/activities.csv.\n";
        return;
    }

    cout << left << setw(7) << "No."
         << setw(34) << "Activity"
         << setw(16) << "Start Time"
         << "End Time\n";

    cout << string(73, '-') << '\n';

    for (size_t i = 0; i < selected.size(); ++i) {
        cout << left << setw(7) << i + 1
             << setw(34) << selected[i].name
             << setw(16)
             << (to_string(selected[i].startTime) + ":00")
             << selected[i].endTime << ":00\n";
    }

    cout << "\nTotal selected activities: "
         << selected.size() << '\n';

    cout << "Schedule uses the sample time slots "
         << "in data/activities.csv.\n";
}

// 5. Optimize Relief Resources
void optimizeReliefResources(
    const vector<FractionalItem>& items
) {
    printHeader("OPTIMIZE RELIEF RESOURCES - FRACTIONAL KNAPSACK");

    if (items.empty()) {
        cout << "No relief items found. Check data/items.csv.\n";
        return;
    }

    FractionalResult result =
        fractionalKnapsack(TRUCK_CAPACITY, items);

    cout << fixed << setprecision(2);

    cout << "Truck capacity       : "
         << TRUCK_CAPACITY << " kg\n";

    cout << "Used capacity        : "
         << result.usedWeight << " kg\n";

    cout << "Remaining capacity   : "
         << TRUCK_CAPACITY - result.usedWeight << " kg\n";

    cout << "Maximum total value  : "
         << result.totalValue << '\n';

    cout << "\nFractional Knapsack allows taking part of an item.\n";
}

// 6. Generate Relief Kit + Relief Package Combination
void generateReliefKit(const vector<KnapsackItem>& items) {
    printHeader("GENERATE RELIEF KIT - 0/1 KNAPSACK");

    if (items.empty()) {
        cout << "No relief items found. Check data/items.csv.\n";
        return;
    }

    KnapsackResult result =
        knapsack01(TRUCK_CAPACITY, items);

    cout << "Truck capacity: "
         << TRUCK_CAPACITY << " kg\n\n";

    cout << "Selected relief items:\n";
    cout << string(48, '-') << '\n';

    if (result.selectedItems.empty()) {
        cout << "No items can be selected within this capacity.\n";
    }
    else {
        for (const string& item : result.selectedItems) {
            cout << "- " << item << '\n';
        }
    }

    cout << string(48, '-') << '\n';

    cout << "Total loaded weight : "
         << result.totalWeight << " kg\n";

    cout << "Total item value    : "
         << result.totalValue << '\n';

    cout << "Remaining capacity  : "
         << TRUCK_CAPACITY - result.totalWeight << " kg\n";


    // Coin Change Algorithm:
    // Calculate minimum relief packages required.

    cout << "\n============================================================\n";
    cout << "          RELIEF PACKAGE COMBINATION\n";
    cout << "============================================================\n";

    cout << "Available package sizes: 7 kg, 5 kg, 3 kg\n";

    cout << "Enter required food quantity in kg (0 to skip): ";

    int amount = 0;

    if (!(cin >> amount)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid quantity. Calculation skipped.\n";
        return;
    }

    if (amount < 0) {
        cout << "Negative quantity is not valid.\n";
        return;
    }

    if (amount == 0)
        return;

    CoinChangeResult change = coinChange(
        amount,
        {7, 5, 3}
    );

    if (!change.possible) {
        cout << "Exact package combination is not possible.\n";
        return;
    }

    cout << "\nMinimum number of packages required: "
         << change.minimumCoins << '\n';

    cout << "Package sizes selected: ";

    for (size_t i = 0; i < change.coinsUsed.size(); ++i) {
        if (i)
            cout << " + ";

        cout << change.coinsUsed[i] << " kg";
    }

    cout << "\nTotal food quantity: "
         << amount << " kg\n";

    cout << "\nCoin Change calculation completed.\n";
}

// Read menu choice
int readMenuChoice() {
    int choice;

    while (true) {
        cout << "\nEnter your choice: ";

        if (cin >> choice)
            return choice;

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Invalid input! Please enter a number.\n";
    }
}

// Main Menu
void showMenu() {
    cout << "\n========================================\n";
    cout << "     FLOOD RELIEF MANAGEMENT SYSTEM\n";
    cout << "========================================\n\n";

    cout << "1. View Affected Areas\n";
    cout << "2. Prioritize Relief Distribution\n";
    cout << "3. Find Shortest Relief Route\n";
    cout << "4. Select Relief Activities\n";
    cout << "5. Optimize Relief Resources\n";
    cout << "6. Generate Relief Kit\n";
    cout << "0. Exit\n";
}

} // namespace

// Main Function
int main() {
    vector<Area> areas;

    vector<FractionalItem> fractionalItems;
    vector<KnapsackItem> knapsackItems;

    vector<Activity> activities;

    if (!loadAreas(areas)) {
        cerr << "Error: Could not open data/areas.csv. "
             << "Run from the project root folder.\n";

        return 1;
    }

    if (!loadItems(fractionalItems, knapsackItems)) {
        cerr << "Error: Could not open data/items.csv.\n";

        return 1;
    }

    if (!loadActivities(activities)) {
        cerr << "Error: Could not open data/activities.csv.\n";

        return 1;
    }

    int choice;

    do {
        showMenu();

        choice = readMenuChoice();

        switch (choice) {

            case 1:
                viewAffectedAreas(areas);
                break;

            case 2:
                prioritizeRelief(areas);
                break;

            case 3:
                findShortestRoutes(areas);
                break;

            case 4:
                selectReliefActivities(activities);
                break;

            case 5:
                optimizeReliefResources(fractionalItems);
                break;

            case 6:
                generateReliefKit(knapsackItems);
                break;

            case 0:
                cout << "\nThank you for using "
                     << "Flood Relief Management System.\n";

                cout << "Stay Safe!\n";
                break;

            default:
                cout << "Invalid choice! "
                     << "Please enter a number between 0 and 6.\n";
        }

    } while (choice != 0);

    return 0;
}
