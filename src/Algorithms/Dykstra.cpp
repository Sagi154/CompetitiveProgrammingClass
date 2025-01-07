#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

using PII = pair<int, int>; // Pair representing (distance, node).
const int INF = numeric_limits<int>::max(); // Constant representing infinity.

int n, m; // Number of nodes and edges in the graph.
vector<vector<pair<int, int>>> wg; // Adjacency list for weighted graph.
vector<int> dist; // Stores shortest distances from source(s).
vector<int> dad; // Stores the parent of each node for path reconstruction.

/**
 * @brief Implements Dijkstra's algorithm to find the shortest paths
 *        from a given set of source nodes in a weighted graph.
 *
 * @param sources The list of source nodes.
 */
void fast_dijkstra(const vector<int>& sources) {
    // Initialize distances to INF and parents to -1.
    dist = vector<int>(n, INF);
    dad = vector<int>(n, -1);

    // Min-heap (priority queue) to store (distance, node).
    priority_queue<PII, vector<PII>, greater<PII>> Q;

    // Set the distance of each source to 0 and push to the priority queue.
    for (int s : sources) {
        Q.push({0, s});
        dist[s] = 0;
    }

    // Process the priority queue.
    while (!Q.empty()) {
        PII p = Q.top(); // Get the node with the smallest distance.
        Q.pop();
        int here = p.second;

        // Ignore if the distance is outdated (stale entry).
        if (dist[here] != p.first) continue;

        // Relaxation step for all neighbors of the current node.
        for (auto& it : wg[here]) {
            int neighbor = it.first;
            int weight = it.second;

            // If a shorter path is found, update the distance and parent.
            if (dist[here] + weight < dist[neighbor]) {
                dist[neighbor] = dist[here] + weight;
                dad[neighbor] = here;
                Q.push({dist[neighbor], neighbor}); // Push the updated distance to the queue.
            }
        }
    }
}

/**
 * @brief Main function to demonstrate the usage of Dijkstra's algorithm.
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input the number of nodes and edges.
    cin >> n >> m;

    // Initialize the adjacency list.
    wg = vector<vector<pair<int, int>>>(n);

    // Input the edges.
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w; // Edge from x to y with weight w.
        wg[x].push_back({y, w});
    }

    // Define the source nodes.
    vector<int> sources = {0}; // Example: starting from node 0.

    // Run Dijkstra's algorithm.
    fast_dijkstra(sources);

    // Output the shortest distances.
    cout << "Shortest distances from source(s):\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << i << ": INF\n"; // If the node is unreachable, print INF.
        } else {
            cout << i << ": " << dist[i] << "\n"; // Print the shortest distance.
        }
    }

    return 0;
}