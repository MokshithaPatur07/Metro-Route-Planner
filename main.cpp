#include "MetroSystem.h"

// ============================================================
// Helper: Display the main menu
// ============================================================
void displayMenu() {
    cout << "METRO ROUTE PLANNER\n";
    cout << "1. Add Station \n";
    cout << "2. Add Route\n";
    cout << "3. Display Metro Map \n";
    cout << "4. Find Shortest Route\n";
    cout << "5. BFS Traversal\n";
    cout << "6. DFS Traversal \n";
    cout << "7. Search Station\n";
    cout << "8. Network Statistics\n";
    cout << "9. Exit  \n";
    
    cout << "  Enter your choice: ";
}

// ============================================================
// Helper: Read a full line of input safely
// ============================================================
string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// ============================================================
// Main Function
// ============================================================
int main() {
    MetroSystem metro;
    int choice;

    cout << "\n  Welcome to Metro Route Planner!\n";
    cout << "  (You can type station names with spaces)\n";

    // Pre-load sample Mumbai metro data for demonstration
    cout << "\n  [Loading sample Mumbai Metro data...]\n";
    metro.addStation("Mumbai Central");
    metro.addStation("Dadar");
    metro.addStation("Andheri");
    metro.addStation("Bandra");
    metro.addStation("Ghatkopar");
    metro.addStation("Kurla");
    metro.addRoute("Mumbai Central", "Dadar",   5);
    metro.addRoute("Dadar",          "Andheri", 8);
    metro.addRoute("Andheri",        "Bandra",  4);
    metro.addRoute("Bandra",         "Ghatkopar", 10);
    metro.addRoute("Dadar",          "Kurla",   6);
    metro.addRoute("Kurla",          "Ghatkopar", 3);
    cout << "  [Sample data loaded successfully!]\n";

    do {
        displayMenu();

        // Validate integer input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Error] Invalid input. Please enter a number (1-9).\n";
            continue;
        }
        cin.ignore(1000, '\n'); // flush leftover newline

        switch (choice) {

            // --------------------------------------------------
            case 1: { // Add Station
                string name = getInput("  Enter station name: ");
                if (name.empty()) {
                    cout << "[Error] Station name cannot be empty.\n";
                } else {
                    metro.addStation(name);
                }
                break;
            }

            // --------------------------------------------------
            case 2: { // Add Route
                string src  = getInput("  Enter source station      : ");
                string dest = getInput("  Enter destination station : ");
                int dist;
                cout << "  Enter distance (km)        : ";
                if (!(cin >> dist)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "[Error] Invalid distance. Please enter a number.\n";
                } else {
                    cin.ignore(1000, '\n');
                    metro.addRoute(src, dest, dist);
                }
                break;
            }

            // --------------------------------------------------
            case 3: { // Display Metro Map
                metro.displayMetroMap();
                break;
            }

            // --------------------------------------------------
            case 4: { // Find Shortest Route
                string src  = getInput("  Enter source station      : ");
                string dest = getInput("  Enter destination station : ");
                metro.findShortestPath(src, dest);
                break;
            }

            // --------------------------------------------------
            case 5: { // BFS Traversal
                string start = getInput("  Enter starting station for BFS: ");
                metro.bfsTraversal(start);
                break;
            }

            // --------------------------------------------------
            case 6: { // DFS Traversal
                string start = getInput("  Enter starting station for DFS: ");
                metro.dfsTraversal(start);
                break;
            }

            // --------------------------------------------------
            case 7: { // Search Station
                string name = getInput("  Enter station name to search: ");
                metro.searchStation(name);
                break;
            }

            // --------------------------------------------------
            case 8: { // Network Statistics
                metro.displayNetworkStats();
                break;
            }

            // --------------------------------------------------
            case 9: { // Exit
                cout << "\n  Thank you for using Metro Route Planner. Goodbye!\n\n";
                break;
            }

            // --------------------------------------------------
            default: {
                cout << "[Error] Invalid choice. Please enter a number between 1 and 9.\n";
            }
        }

    } while (choice != 9);

    return 0;
}
