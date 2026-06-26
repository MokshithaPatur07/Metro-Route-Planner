#ifndef METROSYSTEM_H
#define METROSYSTEM_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <climits>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// ============================================================
// MetroSystem Class
// Represents a metro network using an adjacency list graph.
// Supports station management, route finding, and traversals.
// ============================================================
class MetroSystem {

private:
    // Maps station name -> internal integer ID
    unordered_map<string, int> stationIndex;

    // Stores station names by their ID (index = ID)
    vector<string> stations;

    // Adjacency list: graph[u] = list of {neighbor, distance}
    vector<vector<pair<int, int>>> graph;

    // Tracks total number of routes (edges, undirected)
    int totalRoutes;

    // --------------------------------------------------------
    // Helper: Check if a station name exists
    // --------------------------------------------------------
    bool stationExists(const string& name) const;

    // --------------------------------------------------------
    // Helper: Get station ID; returns -1 if not found
    // --------------------------------------------------------
    int getStationID(const string& name) const;

    // --------------------------------------------------------
    // Helper: Print a divider line for UI formatting
    // --------------------------------------------------------
    void printDivider() const;

public:
    // Constructor
    MetroSystem();

    // --------------------------------------------------------
    // 1. Add a new station to the network
    // --------------------------------------------------------
    void addStation(const string& name);

    // --------------------------------------------------------
    // 2. Add a bidirectional route between two stations
    // --------------------------------------------------------
    void addRoute(const string& source, const string& destination, int distance);

    // --------------------------------------------------------
    // 3. Display the full metro map as an adjacency list
    // --------------------------------------------------------
    void displayMetroMap() const;

    // --------------------------------------------------------
    // 4. Find and display shortest path using Dijkstra's algo
    // --------------------------------------------------------
    void findShortestPath(const string& start, const string& end) const;

    // --------------------------------------------------------
    // 5. Breadth-First Search traversal from a station
    // --------------------------------------------------------
    void bfsTraversal(const string& startStation) const;

    // --------------------------------------------------------
    // 6. Depth-First Search traversal from a station
    // --------------------------------------------------------
    void dfsTraversal(const string& startStation) const;

    // --------------------------------------------------------
    // 7. Search for a station and show its connections
    // --------------------------------------------------------
    void searchStation(const string& name) const;

    // --------------------------------------------------------
    // 8. Display overall network statistics
    // --------------------------------------------------------
    void displayNetworkStats() const;
};

#endif // METROSYSTEM_H
