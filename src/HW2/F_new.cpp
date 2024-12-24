#include <bits/stdc++.h>

/***
 * Algorithm: We use a topological sort followed by a dynamic programming approach
 * to compute the maximum number of citizens the bandit can catch if both sides act optimally.
 * The idea is to distribute the citizens optimally among all reachable leaves
 * from the root so we can minimize the maximum number of citizens the bandit can catch.
 * First, we perform a topological sort of the tree using DFS.
 * This ensures we process the nodes in bottom-up order, starting from the leaves.
 * Then, we go over each node in reverse topological order.
 * For each node u:
 *   - Compute the maximum citizens (C_v) among all children of u.
 *   - Calculate the total deficit (D_v) needed to balance citizens across all children.
 *   - Distribute remaining citizens at u to minimize their capture by the bandit.
 *   - Update the DP values for the node (C_v, D_v, N_v, L_v).
 * Lastly, output the maximum citizens (C_1) the bandit can catch when starting from the root.
 * Definitions:
 * - C_v: Maximum number of citizens the bandit can catch on subtree with node v as root.
 * - D_v: Remaining citizens required to balance all children of node v to match C_v.
 * - N_v: Number of direct neighbors (children) of node v.
 * - L_v: Total number of leaf nodes in the subtree rooted at node v.
 * Time complexity: O(n) — We go over each node and edge exactly once.
 * Space complexity: O(n) — For storing the graph, citizens, and needed values.
 */

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

vector<int> graph[MAX_N], topo;
int n, visited[MAX_N];

void dfs(int u) {
    visited[u] = 1;
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v);
        else if (visited[v] == 1) {
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
        int v;
        cin >> v;
        graph[v].push_back(i); // Create an edge from square p_i to square i
    }
    vector<ll> citizens(n + 1);
    ll sum_citizens = 0;
    for (int i = 1; i <= n; i++) { // Get Citizens count in each square
        cin >> citizens[i];
        sum_citizens += citizens[i];
    }
    topo_sort();
    // Perform a topological sort
    vector<tuple<ll, ll, ll, ll>> vals(n + 1); // Each element in the array is C_v, D_v, N_v, L_v
    fill(vals.begin(), vals.end(), make_tuple(0, 0, 0, 0));
    // Go over the topological sort in reverse order
    for (int k = n - 1; k >= 0; k--) {
        int u = topo[k];

        if (graph[u].empty()) {
            // Leaf node means all citizens are caught here (those losers)
            vals[u] = make_tuple(citizens[u], 0, 0, 1);
            continue;
        }

        ll tmp_max = -1; // Maximum citizens in a leaf among children
        ll total_leaves = 0; // Total leaves in the current subtree
        ll deficit = 0; // Total deficit for balancing citizens

        for (int v : graph[u]) { // Go over the node children and calculate max citizens and total leaves
            auto [c_v, d_v, n_v, l_v] = vals[v];
            tmp_max = max(tmp_max, c_v);
            total_leaves += l_v;
        }

        ll max_c = tmp_max;
        // Calculate the total deficit needed to balance pad children to max_c
        for (int v : graph[u]) {
            auto [c_v, d_v, n_v, l_v] = vals[v];
            if (c_v < max_c) {
                deficit += d_v + l_v * (max_c - c_v);
            } else {
                deficit += d_v;
            }
        }

        ll remaining_citizens = citizens[u];
        // In case padded entirely yet exceeded the deficit, max_c should increase
        if (remaining_citizens > deficit) {
            ll extra = remaining_citizens - deficit;
            max_c += (extra + total_leaves - 1) / total_leaves; // Equivalent to ceil(extra / total_leaves)
            deficit = total_leaves - (extra % total_leaves);
            if (deficit == total_leaves) deficit = 0;
        } else {
            // Use citizens to reduce the deficit
            deficit -= remaining_citizens;
        }

        vals[u] = make_tuple(max_c, deficit, graph[u].size(), total_leaves);
    }

    // Finished going over the topological sort, so we have the results at vals[1]
    auto [c_1, d_1, n_1, l_1] = vals[1];
    cout << c_1 << endl;
}

