#include "MetroSystem.h"

// ============================================================
// Constructor
// ============================================================
MetroSystem::MetroSystem() : totalRoutes(0) {}

// ============================================================
// Private Helpers
// ============================================================

bool MetroSystem::stationExists(const string& name) const {
    return stationIndex.find(name) != stationIndex.end();
}

int MetroSystem::getStationID(const string& name) const {
    auto it = stationIndex.find(name);
    if (it == stationIndex.end()) return -1;
    return it->second;
}

void MetroSystem::printDivider() const {
    cout << string(50, '-') << endl;
}

// ============================================================
// 1. Add Station
// ============================================================
void MetroSystem::addStation(const string& name) {
    // Validate: empty name
    if (name.empty()) {
        cout << "[Error] Station name cannot be empty.\n";
        return;
    }
    // Validate: duplicate station
    if (stationExists(name)) {
        cout << "[Error] Station \"" << name << "\" already exists.\n";
        return;
    }

    int id = (int)stations.size();
    stationIndex[name] = id;
    stations.push_back(name);

    // Expand the adjacency list with an empty row for this station
    graph.push_back({});

    cout << "[Success] Station added: " << name
         << " (ID: " << id << ")\n";
}

// ============================================================
// 2. Add Route
// ============================================================
void MetroSystem::addRoute(const string& source, const string& destination, int distance) {
    // Validate: stations exist
    if (!stationExists(source)) {
        cout << "[Error] Station \"" << source << "\" not found.\n";
        return;
    }
    if (!stationExists(destination)) {
        cout << "[Error] Station \"" << destination << "\" not found.\n";
        return;
    }
    // Validate: self-loop
    if (source == destination) {
        cout << "[Error] Source and destination cannot be the same station.\n";
        return;
    }
    // Validate: distance
    if (distance <= 0) {
        cout << "[Error] Distance must be a positive value.\n";
        return;
    }

    int u = getStationID(source);
    int v = getStationID(destination);

    // Validate: duplicate route
    for (auto& edge : graph[u]) {
        if (edge.first == v) {
            cout << "[Error] Route between \"" << source
                 << "\" and \"" << destination << "\" already exists.\n";
            return;
        }
    }

    // Add bidirectional edge
    graph[u].push_back({v, distance});
    graph[v].push_back({u, distance});
    totalRoutes++;

    cout << "[Success] Route added: " << source
         << " <-> " << destination
         << " (" << distance << " km)\n";
}

// ============================================================
// 3. Display Metro Map
// ============================================================
void MetroSystem::displayMetroMap() const {
    if (stations.empty()) {
        cout << "[Info] No stations in the network yet.\n";
        return;
    }

    cout << "\n========== METRO MAP (Adjacency List) ==========\n";
    for (int i = 0; i < (int)stations.size(); i++) {
        cout << "  " << left << setw(22) << stations[i] << " --> ";
        if (graph[i].empty()) {
            cout << "(no connections)";
        } else {
            for (int j = 0; j < (int)graph[i].size(); j++) {
                int neighbor = graph[i][j].first;
                int dist     = graph[i][j].second;
                cout << stations[neighbor] << " (" << dist << " km)";
                if (j < (int)graph[i].size() - 1) cout << ",  ";
            }
        }
        cout << "\n";
    }
    cout << "=================================================\n";
}

// ============================================================
// 4. Dijkstra's Shortest Path
// ============================================================
void MetroSystem::findShortestPath(const string& start, const string& end) const {
    // Validate inputs
    if (!stationExists(start)) {
        cout << "[Error] Station \"" << start << "\" not found.\n";
        return;
    }
    if (!stationExists(end)) {
        cout << "[Error] Station \"" << end << "\" not found.\n";
        return;
    }
    if (start == end) {
        cout << "[Info] You are already at \"" << start << "\".\n";
        return;
    }

    int n      = (int)stations.size();
    int source = getStationID(start);
    int dest   = getStationID(end);

    // dist[i] = shortest distance from source to station i
    vector<int> dist(n, INT_MAX);
    // parent[i] = previous station ID on the shortest path
    vector<int> parent(n, -1);

    // Min-heap: {distance, station_id}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int curr     = pq.top().second;
        pq.pop();

        // Skip if we already found a shorter path
        if (currDist > dist[curr]) continue;

        for (auto& edge : graph[curr]) {
            int next   = edge.first;
            int weight = edge.second;

            if (dist[curr] + weight < dist[next]) {
                dist[next]   = dist[curr] + weight;
                parent[next] = curr;
                pq.push({dist[next], next});
            }
        }
    }

    // No path found
    if (dist[dest] == INT_MAX) {
        cout << "[Info] No route available between \""
             << start << "\" and \"" << end << "\".\n";
        return;
    }

    // Reconstruct path using parent array
    vector<string> path;
    for (int cur = dest; cur != -1; cur = parent[cur]) {
        path.push_back(stations[cur]);
    }
    reverse(path.begin(), path.end());

    // Display results
    cout << "\n========== SHORTEST ROUTE ==========\n";
    cout << "  From    : " << start << "\n";
    cout << "  To      : " << end << "\n";
    printDivider();
    cout << "  Route   : ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i < (int)path.size() - 1) cout << " --> ";
    }
    cout << "\n";
    printDivider();
    cout << "  Stations visited : " << path.size() << "\n";
    cout << "  Total distance   : " << dist[dest] << " km\n";
    cout << "=====================================\n";
}

