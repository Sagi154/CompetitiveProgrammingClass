#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size

// main template
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 1;
    cin >> n;
    int count = 1;
    vector<vector<int>> adj(n+1);
    for (int i = 2; i <=n; ++i) {
      int node;
      cin >> node;
      adj[i].push_back(node);
      adj[node].push_back(i);
    }
    vector<int> colors(n+1);
    for (int i = 1; i <= n; ++i) {
      cin >> colors[i];
    }
    vector<int> color(n+1);  // Set to track visited nodes
    queue<int> q;                // Queue for BFS
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }
    color[1] = 1;
    q.push(1);
    // Finished initialization

    // Main loop
    while (!q.empty()) {
        int node = q.front();
        // Visit all unvisited neighbors
        for (int neighbor : adj[node]) {
            if (color[neighbor] == 0){
                color[neighbor] = 1; // Turn to grey
                if (colors[neighbor] != colors[node]) {
                    count++;
                  }
                q.push(neighbor);
            }
        }
        q.pop();
        color[node] = 2; // Turn to black
    }
    cout << count << endl;
}