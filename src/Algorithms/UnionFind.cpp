#include <vector>
#include <numeric>
using namespace std;

/**
 * @brief Disjoint Set Union (Union-Find) data structure.
 */
struct dsu {
    vector<int> parent; // Parent array to represent sets.
    vector<int> size_;  // Size array to keep track of the size of each set.

    /**
     * @brief Constructor to initialize DSU for n elements.
     *
     * @param n The number of elements in the DSU.
     */
    dsu(int n) {
        // Initialize each element to be its own parent.
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);

        // Initialize the size of each set to 1.
        size_.resize(n, 1);
    }

    /**
     * @brief Find the representative (root) of the set containing x.
     *        Implements path compression to optimize future queries.
     *
     * @param x The element whose set representative is to be found.
     * @return int The representative of the set.
     */
    int find_(int x) {
        // Path compression: Make the parent of x point to its root.
        return x == parent[x] ? x : parent[x] = find_(parent[x]);
    }

    /**
     * @brief Union two sets containing elements x and y.
     *        Uses union by size to keep the tree shallow.
     *
     * @param x An element in the first set.
     * @param y An element in the second set.
     * @return bool Returns true if the sets were merged, false if they were already in the same set.
     */
    bool union_(int x, int y) {
        int X = find_(x); // Find the root of the set containing x.
        int Y = find_(y); // Find the root of the set containing y.

        // If both elements are already in the same set, no union is performed.
        if (X == Y) {
            return false;
        }

        // Union by size: Attach the smaller tree under the larger tree.
        if (size_[X] < size_[Y]) {
            swap(X, Y);
        }

        // Update the parent and size.
        parent[Y] = X;
        size_[X] += size_[Y];
        return true;
    }
};