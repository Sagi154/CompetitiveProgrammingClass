#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
string colors;

int n, m, visited[MAX_N];
vector<int> adj[MAX_N];
vector<pair<int, int>> color_count[MAX_N];
int counter;

pair<int, int> dfs(int u) {
    visited[u] = 1;
    int white_count = 0, black_count = 0;

    white_count += colors[u-1] == 'W';
    black_count += colors[u-1] == 'B';

        if (adj[u].size() == 0 ) {
            return make_pair(white_count, black_count);
        }

    for (int v : adj[u]) {
        pair<int, int> curr_count = dfs(v);
        white_count += curr_count.first;
        black_count += curr_count.second;
    }

    counter += black_count == white_count;
    visited[u] = 2;
    return make_pair(white_count, black_count);
}


void solve(){
    // int visited[MAX_N];
    // vector<int> adj[MAX_N];
    // vector<pair<int, int>> color_count[MAX_N];
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    adj->clear();
    fill(visited, visited + MAX_N, 0);
    color_count->clear();
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int u; cin >> u;
        adj[u].push_back(i);
    }
    // get str from input
    cin >> colors;
    pair <int, int> curr_color = dfs(1);
    cout << counter << endl;
}

// main template for T test cases
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--){
        counter = 0;
        solve();
    }
    return 0;
}