struct SegmentTreeWalk {
  vector<ll> a, final_pos;
  int n;
 
  SegmentTreeWalk(int _n) : a(4 * _n, 1e18), final_pos(_n), n(_n) {}
  
  // l = 0, r = n - 1
  void build(int l, int r, int node, const vector<ll> &vals) {
    if (l == r){
      final_pos[l] = node;
      a[node] = vals[l];
    }
    else {
      int mid = (l + r) / 2;
      build(l, mid, node * 2, vals);
      build(mid + 1, r, node * 2 + 1, vals);
      a[node] = min(a[node * 2], a[node * 2 + 1]);
    }
  }

  void update(int pos, ll val){
    pos = final_pos[pos];
    a[pos] = val;
    pos /= 2;
    while(pos){
      a[pos] = min(a[2 * pos], a[2 * pos + 1]);
      pos /= 2;
    }
  }
  
  //inclusive
  ll get(int l, int r, int L, int R, int node) {
    if (L > R) 
      return 1e18;
    if (l == L && r == R) {
      return a[node];
    }
    int mid = (l + r) / 2;
    return min(get(l, mid, L, min(R, mid), 2 * node), get(mid + 1, r, max(L, mid + 1), R, 2 * node + 1));
  }
  
  // l = 0, r = n - 1, L = query start, R = query end
  // you can just do ll if you only care about value and not index or no update
  pair<ll, ll> query(int l, int r, int L, int R, int node, int val){
    //cout << l << " " << r << endl;
    if(l > R || r < L) return {-1, 0};
    if(a[node] < val) return {-1, 0};
    if(l == r){
      // depending on what you want to do
      return {a[node], l};
    }
    
    int mid = (l + r) / 2;
    auto left = query(l, mid, L, R, 2 * node, val);
    if(left.first != -1) return left;
    auto right = query(mid + 1, r, L, R, 2 * node + 1, val);
    return right;
  }
};
