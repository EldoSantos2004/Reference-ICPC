/*
  Kruskal's Algorithm (Minimum Spanning Tree - MST)
  --------------------------------------------------
  Indexing: 0-based for nodes in edges
  Time Complexity: O(E log E)
  Space Complexity: O(N)

  Input:
    - N: number of nodes
    - edges: list of weighted edges in form {weight, {u, v}}

  Output:
    - Returns total weight of the MST if the graph is connected
    - Returns -1 if MST cannot be formed (i.e., graph is disconnected)

  Note:
    - Requires a Disjoint Set Union (DSU) / Union-Find data structure with:
        - unite(a, b): merges components, returns true if successful
        - size(v): returns size of component containing v
*/

template <class T>
T kruskal(int N, vector<pair<T, pair<int, int>>> edges) {
  sort(edges.begin(), edges.end()); // Sort by weight (non-decreasing)
  T ans = 0;
  DSU D(N); // Disjoint Set Union for N nodes
  for (auto &[w, uv] : edges) {
    int u = uv.first, v = uv.second;
    if (D.unite(u, v)) {
      ans += w; // Add edge to MST if u and v are in different components
    }
  }
  // Check if MST spans all nodes (i.e., one component of size N)
  return (D.size(0) == N ? ans : -1);
}
