#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
void solve(){
    int n, h;
    cin >> n >> h;
    vector<ll> a;
    a.assign(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int hard_min = max(1, (h / n) + 1);
    ll left = 0;
    ll mid = 0;
    ll right = h - 1;
    while (left < right - 1) {
        mid = left + (right - left) / 2;
        ll sum = 0;
        for(int i = 1; i < n; i++) {
            sum += min(a[i] - a[i-1], mid);
        }
        // if (sum == h) {
        //     cout << "breaked" << endl;
        //     break;
        // }
        if (sum <= h) {
            left = mid;
        }
        else {
            right = mid;
        }

    }
    ll sum1 = 0, sum2 = 0;
    for(int i = 1; i < n; i++) {
        sum1 += min(a[i] - a[i-1], left);
    }
    for(int i = 1; i < n; i++) {
        sum2 += min(a[i] - a[i-1], right);
    }
    cout << right << endl;
    cout << left << endl;
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