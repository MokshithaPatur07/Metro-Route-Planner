# Metro Route Planner

This is a simple C++ project that simulates a metro route system using graph data structures. It allows users to add stations, connect them with routes, and find the shortest path between two stations.

## Features

* Add new metro stations
* Add routes between stations
* Find the shortest path using Dijkstra's Algorithm
* Display all stations and routes
* BFS and DFS traversal
* Fast station search using `unordered_map`

## Concepts Used

* Graph (Adjacency List)
* Dijkstra's Algorithm
* BFS & DFS
* Hash Map (`unordered_map`)
* Priority Queue
* Object-Oriented Programming (OOP)

## Files

* `main.cpp` – Menu-driven program
* `MetroSystem.h` – Class declarations
* `MetroSystem.cpp` – Function definitions

## How to Run

```bash
g++ main.cpp MetroSystem.cpp -o metro
./metro
```

## What I Learned

* How graphs are represented using adjacency lists
* Implementing Dijkstra's Algorithm for shortest path
* Using STL containers like `vector`, `unordered_map`, and `priority_queue`
