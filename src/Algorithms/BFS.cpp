#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int n, m;
vector<int> graph[MAX_N];
vector<int> dist;

void bfs(int s) {
    dist.assign(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        q.pop();
    }
}

void solve() {
    cin >> n >> m; // n num of vertices, m num of edges
    for (int i = 0; i < m; i++) { // Build graph from input with adjacency list
        int u, v; cin >> u >> v;
        graph[u].push_back(v); // add edge e = (u,v)
        graph[v].push_back(u); // add edge e = (v,u)
    }
    bfs(1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}