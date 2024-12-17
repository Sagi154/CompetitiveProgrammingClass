#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> graph[n + 1];
    vector<int> leaves[n + 1]; // Accisible leaves for every node
    for (int i = 2; i <= n; i++) {
        int v; cin >> v;
        graph[v].push_back(i); // Create an edge from square p_i to square i
    }
    vector<int> citizens(n + 1);
    for (int i = 1; i <= n; i++) { // Get Citizens count in each square
        cin >> citizens[i];
    }

    // Perform a topological sort
    vector<int> topo(n + 1);
    for (int k = n; k >= 1; k--) {
        int i = topo[k];
        if (graph[i].empty()) {
            // Node i is leaf
            leaves[i].push_back(i);
        }
        else {
            // Node is not leaf
            for (int j : graph[i]) {
                leaves[i].insert(leaves[i].end(), leaves[j].begin(), leaves[j].end());
            }
        }








    }