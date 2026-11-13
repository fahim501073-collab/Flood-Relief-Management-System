
# Flood Relief Management System

## Project Description

Flood Relief Management System is a C++ based
project designed to support the management and
distribution of relief resources in flood-affected areas.

The system uses different algorithms to prioritize
affected areas, optimize resource allocation,
manage relief activities, and analyze transportation
routes.

## Objectives

- Prioritize flood-affected areas based on urgency.
- Analyze connectivity between affected areas.
- Find shortest routes between connected areas.
- Schedule relief distribution activities.
- Allocate relief supplies efficiently.
- Calculate suitable voucher denominations.

## Algorithms Used

1. Priority Queue – Prioritizing flood-affected areas.
2. Graph (Dijkstra's Algorithm) – Finding shortest routes.
3. Activity Selection – Scheduling relief activities.
4. Fractional Knapsack – Allocating divisible relief supplies.
5. 0/1 Knapsack – Selecting indivisible relief items.
6. Coin Change – Calculating voucher denominations.

## Technologies Used

- C++ (Core Programming Language)
- Crow Framework (Backend)
- HTML (Frontend Structure)
- CSS (Frontend Design)
- JavaScript (Frontend Interaction)
- JSON (Data Exchange)
- CMake (Build System)
- Git & GitHub (Version Control)

## Main Features

- Flood-affected area prioritization.
- Area connectivity and route analysis.
- Relief activity scheduling.
- Efficient relief supply allocation.
- Voucher denomination calculation.
- Web-based user interface.

## Project Structure

```text
Flood-Relief-Management-System/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   └── common.h
├── algorithms/
│   ├── priority.h
│   ├── graph.h
│   ├── activity.h
│   ├── fractional.h
│   ├── knapsack01.h
│   └── coin_change.h
├── backend/
│   └── server.cpp
├── frontend/
│   ├── index.html
│   ├── css/
│   │   └── style.css
│   └── js/
│       └── script.js
└── data/
    ├── areas.json
    ├── roads.json
    └── supplies.json
```

## How to Run

The project will use CMake to build the C++ Crow backend.

Build and execution instructions will be added after backend configuration is completed.

## Team Members

1. Member 1 – Abu Hasnat / 253-115-046
2. Member 2 – Anzu /  253-115-025
3. Member 3 – Sreoshi/  253-115-045

## Course Information

- Course: Algorithm Design and Analysis
- Department: Computer Science and Engineering
- University: Metropolitan University

## Academic Note

This project is developed for academic purposes. It demonstrates the practical application of algorithm design and analysis in a simulated flood relief management scenario.
