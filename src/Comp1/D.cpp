
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size

void solve(){
  int n;
  cin >> n;
  int arr[n] = {0};
  for(int i=0;i<n;i++){
    cin >> arr[i];
  }
    // cout << "len is: " << n << endl;
  ll switched[n] = {0};
  ll same[n] = {0};
  same[1] = arr[0] + arr[1];
  switched[1] = ((-1) * arr[0]) - arr[1];
  for(int k = 2; k < n; k++){
    // cout << "k is " << k << endl;
    same[k] = max(same[k-1] + arr[k], switched[k-1] + arr[k]);
    switched[k] = max(switched[k-1] + (2 * arr[k-1]) - arr[k], same[k-1] - (2 * arr[k-1]) - arr[k]);
    // cout << "same[k]: " << same[k] << endl;
    // cout << "switched[k]: " << switched[k] << endl;
  }
  cout << max(switched[n-1], same[n-1]) << endl;
    return;
}


// main template
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    while (T--){
        // cout << "Case: " << T << "\n" << endl;
        solve();
    }
    return 0;
}