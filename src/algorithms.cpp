#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size

/* ------- BFS --------- */
class BFS {
  vector<int> d;
  vector<int> source;
void BFS(const vector<vector<int>>& graph, int start_node) {
    vector<int> color;  // Set to track visited nodes
    queue<int> q;                // Queue for BFS
    for (int i = 0; i < n; i++) {
      color[i] = 0;
      d[i] = 1000000000;
      source[i] = null;
    }
    color[start_node] = 1;
    d[start_node] = 0;
    source[start_node] = null;
    q.push(start_node);
    // Finished initialization

    // Main loop
    while (!q.empty()) {
        int node = q.front();
        cout << node << " ";  // Process the current node (you can do other actions here)

        // Visit all unvisited neighbors
        for (int neighbor : graph[node]) {
          if (color[neighbor] == 0){
            color[neighbor] = 1; // Turn to grey
            d[neighbor] = d[node] + 1;
            source[neighbor] = node;
            q.push(neighbor);
            }
        }
        q.pop();
        color[node] = 2; // Turn to black
    }
}
};

/* ------- DFS --------- */
class DFS {
    vector<vector<int>> g;
    vector<bool> visible;
    void dfs(int cur) {
        visible[cur] = true;
        for(int s : g[cur]) {
            if(visible[s]) continue;
            dfs(s);
        }
    }
};

/* ------- Tarjan --------- */
// Algorithm for finding strongly connected components
class Tarjan {

    vector<int> g[MAXN];
    int d[MAXN], low[MAXN], scc[MAXN];
    bool stacked[MAXN];
    stack<int> s;
    int ticks,current_scc;
    void tarjan(int u) {
        d[u]=low[u] = ticks++;
        s.push(u);
        stacked[u] = true;
        const vector<int> &out = g[u];
        for(int k = 0, m = out.size();k < m;++k) {
            const int &v = out[k];
            if( d[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (stacked[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        if (d[u] == low[u]) {
            int v;
            do {
                v = s.top();
                s.pop();
                stacked[v] = false;
                scc[v] = current_scc;
            } while(u != v);
            current_scc++;
        }
    }

};


void solve(){
  return;
  }

int N = 5;
vector<int> vect(N); // Creating vector of size N

// main template
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  cin >> T;
  while (T--){
    solve();
    }
  return 0;
  }