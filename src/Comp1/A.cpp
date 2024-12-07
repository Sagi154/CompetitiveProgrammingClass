#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;
typedef long long ll;
const int MAXN = 100000; // Maximum size
string test = "Yes";

void solve(){
    string s;
    cin >> s;
    if (test.find(s) != std::string::npos)
      cout << "Yes" << endl;
    else
      cout << "No" << endl;
  }

// main template
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 0; i < 50; i++){
       test += "Yes";
    }
    while (T--){
        solve();
    }
    return 0;
}