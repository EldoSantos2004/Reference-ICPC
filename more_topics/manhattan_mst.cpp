/*
  Manhattan MST Edge Generation
  -----------------------------
  Given n points ps[0..n-1], returns a list of candidate edges
    (weight, u, v) for the Manhattan MST, where
    weight = |x[u]-x[v]| + |y[u]-y[v]|.
  Indexing: 0-based for points and returned edges
  Time Complexity: O(n log n)
*/
struct Point {
  ll x, y;
};

vector<tuple<ll,int,int>> manhattan_mst_edges(vector<Point> ps) {
  int n = ps.size();
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  vector<tuple<ll,int,int>> edges;
  edges.reserve(n * 4);
  // Repeat for 4 orientations
  for (int r = 0; r < 4; r++) {
    // Sort by x+y ascending
    sort(order.begin(), order.end(), [&](int i, int j) {
      return ps[i].x + ps[i].y < ps[j].x + ps[j].y;
    });
    // Active map: key = x-coordinate, value = point index
    map<ll,int,greater<ll>> active;
    for (int i : order) {
      // For all active points with x >= ps[i].x
      for (auto it = active.lower_bound(ps[i].x); it != active.end(); active.erase(it++)) {
        int j = it->second;
        if (ps[i].x - ps[i].y > ps[j].x - ps[j].y) break;
        assert(ps[i].x >= ps[j].x && ps[i].y >= ps[j].y);
        edges.emplace_back({(ps[i].x - ps[j].x) + (ps[i].y - ps[j].y), i, j});
      }
      active[ps[i].x] = i;
    }
    // Rotate points 90 degrees: (x,y) -> (y,-x)
    for (auto &p : ps) {
      ll tx = p.x;
      p.x = p.y;
      p.y = -tx;
    }
  }
  return edges;
}
