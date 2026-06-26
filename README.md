# 🚇 Metro Route Planner — C++ (v2.0)

A console-based **Metro Network Management System** built in C++ using core Data Structures and Algorithms. Models a real metro network as a weighted undirected graph and supports shortest-path finding, BFS/DFS traversals, station management, and live network statistics — all via an interactive menu.

---

## 📌 Features

| Feature | Description |
|---|---|
| **Add Station** | Dynamically register metro stations with duplicate validation |
| **Add Route** | Connect stations with distance (km), with duplicate-edge check |
| **Display Metro Map** | Visual adjacency-list view of the full network |
| **Shortest Route (Dijkstra)** | Optimal path with full route, distance, and stations visited |
| **BFS Traversal** | Level-by-level station exploration from any node |
| **DFS Traversal** | Depth-first station exploration using an explicit stack |
| **Search Station** | O(1) lookup via `unordered_map` showing all connections |
| **Network Statistics** | Total stations, routes, and the most-connected hub |
| **Input Validation** | Handles empty input, duplicates, invalid numbers, missing stations |

---

## 🗂️ Project Structure

```
MetroRoutePlanner/
├── main.cpp          # Menu-driven driver; handles all user I/O
├── MetroSystem.h     # Class declaration and STL includes
├── MetroSystem.cpp   # All algorithm implementations
└── README.md
```

---

## ⚙️ How to Compile & Run

```bash
# Compile
g++ -std=c++17 -Wall -o metro main.cpp MetroSystem.cpp

# Run
./metro          # Linux / macOS
metro.exe        # Windows
```

No external libraries required — standard g++ only.

---

## 🗺️ Sample Session

```
  [Loading sample Mumbai Metro data...]
[Success] Station added: Mumbai Central (ID: 0)
[Success] Station added: Dadar        (ID: 1)
...
[Success] Route added: Mumbai Central <-> Dadar (5 km)

╔══════════════════════════════════════╗
║       METRO ROUTE PLANNER  v2.0      ║
╠══════════════════════════════════════╣
║  1. Add Station                      ║
║  4. Find Shortest Route              ║
║  ...                                 ║
╚══════════════════════════════════════╝

Enter choice: 4
  Enter source      : Mumbai Central
  Enter destination : Ghatkopar

========== SHORTEST ROUTE ==========
  From    : Mumbai Central
  To      : Ghatkopar
  --------------------------------------------------
  Route   : Mumbai Central --> Dadar --> Kurla --> Ghatkopar
  --------------------------------------------------
  Stations visited : 4
  Total distance   : 14 km
=====================================
```

---

## 📊 Data Structures Used

| Structure | Usage |
|---|---|
| `vector<vector<pair<int,int>>>` | Dynamic adjacency list (replaces fixed `graph[100]`) |
| `unordered_map<string, int>` | O(1) station name → ID lookup |
| `priority_queue` (min-heap) | Dijkstra's greedy expansion |
| `queue<int>` | BFS traversal |
| `stack<int>` | Iterative DFS traversal |
| `vector<int>` (dist + parent) | Dijkstra distance tracking and path reconstruction |

---

## ⏱️ Time & Space Complexity

### Dijkstra's Algorithm
- **Time:** O((V + E) log V) — where V = stations, E = routes
- **Space:** O(V + E) — adjacency list + dist/parent arrays

### BFS Traversal
- **Time:** O(V + E)
- **Space:** O(V) — visited array + queue

### DFS Traversal
- **Time:** O(V + E)
- **Space:** O(V) — visited array + stack

### Add Station / Search Station
- **Time:** O(1) average — via `unordered_map`
- **Space:** O(1)

### Display Metro Map
- **Time:** O(V + E)
- **Space:** O(1) extra (reads in-place)

---

## 🎯 Resume Bullet Points

- Engineered a **C++ Metro Route Planner** using OOP with a dynamic adjacency list (`vector<vector<pair<int,int>>>`), replacing a fixed-size array to support unlimited stations at runtime.
- Implemented **Dijkstra's Algorithm** with a min-heap priority queue achieving O((V+E) log V) time complexity for computing optimal metro paths with full route reconstruction via parent tracking.
- Integrated **BFS and DFS graph traversals** using STL `queue` and `stack`, enabling complete network exploration and connectivity analysis from any station.
- Built O(1) **station lookup** using `unordered_map<string, int>`, with comprehensive input validation covering duplicate stations, duplicate routes, invalid distances, and missing entries.
- Designed a **modular 3-file C++ architecture** (`main.cpp`, `MetroSystem.h`, `MetroSystem.cpp`) with a menu-driven CLI, clean separation of concerns, and no external library dependencies.

---

## 🎤 Viva / Interview Q&A

**Q1. Why did you use `vector<vector<pair<int,int>>>` instead of `graph[100]`?**

The fixed array `graph[100]` wastes memory and breaks if you add more than 100 stations. The dynamic `vector<vector<...>>` grows on demand using `graph.push_back({})` when a new station is added — it's memory-safe, scalable, and the standard industry approach.

---

**Q2. How does Dijkstra's algorithm work in your project?**

We start from the source with distance 0. A min-heap (priority queue) always picks the nearest unvisited station. For each station, we check all its neighbors — if the new path is shorter than what we recorded, we update `dist[]` and `parent[]`, then push the neighbor into the heap. We reconstruct the path by tracing `parent[]` back from destination to source and reversing it.

---

**Q3. What is the difference between BFS and DFS, and when would you use each?**

BFS uses a queue and explores stations level by level (nearest first). DFS uses a stack and goes as deep as possible before backtracking. In a metro context: BFS is ideal for finding the station with the fewest stops; DFS is useful for detecting connectivity or checking if all stations are reachable. For shortest distance, Dijkstra's is used since edges have weights.

---

**Q4. Why use `unordered_map` instead of `map` for station lookup?**

`unordered_map` gives O(1) average lookup using a hash table, while `map` gives O(log n) using a red-black tree. Since station searches happen frequently (every route addition, every shortest-path query), O(1) lookup gives a significant performance advantage for large networks.

---

**Q5. How did you handle the duplicate route validation?**

Before adding an edge, we iterate over `graph[u]` (the adjacency list of the source station) and check if any existing entry already points to the destination. If found, we print an error and return without modifying the graph. This keeps the graph clean and avoids inflated route counts.

---

## 🧠 Concepts Demonstrated

- Object-Oriented Programming (encapsulation, modular design)
- Graph representation (weighted undirected adjacency list)
- Greedy algorithm (Dijkstra's with min-heap)
- Graph traversals (BFS, DFS)
- STL mastery (`vector`, `unordered_map`, `priority_queue`, `queue`, `stack`)
- Input validation and defensive programming
- Multi-file C++ project organization

---

## 👩‍💻 Author

Built as a DSA portfolio project demonstrating practical applications of graph algorithms in transportation systems.
