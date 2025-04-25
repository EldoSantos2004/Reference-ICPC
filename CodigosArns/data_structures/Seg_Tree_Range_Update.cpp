struct SegmentTree {
  vector<ll> a;
  int n;
 
  SegmentTree(int _n) : a(2 * _n, 1e18), n(_n) {}
  

  ll get(int pos) {
    ll res = 1e18;
    for (pos += n; pos; pos >>= 1) {
      res = min(res, a[pos]);
    }
    return res;
  }
  
  void update(int l, int r, ll val) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        a[l] = min(a[l], val);
        l++;
      }
      if (r & 1) {
        r--;
        a[r] = min(a[r], val);
      }
    }
  }
};
