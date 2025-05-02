/*
  Merge Sort Tree (Segment Tree of Sorted Arrays)
  -----------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity:
    - build(): O(n log n)
    - q(l, r, x): O(log^2 n) -> number of elements <= x in [l, r)
  Space Complexity: O(n log n)

  Features:
    - Supports frequency/count queries: "how many values <= x in range [l, r)?"
    - Static array (no point updates unless rebuilt)
*/

const int MAXN = 100005;        // size of original array
const int MAXT = 2 * MAXN;      // size of segment tree (2n)

vector<int> t[MAXT];    // Segment tree: each node holds sorted vector
int a[MAXN];            // Original array
int n;                  // Size of array

// Build merge sort tree (bottom-up)
void build() {
  // Fill leaves
  for (int i = 0; i < n; i++) {
    t[i + n].push_back(a[i]);
  }

  // Merge children into parent
  for (int i = n - 1; i > 0; i--) {
    auto &left = t[2 * i], &right = t[2 * i + 1];
    merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(t[i]));
  }
}

// Query how many elements <= `x` in range [l, r)
int q(int l, int r, int x) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      res += upper_bound(t[l].begin(), t[l].end(), x) - t[l].begin();
      l++;
    }
    if (r & 1) {
      r--;
      res += upper_bound(t[r].begin(), t[r].end(), x) - t[r].begin();
    }
  }
  return res;
}
// Read n and array a, then call build()
