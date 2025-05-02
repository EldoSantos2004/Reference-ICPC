/*
  Offline Dynamic Connectivity — Segment Tree + Rollback DSU
  -----------------------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1]

  Features:
    - Handles dynamic edge insertions and deletions over time
    - Answers queries of type: "how many connected components at time t?"
    - All operations are processed offline

  Components:
    - DSU with rollback (stores a stack of previous states)
    - Segment tree over time to store active edge intervals
*/

// Rollbackable Disjoint Set Union (Union-Find)
struct DSU {
  vector<int> e; // e[x] < 0 means x is a root, and size is -e[x]
  vector<pair<int, int>> st; // Stack for rollback (stores changed values)
  int cnt; // Current number of connected components

  DSU() {}
  DSU(int N) : e(N, -1), cnt(N) {}

  // Find root of x with path compression
  int get(int x) {
    return e[x] < 0 ? x : get(e[x]);
  }

  // Check if x and y are connected
  bool connected(int a, int b) {
    return get(a) == get(b);
  }

  // Size of component containing x
  int size(int x) {
    return -e[get(x)];
  }

  // Union two components; record state for rollback
  bool unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return false; // Already connected

    if (e[x] > e[y]) swap(x, y); // Union by size: ensure x is larger

    // Save state for rollback
    st.push_back({x, e[x]});
    st.push_back({y, e[y]});

    e[x] += e[y]; // Merge y into x
    e[y] = x;
    cnt--; // One fewer component
    return true;
  }

  // Undo last union
  void rollback() {
    auto [x1, y1] = st.back(); st.pop_back();
    e[x1] = y1;
    auto [x2, y2] = st.back(); st.pop_back();
    e[x2] = y2;
    cnt++;
  }
};

// Represents a single union operation (on edge u—v)
struct query {
  int v, u;
  bool united;
  query(int _v, int _u) : v(_v), u(_u), united(false) {}
};

// Segment Tree for storing edge intervals [l, r]
struct QueryTree {
  vector<vector<query>> t; // Each node stores queries that are active in that time segment
  DSU dsu;
  int T; // Number of total operations (time steps)

  QueryTree() {}
  QueryTree(int _T, int n) : T(_T) {
    dsu = DSU(n);
    t.resize(4 * T + 4);
  }

  // Internal segment tree add function
  void add(int v, int l, int r, int ul, int ur, query& q) {
    if (ul > ur) return;
    if (l == ul && r == ur) {
      t[v].push_back(q);
      return;
    }
    int mid = (l + r) / 2;
    add(2 * v, l, mid, ul, min(ur, mid), q);
    add(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
  }

  // Public wrapper: add a query in interval [l, r]
  void add_query(query q, int l, int r) {
    add(1, 0, T - 1, l, r, q);
  }

  // Traverse the segment tree and simulate unions with rollback
  void dfs(int v, int l, int r, vector<int>& ans) {
    // Apply all union operations in this segment node
    for (query& q : t[v]) {
      q.united = dsu.unite(q.v, q.u);
    }

    if (l == r) {
      ans[l] = dsu.cnt; // Save answer for time l
    } else {
      int mid = (l + r) / 2;
      dfs(2 * v, l, mid, ans);
      dfs(2 * v + 1, mid + 1, r, ans);
    }

    // Rollback all operations applied in this node
    for (query& q : t[v]) {
      if (q.united)
        dsu.rollback();
    }
  }
};

int main() {
  int n, k;
  cin >> n >> k; // n nodes, k operations
  if (k == 0) return 0;
  QueryTree st(k, n);
  map<pair<int, int>, int> mp; // Edge -> start time
  vector<int> ans(k);          // Answers for '?' queries
  vector<int> qmarks;          // Indices of '?' queries
  // Parse all k operations
  for (int i = 0; i < k; i++) {
    char c;
    cin >> c;
    if (c == '?') {
      qmarks.push_back(i); // Save query index
      continue;
    }
    int u, v;
    cin >> u >> v;
    u--; v--;
    if (u > v) swap(u, v); // Normalize edge direction

    if (c == '+') {
      mp[{u, v}] = i; // Mark time edge is added
    } else {
      // Edge removed: store active interval
      st.add_query(query(u, v), mp[{u, v}], i);
      mp[{u, v}] = -1;
    }
  }
  // Any edge still active is added until end of timeline
  for (auto [edge, start] : mp) {
    if (start != -1) {
      st.add_query(query(edge.first, edge.second), start, k - 1);
    }
  }
  // Process the tree to compute all '?'-query answers
  st.dfs(1, 0, k - 1, ans);
  // Output results of all '?'
  for (int x : qmarks) {
    cout << ans[x] << '\n';
  }
}
