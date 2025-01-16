#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, visited[MAX_N];
vector<ar<int,2>> adj[MAX_N];
vector<int> cost;

void prim(int s = 1) {
    ll cost = 0;
    priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq;
    visited[s] = 1;
    for (auto [u, d] : adj[s])
        if (!visited[u])
            pq.push({d, u});
    while (pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        if (!visited[u]) {
            cost += d;
            visited[u] = 1;
            for (auto [v, w] : adj[u])
                if (!visited[v])
                    pq.push({w, v});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    cout << cost << "\n";
}

// main template for T test cases
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n >> m;

    cost.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cost.push_back(x);
    }

    // Input the edges.
    for (int i = 1; i <=n; i++) {
        for (int j = 1; j <=n; j++) {
            adj[i].push_back({j, cost[i] + cost[j]});
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        // Get weight from graph and compare to w
        if (cost[x] + cost[y] > w) {
            // delete edge x, y from graph
            for (ar<int,2> pair : adj[x]) {
                if (pair[0] == y) {
                    pair[1] = w;
                }
            }
            // adj[x][y][1] = w;
            // adj[x].push_back({y, w});
        }
    }
    prim();
    return 0;
}