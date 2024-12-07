#include <iostream>
#include <vector>
#include <bits/stdc++.h>

/***
 * Algorithm: We run a BFS like algorithm
 * We start a simulated BFS run from vertex 1 for player 1 and from vertex n for player 2.
 * We go over each possible pair of vertices that represents a legal move for both players.
 * as in player 1 can move to the next level ( of the BFS run) to a node with X color
 * if player 2 can move to the next level to a node with Y color.
 * We consider the next level to be any possible legal move (even "backwards")
 * We run in a BFS like manner to achieve the goal of getting the least moves.
 * Time complexity : O(n + m)
 * Memory complexity : O(n + m)
 */

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int n, m;
vector<int> results;

void solve(){
    cin >> n >> m; // n num of vertices, m num of edges
    vector<int> color(n + 1);
    for(int i = 1; i <= n; i++) { // get colors from input
        cin >> color[i];
    }
    vector<int> graph[n + 1];
    for (int i = 0; i < m; i++) { // Build graph from input with adjacency list
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v); // add edge e = (u,v)
        graph[v].push_back(u); // add edge e = (v,u)
    }
    if (color[1] == color[n]) { // check for case that player 1 and 2 are on the same color on start
        results.push_back(-1) ;
        return;
    }
    queue<tuple<int, int, int>> q; // Each element in the queue represents (player 1 position, player 2 position, number of moves to reach that state)
    vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false)); // A 2D boolean array to mark for every possible pair of vertices if the players can visit them together
    visited[1][n] = true;
    q.push({1, n, 0}); // Initial state
    bool flag = false;
    while (q.size()) {
        auto [p1, p2, moves] = q.front();
        if (p1 == n && p2 == 1 ) { // Reached target
            results.push_back(moves);
            flag = true;
            break;
        }
        // Check for any pair of possible moves that it's a legal move and wasn't seen before
        for (int p1_neighbor: graph[p1]) {
            for (int p2_neighbor: graph[p2]) {
                if (!visited[p1_neighbor][p2_neighbor] && (color[p1_neighbor] != color[p2_neighbor])) { // Check for legal move
                    visited[p1_neighbor][p2_neighbor] = true;
                    q.push({p1_neighbor, p2_neighbor, moves + 1});
                }
            }
        }
        q.pop();
    }

    if (!flag)
            results.push_back(-1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
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
