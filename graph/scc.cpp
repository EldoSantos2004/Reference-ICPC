/*
  Strongly Connected Components (Kosaraju's Algorithm)
  -----------------------------------------------------
  Indexing: 0-based
  Time Complexity: O(V + E)
  Space Complexity: O(V + E)

  Input:
    - n: number of nodes
    - m: number of directed edges
    - adj: original graph
    - adjr: reversed graph

  Output:
    - comp[i]: component ID of node i
    - order[]: nodes in reverse post-order (1st DFS)
    - nc: is the number of unique comp values
*/

vector<vector<int>> adj, adjr;
vector<bool> vis;
vector<int> order, comp;

// First DFS: post-order on original graph
void dfs(int v) {
  vis[v] = true;
  for (int u : adj[v]) {
    if (!vis[u])
      dfs(u);
  }
  order.push_back(v); // Record post-order
}

// Second DFS: assign component IDs on reversed graph
void dfsr(int v, int k) {
  vis[v] = true;
  comp[v] = k;
  for (int u : adjr[v]) {
    if (!vis[u])
      dfsr(u, k);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  adj.assign(n, vector<int>());
  adjr.assign(n, vector<int>());
  comp.resize(n);
  // Read edges and build both original and reversed graphs
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adjr[b].push_back(a);
  }
  // First pass: DFS on original graph to get order
  vis.assign(n, false);
  order.clear();
  for (int i = 0; i < n; i++) {
    if (!vis[i]) dfs(i);
  }
  // Second pass: DFS on reversed graph using reverse post-order
  vis.assign(n, false);
  int nc = 0;
  for (int i = n - 1; i >= 0; i--) {
    int v = order[i];
    if (!vis[v]) {
      dfsr(v, nc++);
    }
  }
  // comp[i] now holds the component ID for node i (0-based)
  // nc = number of strongly connected components
}
