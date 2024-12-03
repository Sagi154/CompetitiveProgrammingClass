#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size

/* ------- BFS --------- */
class BFS {
    vector<vector<int>> g;
    vector<bool> visible;
    void bfs(vector<int>& starts){
        for(int x : starts)
            visible[x]=true;
        vector<int> cur_level=starts;
        int dist=0;
        while (!cur_level.empty()) {
            vector<int> next_level;
            for(int f : cur_level) {
                for(int s : g[f]) {
                    if (visible[s]) continue;
                    visible[s]=true;
                    next_level.push_back(s);
                }
            }
            cur_level = next_level;
            dist++;
        }
    }
};

/* ------- DFS --------- */
class DFS {
    vector<vector<int>> g;
    vector<bool> visible;
    void dfs(int cur) {
        visible[cur] = true;
        for(int s : g[cur]) {
            if(visible[s]) continue;
            dfs(s);
        }
    }
};

/* ------- Tarjan --------- */
// Algorithm for finding strongly connected components
class Tarjan {

    vector<int> g[MAXN];
    int d[MAXN], low[MAXN], scc[MAXN];
    bool stacked[MAXN];
    stack<int> s;
    int ticks,current_scc;
    void tarjan(int u) {
        d[u]=low[u] = ticks++;
        s.push(u);
        stacked[u] = true;
        const vector<int> &out = g[u];
        for(int k = 0, m = out.size();k < m;++k) {
            const int &v = out[k];
            if( d[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (stacked[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        if (d[u] == low[u]) {
            int v;
            do {
                v = s.top();
                s.pop();
                stacked[v] = false;
                scc[v] = current_scc;
            } while(u != v);
            current_scc++;
        }
    }

};


void solve(){
  return;
  }

int N = 5;
vector<int> vect(N); // Creating vector of size N

// main template
int main3() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  cin >> T;
  while (T--){
    solve();
    }
  return 0;
  }