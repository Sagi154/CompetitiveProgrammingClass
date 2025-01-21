#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

ll n;
vector<ll> vis, val;
vector<vector<ll>> adj, dp;

void dfs(ll u) {
    vis[u] = 1;

    if (adj[u].empty()) {
        // Leaf node: all citizens are caught here
        dp[u] = {val[u], 0, 1};
        return;
    }

    ll tmp_max = -1;
    dp[u] = {0, 0, 0};

    for (ll v : adj[u]) {
        if (!vis[v]) dfs(v);
    }

    for (ll v : adj[u]) {
        tmp_max = max(tmp_max, dp[v][0]);
        dp[u][2] += dp[v][2]; // Total leaf nodes in subtree
    }
    dp[u][0] = tmp_max;

    for (ll v : adj[u]) {
        if (dp[v][0] < tmp_max) {
            dp[u][1] += dp[v][1] + dp[v][2] * (tmp_max - dp[v][0]);
        } else {
            dp[u][1] += dp[v][1];
        }
    }

    // Citizens at this node try to minimize their capture
    if (val[u] > dp[u][1]) {
        ll tmp = val[u] - dp[u][1];
        dp[u][0] += (tmp + dp[u][2] - 1) / dp[u][2]; // Equivalent to ceil(tmp / dp[u][2])
        dp[u][1] = dp[u][2] - (tmp % dp[u][2]);
        if (dp[u][1] == dp[u][2]) dp[u][1] = 0;
    } else {
        dp[u][1] -= val[u];
    }
}

void solve() {
    cin >> n;

    vis.assign(n, 0);
    dp.assign(n, vector<ll>(3, 0));
    adj.assign(n, vector<ll>());
    val.assign(n, 0);

    for (ll i = 1; i < n; i++) {
        ll u;
        cin >> u;
        u--;
        adj[u].push_back(i);
    }

    for (ll i = 0; i < n; i++) {
        cin >> val[i];
    }

    dfs(0); // Start DFS from root node
    cout << dp[0][0] << endl; // Maximum citizens caught by the bandit
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}