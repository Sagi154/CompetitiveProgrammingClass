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
vector<int> seq;
vector<int> snake;

int bfs(int s) {
    dist.assign(n + 1, -1);
    seq.assign(n + 1, 0);
    queue<int> q;
    dist[s] = 0;
    seq[1] = snake[1];
    q.push(s);
    int count = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        if (graph[u].size() == 1 && seq[u] <= m && u != 1) {
            // If leaf and seq valid
            count++;
        } else {
            for (int v : graph[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (snake[v] == 1) {
                        seq[v] = seq[u] + 1;
                    }
                    else {
                        seq[v] = 0;
                    }
                    if (seq[v] <= m) {
                        q.push(v);
                    }
                }
            }
        }
    }
    return count;
}

void solve() {
    cin >> n >> m; // n num of vertices, m num of edges
    snake.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) { // Get Citizens count in each square
        cin >> snake[i]; // 1 if has snake and 0 otherwise
    }
    for (int i = 1; i < n; i++) { // Build graph from input with adjacency list
        int u, v; cin >> u >> v;
        graph[u].push_back(v); // add edge e = (u,v)
        graph[v].push_back(u); // add edge e = (v,u)
    }
    cout << bfs(1) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}