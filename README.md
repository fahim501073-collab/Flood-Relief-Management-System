# 🌊 Flood Relief Management System

A C++ based terminal application designed to demonstrate how different Data Structures and Algorithms can support flood relief planning and resource management.

The system uses sample data from affected areas in **Chattogram, Feni, Cumilla, and Noakhali, Bangladesh**.

## 📌 Project Overview

During flood emergencies, proper planning is important for distributing relief resources efficiently.

The Flood Relief Management System demonstrates how algorithms can help with:

- Identifying affected areas and their population.
- Prioritizing areas for relief distribution.
- Finding the shortest relief transportation routes.
- Scheduling relief activities without time conflicts.
- Optimizing relief resources within limited truck capacity.
- Generating relief kits and calculating package combinations.

**Current Version:** C++ Terminal Application

## ✨ Features

The system provides six main features:

### 1\. View Affected Areas

Displays affected unions, their upazilas, districts, affected population, and priority levels.

### 2\. Prioritize Relief Distribution

Uses a **Priority Queue** to rank affected areas based on urgency and the number of affected people.

### 3\. Find Shortest Relief Route

Uses **Dijkstra's Algorithm** to calculate the shortest distance from the Central Relief Hub to affected areas.

### 4\. Select Relief Activities

Uses **Sorting and Greedy Activity Selection** to select the maximum number of non-overlapping relief activities.

### 5\. Optimize Relief Resources

Uses the **Fractional Knapsack Algorithm** to maximize total resource value within a limited truck capacity.

### 6\. Generate Relief Kit

Uses two algorithms:

- **0/1 Knapsack:** Selects the best combination of indivisible relief items within the truck capacity.
- **Coin Change:** Calculates the minimum number of standard food packages required to meet a target quantity.

## 🧠 Algorithms Used

| Algorithm | Purpose |
| --- | --- |
| Priority Queue | Relief distribution prioritization |
| Dijkstra's Algorithm | Shortest route calculation |
| Sorting | Ordering relief activities |
| Greedy Activity Selection | Selecting non-overlapping activities |
| Fractional Knapsack | Resource optimization |
| 0/1 Knapsack | Relief kit selection |
| Coin Change | Minimum package combination |

## 🛠️ Technologies Used

- C++
- Standard Template Library (STL)
- File Handling
- CSV Data Processing
- Data Structures and Algorithms
- Git and GitHub

## 📂 Project Structure

``` text
Flood-Relief-Management-System/
│
├── algorithms/
│   ├── activity.h
│   ├── coin_change.h
│   ├── fractional.h
│   ├── graph.h
│   ├── knapsack01.h
│   └── priority.h
│
├── data/
│   ├── activities.csv
│   ├── areas.csv
│   ├── items.csv
│   └── roads.csv
│
├── include/
│   └── common.h
│
├── main.cpp
├── CMakeLists.txt
└── README.md
```

## ⚙️ How to Run

### Requirements

- A C++ compiler supporting C++17 or later.
- Git (optional).

### Compile

Open the project folder in the terminal and run:

``` bash
g++ -std=c++17 -Wall -Wextra main.cpp -o FloodRelief.exe
```

### Run

On Windows Git Bash:

``` bash
./FloodRelief.exe
```

## 🗺️ Sample Data

The project currently uses CSV files for demonstration:

- `areas.csv` — affected areas and population information.
- `roads.csv` — road connections and distances.
- `items.csv` — relief items, weights, and values.
- `activities.csv` — relief activities and their time slots.

**Note:** The current dataset is illustrative sample data, not live disaster-management or real-time road information.

## 🚀 Future Plans

The following improvements are planned for future versions:

- **Web-Based Interface:** Develop a user-friendly website using HTML, CSS, and JavaScript.
- **Database Integration:** Replace static CSV files with a database for better data management.
- **Interactive Map:** Display affected areas and relief routes on an interactive map.
- **Real-Time Data:** Integrate updated flood information, affected population data, and road conditions from reliable sources.
- **Resource Stock Management:** Track available relief items and warehouse inventory.
- **User Authentication:** Introduce separate access for administrators and relief volunteers.
- **Improved Reporting:** Generate detailed relief distribution and resource management reports.

## 🎯 Project Objective

The main objective of this project is to apply fundamental Data Structures and Algorithms to a practical problem scenario and demonstrate how computational techniques can support efficient flood relief planning.

## 👨‍💻 Development

This project is developed as an academic C++ project with a focus on Data Structures and Algorithms.

**Current Status:** Terminal-based version completed. Future enhancements are planned.

## Team Members

1. Member 1 – Abu Hasnat / 253-115-046
2. Member 2 – Anzu /  253-115-025
3. Member 3 – Sreoshi/  253-115-045

## Course Information

- Course: Algorithm Design and Analysis
- Department: Computer Science and Engineering
- University: Metropolitan University

