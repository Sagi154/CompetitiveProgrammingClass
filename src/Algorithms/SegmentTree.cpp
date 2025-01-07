#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1e5;  // Maximum size for the array
int n;  // Array size
int t[2 * MAX_N];  // Segment tree array

// Build the segment tree
void build() {
    // Initialize the tree with the values
    for (int i = 0; i < n; ++i) {
        cin >> t[n + i];  // The leaf nodes are the elements of the array
    }
    // Build the segment tree by calculating internal nodes
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i * 2] + t[i * 2 + 1];  // Internal node is the sum of its children
    }
}

// Modify the value at position p (update)
void modify(int p, int value) {
    // Move to the leaf node corresponding to the position p
    p += n;
    t[p] = value;  // Set the new value at the leaf node
    // Update the segment tree by propagating the changes upwards
    for (p /= 2; p > 0; p /= 2) {
        t[p] = t[2 * p] + t[2 * p + 1];  // Internal node is the sum of its children
    }
}

// Query the sum in the range [l, r)
int query(int l, int r) {
    int res = 0;
    // Move to the leaf nodes corresponding to positions l and r
    l += n;
    r += n;
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
    return res;  // Return the sum of the range [l, r)
}