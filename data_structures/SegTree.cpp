struct SegmentTree {
  vector<ll> a;
  int n;
 
  SegmentTree(int _n) : a(2 * _n, 1e18), n(_n) {}
  
  void update(int pos, ll val) {
    for (a[pos += n] = val; pos > 1; pos >>= 1) {
      a[pos / 2] = min(a[pos], a[pos ^ 1]);
    }
  }
  
  ll get(int l, int r) {
    ll res = 1e18;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res = min(res, a[l++]);
      }
      if (r & 1) {
        res = min(res, a[--r]);
      }
    }
    return res;
  }
};

