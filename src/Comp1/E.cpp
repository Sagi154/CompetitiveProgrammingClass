#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
vector<vector<int>> adj(MAX_N);
vector<vector<int>> comp(MAX_N);

int n, m, scc, dfsCounter;
int dfs_num[MAX_N], dfs_low[MAX_N], visited[MAX_N];
stack<int> st;

// Modified DFS
void tarjan(int u) {
    dfs_low[u] = dfs_num[u] = dfsCounter++;
    visited[u] = 1;
    st.push(u);
    for (int v : adj[u]) {
        if (dfs_num[v] == -1) tarjan(v);
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        scc++;
        while (st.size()) {
            int v = st.top(); st.pop();
            visited[v] = 0;
            comp[scc].push_back(v);
            if (v == u) break;
        }
    }
}

void dfs(int u) {
    visited[u] = 1;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v);
}

void solve(){
    return;
}


// main template
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 1;
    cin >> n;
    int costs[n] = {0};
    for (int i = 0; i < n; i++){
      cin >> costs[i];
      }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    memset(dfs_low, -1, sizeof dfs_low);
    memset(dfs_num, -1, sizeof dfs_num);
    for (int i = 1; i <= n; i++)
        if (dfs_num[i] == -1)
            tarjan(i);
    ll total_comps = 0;
    ll total_ways = 1;
    int min_comp_i = INF;
    int count_min_comp_i = 0;
    for (int i = 0; i < scc; i++){
        min_comp_i = INF;
        count_min_comp_i = 0;
        for (int j = 0; j < comp[i].size(); j++) {
            cout << "min_comp i " << min_comp_i << endl;
            min_comp_i = min(min_comp_i, costs[j]);
            cout << "in for comp" << endl;
            cout << costs[j] << "cost j" << endl;
        }
        for (int j = 0; j < comp[i].size(); j++) {
            count_min_comp_i += (costs[j] == min_comp_i);
        }
        cout << "in for gcc" << endl;

        total_comps += min_comp_i;
        total_ways *= count_min_comp_i;
      }
    cout << total_comps << endl;
    cout << total_ways << endl;

    return 0;
}