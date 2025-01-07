#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int INF = 2e9; // Infinity value for initialization.

class SegmentTree {
    int n, h;                 // Size of the array and height of the segment tree.
    vector<int> t, d;         // t: segment tree, d: lazy propagation array.

public:
    /**
     * @brief Constructor to initialize the Segment Tree.
     *
     * @param size The size of the input array.
     */
    SegmentTree(int size) {
        n = size;
        h = sizeof(int) * 8 - __builtin_clz(n); // Calculate the height of the segment tree.
        t.assign(2 * n, 0);                    // Segment tree array.
        d.assign(n, 0);                        // Lazy propagation array.
    }

    /**
     * @brief Applies a value to a node in the segment tree.
     *
     * @param p The position of the node in the segment tree.
     * @param value The value to apply.
     */
    void apply(int p, int value) {
        t[p] += value;
        if (p < n) d[p] += value; // Mark lazy value for non-leaf nodes.
    }

    /**
     * @brief Rebuilds the tree upwards from a given position.
     *
     * @param p The position to rebuild from.
     */
    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = max(t[p << 1], t[p << 1 | 1]) + d[p];
        }
    }

    /**
     * @brief Pushes lazy updates from root to leaves.
     *
     * @param p The position to push updates from.
     */
    void push(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i << 1, d[i]);      // Apply lazy value to left child.
                apply(i << 1 | 1, d[i]); // Apply lazy value to right child.
                d[i] = 0;                // Clear lazy value at the current node.
            }
        }
    }

    /**
     * @brief Increment values in a range [l, r) by a specified value.
     *
     * @param l The left boundary of the range (inclusive).
     * @param r The right boundary of the range (exclusive).
     * @param value The value to increment.
     */
    void inc(int l, int r, int value) {
        l += n; r += n;
        int l0 = l, r0 = r;

        // Apply the increment to the range [l, r).
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }

        build(l0);        // Rebuild the left boundary.
        build(r0 - 1);    // Rebuild the right boundary.
    }

    /**
     * @brief Query the maximum value in a range [l, r).
     *
     * @param l The left boundary of the range (inclusive).
     * @param r The right boundary of the range (exclusive).
     * @return int The maximum value in the range.
     */
    int query(int l, int r) {
        l += n; r += n;
        push(l);          // Push updates for the left boundary.
        push(r - 1);      // Push updates for the right boundary.
        int res = -INF;

        // Traverse the range [l, r).
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(t[--r], res);
        }

        return res;
    }
};

int main() {
    int size = 10; // Example size of the input array.
    SegmentTree seg(size);

    // Example operations:
    seg.inc(2, 5, 3);        // Increment range [2, 5) by 3.
    seg.inc(4, 9, 2);        // Increment range [4, 9) by 2.
    cout << seg.query(1, 6); // Query the maximum in range [1, 6).
    return 0;
}