#include <algorithm>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <limits>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size
float inf_f = std::numeric_limits<float>::infinity();

vector<int> results;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> color;
    for(int i = 0; i < n; i++) {
      cin >> color[i];
    }
    vector<int> graph[n];
    cout << "n and m are: " << n << " " << m << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int player_1_start = 1, player_2_start = n;
    if (color[player_1_start] == color[player_2_start]) {
        results.push_back(-1) ;
        return;
    }
    vector<int> d_player1;
    vector<int> d_player2;
    queue<int> q_player1;                // Queue for BFS
    queue<int> q_player2;                // Queue for BFS
    vector<int> player1_blues;
    vector<int> player1_reds;
    vector<int> player2_blues;
    vector<int> player2_reds;
    for (int i = 0; i < n; i++) {
        d_player1[i] = inf_f;
        d_player2[i] = inf_f;
    }
    d_player1[player_1_start] = 0;
    d_player2[player_2_start] = 0;
    q_player1.push(player_1_start);
    q_player2.push(player_2_start);
    // Finished initialization
    int min_moves = -1;
    while ((!q_player1.empty() && !q_player2.empty())) { // if one empty then fuck off
        int node1 = q_player1.front();
        int node2 = q_player2.front();
        // Visit all unvisited neighbors
        for (int neighbor : graph[node1]) {
            if (color[neighbor] == 0) // red color
                player1_reds[d_player1[node1] + 1] = 1;
            else
                player1_blues[d_player1[node1] + 1] = 1;
        }
        for (int neighbor : graph[node2]) {
            if (color[neighbor] == 0) // red color
                player2_reds[d_player2[node2] + 1] = 1;
            else
                player2_blues[d_player2[node2] + 1] = 1;
        }
        for (int neighbor : graph[node1]) {
            if ((color[neighbor] == 0 && player2_blues[d_player1[node1] + 1] == 1) || (color[neighbor] == 1 && player2_reds[d_player1[node1] + 1] == 1)){
                d_player1[neighbor] = d_player1[node1] + 1;
                q_player1.push(neighbor);
            }
        }
        for (int neighbor : graph[node2]) {
            if ((color[neighbor] == 0 && player1_blues[d_player2[node2] + 1] == 1) || (color[neighbor] == 1 && player1_reds[d_player2[node2] + 1] == 1)){
                d_player2[neighbor] = d_player2[node2] + 1;
                q_player2.push(neighbor);
            }
        }
        q_player1.pop();
        q_player2.pop();
        if (d_player1[player_2_start - 1] == d_player2[player_1_start - 1]){
            min_moves = d_player1[player_2_start - 1];
            break;
        }
    }
    results.push_back(min_moves); ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    while (T--){
        solve();
    }
    for (int result : results) {
        cout << result << endl;
    }
    return 0;
}