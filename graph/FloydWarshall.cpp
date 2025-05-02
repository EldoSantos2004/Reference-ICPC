/*
  Floyd-Warshall Algorithm (All-Pairs Shortest Paths)
  ---------------------------------------------------
  Indexing: 0-based
  Time Complexity: O(V^3)
  Space Complexity: O(V^2)

  Input:
    - d: distance matrix of size n x n
        * d[i][j] should be initialized as:
            - 0 if i == j
            - weight of edge (i, j) if exists
            - INF (e.g. 1e18) otherwise
*/

vector<vector<ll>> d(n, vector<ll>(n, 1e18)); // distance matrix

// This version is by default adapted for UNDIRECTED graphs.
for (int k = 0; k < n; k++) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) { // For directed graphs, use j = 0; j < n; j++
      long long new_dist = d[i][k] + d[k][j];
      if (new_dist < d[i][j]) {
        d[i][j] = d[j][i] = new_dist; // update both directions for undirected graph
      }
    }
  }
}
