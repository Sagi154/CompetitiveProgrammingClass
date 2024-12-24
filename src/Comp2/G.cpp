#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int n, k;
void solve(){
  cin >> n;
  cin >> k;
  vector<int> g;
  g.assign(n, 0);
  for(int i = 0; i < n; i++){
    int temp;
    cin >> temp;
    g[i] = temp * (-1);
  }
  vector<int> copy = g;
  priority_queue<pair<int, int>> maxHeap;
  for (int i = 0; i < n; i++){
    maxHeap.push(make_pair(g[i], i));
  }
  for(int i = 1; i <= k; i++){
    pair<int, int> p = maxHeap.top();
    maxHeap.pop();
    int key = p.first;
    key--;
    int index = p.second;
    g[index] = key;
    maxHeap.push(make_pair(g[index], index));
  }
  for(int i = 0; i < n; i++){
    g[i] = g[i] * (-1);
  }

  ll sum = 0;
  for(int i = 0; i <= n-2; i++){
    for(int j = i+1; j <= n-1; j++){
        sum += (g[i] * g[j]) % MOD;
        sum = sum % MOD;
    }
  }
  cout << sum % MOD << endl;
}

// main template for T test cases
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--){
        solve();
    }
    return 0;
}