// ============================================================
// 5. BFS Traversal
// ============================================================
void MetroSystem::bfsTraversal(const string& startStation) const {
    if (!stationExists(startStation)) {
        cout << "[Error] Station \"" << startStation << "\" not found.\n";
        return;
    }

    int n     = (int)stations.size();
    int start = getStationID(startStation);

    vector<bool> visited(n, false);
    queue<int> bfsQueue;

    visited[start] = true;
    bfsQueue.push(start);

    cout << "\n========== BFS TRAVERSAL ==========\n";
    cout << "  Starting from: " << startStation << "\n";
    cout << "  Order: ";

    int count = 0;
    while (!bfsQueue.empty()) {
        int curr = bfsQueue.front();
        bfsQueue.pop();

        cout << stations[curr];
        count++;

        for (auto& edge : graph[curr]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                bfsQueue.push(neighbor);
            }
        }

        if (!bfsQueue.empty()) cout << " --> ";
    }

    cout << "\n  Total stations visited: " << count << "\n";
    cout << "====================================\n";
}

// ============================================================
// 6. DFS Traversal (iterative using stack)
// ============================================================
void MetroSystem::dfsTraversal(const string& startStation) const {
    if (!stationExists(startStation)) {
        cout << "[Error] Station \"" << startStation << "\" not found.\n";
        return;
    }

    int n     = (int)stations.size();
    int start = getStationID(startStation);

    vector<bool> visited(n, false);
    stack<int> dfsStack;

    dfsStack.push(start);

    cout << "\n========== DFS TRAVERSAL ==========\n";
    cout << "  Starting from: " << startStation << "\n";
    cout << "  Order: ";

    int count = 0;
    bool first = true;
    while (!dfsStack.empty()) {
        int curr = dfsStack.top();
        dfsStack.pop();

        if (visited[curr]) continue;
        visited[curr] = true;

        if (!first) cout << " --> ";
        cout << stations[curr];
        first = false;
        count++;

        // Push neighbors in reverse for natural left-to-right traversal
        for (int i = (int)graph[curr].size() - 1; i >= 0; i--) {
            int neighbor = graph[curr][i].first;
            if (!visited[neighbor]) {
                dfsStack.push(neighbor);
            }
        }
    }

    cout << "\n  Total stations visited: " << count << "\n";
    cout << "====================================\n";
}

// ============================================================
// 7. Search Station
// ============================================================
void MetroSystem::searchStation(const string& name) const {
    if (!stationExists(name)) {
        cout << "[Error] Station \"" << name << "\" not found in the network.\n";
        return;
    }

    int id = getStationID(name);

    cout << "\n========== STATION INFO ==========\n";
    cout << "  Name       : " << name << "\n";
    cout << "  Station ID : " << id << "\n";
    cout << "  Connections: " << graph[id].size() << "\n";

    if (!graph[id].empty()) {
        cout << "  Connected to:\n";
        for (auto& edge : graph[id]) {
            cout << "    -> " << stations[edge.first]
                 << " (" << edge.second << " km)\n";
        }
    }
    cout << "==================================\n";
}

// ============================================================
// 8. Network Statistics
// ============================================================
void MetroSystem::displayNetworkStats() const {
    cout << "\n========== NETWORK STATISTICS ==========\n";
    cout << "  Total Stations : " << stations.size() << "\n";
    cout << "  Total Routes   : " << totalRoutes << "\n";

    if (!stations.empty()) {
        // Find most connected station
        int maxConn = -1;
        string hub;
        for (int i = 0; i < (int)stations.size(); i++) {
            if ((int)graph[i].size() > maxConn) {
                maxConn = (int)graph[i].size();
                hub = stations[i];
            }
        }
        cout << "  Network Hub    : " << hub
             << " (" << maxConn << " connections)\n";
    }
    cout << "=========================================\n";
}
