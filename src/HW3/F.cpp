#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int t[4 * MAX_N]; // Segment tree array
int d[4 * MAX_N]; // Lazy propagation array
int a[MAX_N]; // Input array
int n; // Size of the input array
int h; // Height of the tree

void build2(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else { 
        int tm = (tl + tr) / 2;
        build2(a, v*2, tl, tm);
        build2(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void apply(int p, int value) {
    t[p] += value;
    if (p < n) d[p] += value;
}

void push(int p) {
    for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i]) {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
    }
}

void build(int p) {
    while (p > 1) {
        p >>= 1;
        t[p] = t[p<<1] + t[p<<1|1];
    }
}

void inc(int l, int r) {
    l += n; r += n;
    int l0 = l, r0 = r;
    push(l); push(r-1);
    
    vector<pair<int,int>> updates;
    int value = 1;
    
    // Store updates in correct order
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) updates.push_back({l++, value++});
        if (r&1) updates.push_back({--r, value++});
    }
    
    // Apply in sequence
    sort(updates.begin(), updates.end());
    for (auto [pos, val] : updates) {
        apply(pos, val);
    }
    
    build(l0);
    build(r0-1);
}

int query(int l, int r) {
    int res = 0;
    // Move to the leaf nodes corresponding to positions l and r
    l += n;
    r += n;
    push(l);
    push(r - 1);
    while (l < r) {
        if (l % 2 == 1) {
            res += t[l];  // If l is odd, add the value at t[l] to the result
            l++;  // Move to the next node
        }
        if (r % 2 == 1) {
            r--;  // Move to the previous node
            res += t[r];  // Add the value at t[r] to the result
        }
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    h = sizeof(int) * 8 - __builtin_clz(n);

    build2(a, 1, 0, n-1);
    int quer, l, r;

    for (int i = 0 ; i < q ; i++) {
        cin >> quer >> l >> r;
        if (quer == 1){
            inc(l-1, r); // Call inc without the value parameter
        }
        else{
            cout << query(l-1, r) << endl;
        }
    }
    return 0;
}