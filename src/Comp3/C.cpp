#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;


ll gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

bool str_contain(string s, string p) {
    if (s.length() % p.length() != 0) {
        return false;
    }
    string formed ="";
    for (int i = 0; i < s.length()/p.length(); i++) {
        formed += p;
    }
    return formed == s;
}

void solve(){
    string s1, s2;
    cin >> s1 >> s2;
    int len1 = s1.length(), len2 = s2.length();
    int gcd_len = gcd(len1, len2);
    int counter = 0;
    for (int i = 1; i <= gcd_len; i++) {
        if (gcd_len % i == 0) {
            string temp = s1.substr(0, i);
            if (str_contain(s1 , temp) && str_contain(s2 , temp)) {
                counter++;
            }
        }
    }
    cout << counter << endl;
}

// main template for T test cases
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}