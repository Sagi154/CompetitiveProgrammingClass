#include <iostream>
#include <vector>
#include <array>
#include <limits>

using namespace std;

using ll = long long;
const ll INF = 1e18; // Define a large value representing infinity for unreachable nodes.

int n; // Number of nodes in the graph.
vector<array<int, 3>> edges; // Stores edges in the format {u, v, w} where u -> v with weight w.
vector<int> parent; // Stores the parent of each node for path reconstruction.
vector<ll> dist; // Stores the shortest distances from the source node.
bool has_negative_cycle = false; // Indicates if a negative weight cycle is detected.
int cycle_start = -1; // Start node of a negative weight cycle if detected.

/**
 * @brief Implements the Bellman-Ford algorithm to calculate the shortest distances
 *        from a given source node and detect negative weight cycles in the graph.
 *
 * @param source The source node from which to calculate shortest paths.
 */
void bellman_ford(int source) {
    // Initialize distance array with INF and parent array with 0.
    dist = vector<ll>(n, INF);
    parent = vector<int>(n, 0);
    dist[source] = 0; // Distance to the source node is 0.

    // Relax edges up to n - 1 times to ensure shortest paths are found.
    for (int iter = 1; iter <= n; iter++) {
        has_negative_cycle = false; // Reset negative cycle flag for each iteration.

        // Relax all edges in the graph.
        for (auto &[u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                has_negative_cycle = true; // A shorter path is found, indicating potential cycle.
                dist[v] = dist[u] + w; // Update the shortest distance.
                parent[v] = u; // Update the parent for path reconstruction.
                cycle_start = v; // Update the cycle start for negative cycle detection.
            }
        }
    }
}

/**
 * @brief Main function to demonstrate the usage of the Bellman-Ford algorithm.
 */
int main() {
    // Input the number of nodes and edges in the graph.
    int m; // Number of edges.
    cin >> n >> m;

    // Resize the edges vector and read the graph edges.
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Read edge (u -> v) with weight w.
        edges[i] = {u, v, w};
    }

    // Run the Bellman-Ford algorithm from source node 0.
    bellman_ford(0);

    // Output results.
    if (has_negative_cycle) {
        cout << "Negative weight cycle detected.\n";
        // Negative weight cycles can be further handled if required.
    } else {
        cout << "Shortest distances from source:\n";
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INF) {
                cout << i << ": INF\n"; // If the node is unreachable, print INF.
            } else {
                cout << i << ": " << dist[i] << "\n"; // Print the shortest distance.
            }
        }
    }

    return 0;
}