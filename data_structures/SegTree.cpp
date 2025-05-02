/*
  Segment Tree (Iterative, Range Minimum Query)
  ---------------------------------------------
  Indexing: 0-based
  Bounds: [0, n-1] inclusive
  Time Complexity:
    - update(pos, val): O(log n)
    - get(l, r): O(log n) -> query min in range [l, r)
  Space Complexity: O(2n)
*/
struct SegmentTree {
  vector<ll> a; // segment tree array
  int n;        // number of elements in original array

  SegmentTree(int _n) : a(2 * _n, 1e18), n(_n) {}
  // Update position `pos` to value `val`
  void update(int pos, ll val) {
    pos += n;      // move to leaf
    a[pos] = val;  // set value
    for (pos /= 2; pos > 0; pos /= 2) {
      a[pos] = min(a[2 * pos], a[2 * pos + 1]); // update parent
    }
  }
  // Get minimum value in range [l, r)
  ll get(int l, int r) {
    ll res = 1e18;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = min(res, a[l++]); // if l is right child
      if (r & 1) res = min(res, a[--r]); // if r is left child
    }
    return res;
  }
};
