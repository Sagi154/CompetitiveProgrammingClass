#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000; // A large constant to represent infinity for unreachable nodes.
int n; // Number of nodes in the graph.
vector<vector<int>> d; // Distance matrix representing the graph.

// Initialization:
// d[i][i] = 0
// If there's an edge (i, j) with weight w, set d[i][j] = w. Otherwise, set d[i][j] = INF.

/**
 * @brief Implements the Floyd-Warshall algorithm to find the shortest paths
 *        between all pairs of nodes in the graph.
 */
void floyd_warshall() {
    // Iterate through all intermediate nodes k.
    for (int k = 0; k < n; ++k) {
        // Iterate through all pairs of nodes (i, j).
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Update the shortest path using the intermediate node k.
                if (d[i][k] < INF && d[k][j] < INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}

/**
 * @brief Main function to demonstrate the usage of the Floyd-Warshall algorithm.
 */
int main() {
    // Input the number of nodes.
    cin >> n;

    // Initialize the distance matrix.
    d = vector<vector<int>>(n, vector<int>(n, INF));

    // Input the graph.
    // Input the number of edges.
    int m; // Number of edges.
    cin >> m;

    // Read the edges and their weights.
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = w; // Set the weight of the edge from u to v.
    }

    // Set diagonal elements to 0 (distance from any node to itself is 0).
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }

    // Run the Floyd-Warshall algorithm.
    floyd_warshall();

    // Output the shortest path matrix.
    cout << "Shortest distances between all pairs of nodes:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] == INF) {
                cout << "INF "; // If there's no path, print "INF".
            } else {
                cout << d[i][j] << " "; // Otherwise, print the distance.
            }
        }
        cout << "\n";
    }

    return 0;
}