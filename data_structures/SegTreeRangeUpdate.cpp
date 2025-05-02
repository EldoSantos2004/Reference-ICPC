/*
  Segment Tree (Range Min Update, Point Query)
  --------------------------------------------
  Indexing: 0-based
  Bounds: [0, n-1]
  Time Complexity:
    - update(l, r, val): O(log n) -> applies min(val) over [l, r)
    - get(pos): O(log n) -> minimum affecting position pos
  Space Complexity: O(2n)
*/

struct SegmentTree {
  vector<ll> a; // a[i] = min value affecting segment i
  int n;

  SegmentTree(int _n) : a(2 * _n, 1e18), n(_n) {}

  // Get the effective minimum at position `pos`
  ll get(int pos) {
    ll res = 1e18;
    for (pos += n; pos > 0; pos >>= 1) {
      res = min(res, a[pos]);
    }
    return res;
  }

  // Apply min(val) to all positions in [l, r)
  void update(int l, int r, ll val) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        a[l] = min(a[l], val);
        l++;
      }
      if (r & 1) {
        --r;
        a[r] = min(a[r], val);
      }
    }
  }
};
