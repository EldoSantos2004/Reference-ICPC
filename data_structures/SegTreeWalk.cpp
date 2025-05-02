/*
  Segment Tree Walk - Find First Position >= val
  ---------------------------------------------
  Indexing: 0-based
  Bounds: [0, n-1]
  Time Complexity:
    - build: O(n)
    - update(pos, val): O(log n)
    - get(L, R): O(log n) -> min value in [L, R]
    - query(L, R, val): O(log n) -> find first index in [L, R] where a[i] >= val

  Features:
    - Stores original value array in segment tree form
    - Maps original indices to tree positions for fast updates
    - Allows efficient walk to find constrained elements (e.g. lower bound >= val)
*/

struct SegmentTreeWalk {
  vector<ll> a;           // segment tree values
  vector<int> final_pos;  // maps index i to position in tree (leaf)
  int n;

  SegmentTreeWalk(int _n) : a(4 * _n, 1e18), final_pos(_n), n(_n) {}

  // Build segment tree from array `vals[0..n-1]`, start with node=1, l=0, r=n-1
  void build(int l, int r, int node, const vector<ll> &vals) {
    if (l == r) {
      final_pos[l] = node;
      a[node] = vals[l];
    } else {
      int mid = (l + r) / 2;
      build(l, mid, node * 2, vals);
      build(mid + 1, r, node * 2 + 1, vals);
      a[node] = min(a[node * 2], a[node * 2 + 1]);
    }
  }

  // Update value at original index `pos` to `val`
  void update(int pos, ll val) {
    pos = final_pos[pos]; // leaf position
    a[pos] = val;
    for (pos /= 2; pos > 0; pos /= 2)
      a[pos] = min(a[pos * 2], a[pos * 2 + 1]);
  }

  // Get min value in [L, R], with current node interval [l, r] and root `node`
  ll get(int l, int r, int L, int R, int node) {
    if (L > R) return 1e18;
    if (l == L && r == R) return a[node];
    int mid = (l + r) / 2;
    return min(
      get(l, mid, L, min(R, mid), node * 2),
      get(mid + 1, r, max(L, mid + 1), R, node * 2 + 1)
    );
  }

  // Find first position in [L, R] with a[i] >= val, starting from node interval [l, r]
  pair<ll, ll> query(int l, int r, int L, int R, int node, int val) {
    if (l > R || r < L) return {-1, 0};            // out of query bounds
    if (a[node] < val) return {-1, 0};             // all values < val
    if (l == r) return {a[node], l};               // leaf node that satisfies

    int mid = (l + r) / 2;
    auto left = query(l, mid, L, R, node * 2, val);
    if (left.first != -1) return left;
    return query(mid + 1, r, L, R, node * 2 + 1, val);
  }
};
// Example usage:
int n = 8;
vector<ll> vals = {4, 2, 7, 1, 9, 5, 6, 3};
SegmentTreeWalk st(n);
st.build(0, n - 1, 1, vals);
