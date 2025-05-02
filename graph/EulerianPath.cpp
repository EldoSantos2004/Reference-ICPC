/*
  Eulerian Path (Hierholzer's Algorithm)
  --------------------------------------
  Time Complexity: O(E)
  Space Complexity: O(V + E)

  Input:
    - g: adjacency list of the graph
        * Directed: vector<vector<pair<int, int>>> g
            where g[v] = list of {to, edge_index}
        * Undirected: vector<vector<int>> g
            where g[v] = list of neighbors
    - seen: vector<bool> seen(E) - only needed for directed version
    - path: vector<int> path - will be filled in reverse order of traversal
            reverse(path.begin(), path.end());
*/

// Directed Version //
void dfs_directed(int node) {
  while (!g[node].empty()) {
    auto [son, idx] = g[node].back();
    g[node].pop_back();
    if (seen[idx]) continue;  // Skip if edge already visited
    seen[idx] = true;
    dfs_directed(son);
  }
  path.push_back(node); // Post-order insertion (reverse of actual path)
}

// Undirected Version //
void dfs_undirected(int node) {
  while (!g[node].empty()) {
    int son = g[node].back();
    g[node].pop_back();
    dfs_undirected(son);
  }
  path.push_back(node); // Post-order insertion
}
