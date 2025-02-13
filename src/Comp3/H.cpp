// Kosaraju's algorithm to find strongly connected components (SCCs) by running DFS twice
// 1st pass done on the original graph and record the topological order of the nodes
// 2nd pass done on the transposed graph using the order found in the 1st pass
// Time complexity: O(n + m)
// Problem link: https://cses.fi/problemset/task/1682/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, scc, visited[MAX_N];
vector<int> adj[2][MAX_N], comp[MAX_N], dfn;
// adj[0] is the original graph, adj[1] is the transposed graph

// t = 0 means 1st pass, t = 1 means 2nd pass
void dfs(int u, int t) {
    visited[u] = 1;
    if (t == 1) comp[scc].push_back(u);
    for (int v : adj[t][u]) {
        if (!visited[v]) {
            dfs(v, t);
        }
    }
    if (t == 0) dfn.push_back(u);
}

void kosaraju() {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    memset(visited, 0, sizeof visited);
    for (int i = n - 1; i >= 0; i--) {
        if (!visited[dfn[i]]) {
            scc++;
            dfs(dfn[i], 1);
        }
    }
}

void solve() {
    cin >> n >> m;
    int capital;
    cin >> capital;
    int count = 0;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }
    kosaraju();
    for (int i = 1; i <= n; i++) {
        if (comp[i].size() == 0 && i != capital) {
            count++;

        }
    }
    cout << count << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    solve();
}