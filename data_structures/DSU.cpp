/*
  Disjoint Set Union (Union-Find) with Rollback
  ---------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, N-1]

  Features:
    - Path compression + union by size
    - Optional rollback to previous state
    - Supports dynamic connectivity in offline algorithms (e.g., divide & conquer)

  Functions:
    - get(x): find root of x
    - connected(a, b): check if a and b are in same component
    - size(x): size of component containing x
    - unite(x, y): union x and y, returns true if merged
    - time(): current rollback timestamp
    - rollback(t): revert to state at timestamp t
*/

struct DSU {
  vector<int> e;                    // e[x] < 0 -> root; size = -e[x]; e[x] >= 0 -> parent
  vector<pair<int, int>> st;       // rollback stack: stores (index, old value)

  DSU(int N) : e(N, -1) {}

  // Find with path compression
  int get(int x) {
    return e[x] < 0 ? x : get(e[x]);
  }

  // Check if x and y belong to the same component
  bool connected(int a, int b) {
    return get(a) == get(b);
  }

  // Return size of component containing x
  int size(int x) {
    return -e[get(x)];
  }

  // Union by size, returns true if union happened
  bool unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y); // Ensure x has larger size (more negative)
    st.push_back({x, e[x]});
    st.push_back({y, e[y]});
    e[x] += e[y];
    e[y] = x;
    return true;
  }

  // Return current rollback timestamp
  int time() {
    return (int)st.size();
  }

  // Roll back to previous state at time t
  void rollback(int t) {
    for (int i = time(); i-- > t;) {
      e[st[i].first] = st[i].second;
    }
    st.resize(t);
  }
};
