#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int bfs(int start1, int start2, const vector<vector<int>>& adj, const vector<int>& color, int N) {
    vector<int> dist1(N + 1, -1);  // Distance array for Player1
    vector<int> dist2(N + 1, -1);  // Distance array for Player2

    queue<int> queue1, queue2;

    dist1[start1] = 0;  // Player1 starts at vertex 1
    dist2[start2] = 0;  // Player2 starts at vertex N

    queue1.push(start1);
    queue2.push(start2);

    while (!queue1.empty() || !queue2.empty()) {
        // Process Player1's queue
        if (!queue1.empty()) {
            int current1 = queue1.front();
            queue1.pop();

            // Visit all adjacent vertices of Player1
            for (int neighbor : adj[current1]) {
                if (dist1[neighbor] == -1) {  // If not visited
                    dist1[neighbor] = dist1[current1] + 1;
                    queue1.push(neighbor);
                }
            }
        }

        // Process Player2's queue
        if (!queue2.empty()) {
            int current2 = queue2.front();
            queue2.pop();

            // Visit all adjacent vertices of Player2
            for (int neighbor : adj[current2]) {
                if (dist2[neighbor] == -1) {  // If not visited
                    dist2[neighbor] = dist2[current2] + 1;
                    queue2.push(neighbor);
                }
            }
        }
    }

    // If both players reach their target positions
    if (dist1[N] != -1 && dist2[1] != -1) {
        return max(dist1[N], dist2[1]);  // Return the maximum number of moves
    } else {
        return -1;  // If it's impossible
    }
}

void solve() {
    int T;
    cin >> T;  // Read number of test cases

    while (T--) {
        int N, M;
        cin >> N >> M;  // Read N (vertices) and M (edges)

        vector<int> color(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> color[i];  // Read the color array
        }

        vector<vector<int>> adj(N + 1);  // Adjacency list

        // Read edges and build the graph
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Run BFS from vertex 1 (Player1's start) and vertex N (Player2's start)
        cout << bfs(1, N, adj, color, N) << endl;
    }
}

int main() {
    solve();
    return 0;
}