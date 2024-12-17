#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

vector<int> graph[MAX_N], topo;
int n, visited[MAX_N];

void dfs(int u) {
    visited[u] = 1;
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v);
        else if (visited[v] == 1) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    visited[u] = 2;
    topo.push_back(u);
}

void topo_sort() {
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);
    reverse(topo.begin(), topo.end());
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int v; cin >> v;
        graph[v].push_back(i); // Create an edge from square p_i to square i
    }
    vector<int> citizens(n + 1);
    for (int i = 1; i <= n; i++) { // Get Citizens count in each square
        cin >> citizens[i];
    }
    topo_sort();
    // Perform a topological sort
    vector<tuple<int, int, int, int>> vals(n + 1); // Each element in the array is C_i, D_i, N_i, L_i
    fill(vals.begin(), vals.end(), make_tuple(0, 0, 0, 0));
    for (int k = n - 1; k >= 0; k--) {
        // Go over the topological sort from the end to start
        int i = topo[k];
        cout << "Node " << i << endl;
        if (graph[i].empty()) {
            // Node i is leaf
            int n_i = 0;
            int d_i = 0;
            int c_i = citizens[i];
            int l_i = 1;
            vals[i] = make_tuple(c_i, d_i, n_i, l_i);
        }
        else { // Node i is not a leaf
            int max_c = 0;
            int n_i = 0;
            int l_i = 0;
            int c_i = 0;
            int d_i = 0;
            for (auto v : graph[i]) {
                // Get maximum of c_j values of i's neighbors
                n_i++; // Neighbors count
                max_c = max(max_c, citizens[v]);
            }
            c_i = max_c;
            cout << "max c is: " << max_c << endl;
            int citizens_i = citizens[i]; // number of citizens currently in square i
            for (auto j : graph[i]) { // Pad each square j with people from i without having to change c_j
                cout << "Neighbor: " << j << endl;
                auto [c_j, d_j, n_j, l_j] = vals[j];
                l_i += l_j; // Number of leaves accessible from i as root of subtree
                if (d_j > 0 && citizens_i != 0) {
                    if (citizens_i <= d_j) {
                        citizens[i] = 0; // Push out citizens from i
                        d_j -= citizens_i; // Pad square reachable from j with temp number of citizens
                        vals[j] = make_tuple(c_j, d_j, n_j, l_j);
                    }
                    else {
                        citizens[i] -= d_j;
                        d_j = 0; // Fully padded squares reachable from j
                        vals[j] = make_tuple(c_j, d_j, n_j, l_j);
                    }
                }
            }
            /* Reached here when fully padded all js without having to change their c_j
             * c_js are not necessarily equal
             * Go over each j and pad to match curr c_i
             */
            cout << "Leaves accessible: " << l_i << endl;
            if (citizens_i != 0) {
                // Fully padded all neighbors and there are still citizens in i ****
                /* The code below matches the case where all c_js match and there are still citizens
                 *
                 */
                int add_each = citizens_i / l_i; // To each neighbor add the same number of citizens from square i
                int deficit = citizens_i % l_i;
                c_i += add_each;
                if (deficit != 0) {
                    c_i++;
                    d_i += (l_i - deficit);
                }
                c_i += (deficit > 0);
                vals[i] = make_tuple(c_i, d_i, n_i, l_i);
            }
            else {
                // Pushed out all citizens from i
                // Calculate d_i
                for (auto j : graph[i]) {
                    auto [c_j, d_j, n_j, l_j] = vals[j];
                    int diff = c_i - c_j;
                    d_i += d_j; // Can pad leaves of j with d_j citizens so all of them are equal to c_j
                    d_i += diff * l_i; // can pad all leaves of j to match c_i

                    // d_i += diff;
                    // if (d_j > 0) { // Checks if neighbor j is not a leaf or a square with no room to pad
                    //     d_i += d_j + ((n_j - 1) * diff);
                    // }
                }
                vals[i] = make_tuple(c_i, d_i, n_i, l_i);
            }
        }
    }
    // Finished going over the topological sort, so we have the results at vals[1]
    auto [c_1, d_1, n_1, l_1] = vals[1];
    cout << c_1 << endl;
}

