/*
  Edmonds' Blossom Algorithm (Maximum Matching in General Graphs)
  ----------------------------------------------------------------
  Indexing: 1-based
  Node Bounds: [1, n]
  Time Complexity: O(n³) in worst case
  Space Complexity: O(n²)

  Features:
    - Handles odd-length cycles (blossoms)
    - Works on any undirected graph (not just bipartite)
    - Uses BFS with blossom contraction and path augmentation

  Input:
    - n: number of vertices
    - add_edge(u, v): undirected edges between nodes (1 ≤ u,v ≤ n)

  Output:
    - maximum_matching(): returns size of max matching
    - match[u]: matched vertex for node u (or 0 if unmatched)
*/

const int N = 2009;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Blossom {
  int vis[N];        // vis[u]: -1 = unvisited, 0 = in queue, 1 = outer layer
  int par[N];        // par[u]: parent in alternating tree
  int orig[N];       // orig[u]: base of blossom u belongs to
  int match[N];      // match[u]: matched partner of u (0 if unmatched)
  int aux[N];        // aux[u]: visit marker for LCA
  int t;             // global timestamp for LCA markers
  int n;             // number of nodes
  bool ad[N];        // ad[u]: whether u is reachable in an alternating path
  vector<int> g[N];  // g[u]: adjacency list
  queue<int> Q;      // BFS queue

  // Constructor: initializes data for n nodes
  Blossom() {}
  Blossom(int _n) {
    n = _n;
    t = 0;
    for (int i = 0; i <= n; ++i) {
      g[i].clear();
      match[i] = par[i] = vis[i] = aux[i] = ad[i] = orig[i] = 0;
    }
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // Augment the matching along the alternating path from u to v
  void augment(int u, int v) {
    int pv = v, nv;
    do {
      pv = par[v];
      nv = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = nv;
    } while (u != pv);
  }

  int lca(int v, int w) {
    ++t; // Increment timestamp for LCA markers
    while (true) {
      if (v) {
        if (aux[v] == t) return v;
        aux[v] = t;
        v = orig[par[match[v]]]; // Move to the parent in the alternating tree
      }
      swap(v, w);
    }
  }

  // Contract a blossom from v and w with common ancestor a
  void blossom(int v, int w, int a) {
    while (orig[v] != a) {
      par[v] = w;
      w = match[v];
      ad[v] = true;
      if (vis[w] == 1) Q.push(w), vis[w] = 0;
      orig[v] = orig[w] = a;
      v = par[w];
    }
  }

  // Find augmenting path starting from unmatched node u
  bool bfs(int u) {
    fill(vis + 1, vis + n + 1, -1);
    iota(orig + 1, orig + n + 1, 1);
    Q = queue<int>();
    Q.push(u);
    vis[u] = 0;

    while (!Q.empty()) {
      int v = Q.front(); Q.pop();
      ad[v] = true;
      for (int x : g[v]) {
        if (vis[x] == -1) {
          par[x] = v;
          vis[x] = 1;
          if (!match[x]) {
            augment(u, x);
            return true;
          }
          Q.push(match[x]);
          vis[match[x]] = 0;
        } else if (vis[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return false;
  }

  // Computes maximum matching and returns the size
  int maximum_matching() {
    int ans = 0;
    vector<int> p(n - 1);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rnd);
    for (int i = 1; i <= n; ++i) {
      shuffle(g[i].begin(), g[i].end(), rnd);
    }

    // Greedy matching: try to match unmatched nodes directly
    for (int u : p) {
      if (!match[u]) {
        for (int v : g[u]) {
          if (!match[v]) {
            match[u] = v;
            match[v] = u;
            ++ans;
            break;
          }
        }
      }
    }

    // Augmenting path phase
    for (int i = 1; i <= n; ++i) {
      if (!match[i] && bfs(i)) ++ans;
    }

    return ans;
  }
} M;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    M = Blossom(n);
    // Read all edges
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      M.add_edge(u, v);
    }
    // Compute max matching
    int matched = M.maximum_matching();
    if (matched * 2 == n) {
      // Perfect matching
      cout << 0 << '\n';
    } else {
      // Find reachable unmatched nodes in alternating trees
      memset(M.ad, 0, sizeof M.ad);
      for (int i = 1; i <= n; i++) {
        if (M.match[i] == 0) M.bfs(i);
      }
      int unmatched_reachable = 0;
      for (int i = 1; i <= n; i++) {
        unmatched_reachable += M.ad[i];
      }
      cout << unmatched_reachable << '\n';
    }
  }
  return 0;
}
