/*
  Bellman-Ford (SPFA variant) for Shortest Paths
  -----------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity: O(V * E) worst-case (amortized better)
  Space Complexity: O(V + E)

  Features:
    - Handles negative edge weights
    - Detects negative weight cycles (returns false if one exists)
    - Works on directed or undirected graphs

  Path Reconstruction:
    - To recover the path from source `s` to any node `u`:
        vector<int> path;
        for (int v = u; v != -1; v = parent[v])
          path.push_back(v);
        reverse(path.begin(), path.end());
*/

const int INF = 1<<30; // Large value to represent "infinity"
vector<vector<pair<int, int>>> adj; // adj[v] = list of (neighbor, weight) pairs
vector<int> parent; // parent(n, -1) for path reconstruction

// SPFA implementation to find shortest paths from source s
// d[i] will contain shortest distance from s to i
// Returns false if a negative cycle is detected
// For path reconstruction add vector<int>& parent as parameter
bool spfa(int s, vector<int>& d, vector<int>& parent) {
  int n = adj.size();
  d.assign(n, INF);
  vector<int> cnt(n, 0);       // Count how many times each node has been relaxed
  vector<bool> inqueue(n, false); // Tracks if a node is currently in queue
  queue<int> q;

  d[s] = 0;
  q.push(s);
  inqueue[s] = true;

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    inqueue[v] = false;

    for (auto edge : adj[v]) {
      int to = edge.first;
      int len = edge.second;

      if (d[v] + len < d[to]) {
        parent[to] = v; // For path reconstruction
        d[to] = d[v] + len;
        if (!inqueue[to]) {
          q.push(to);
          inqueue[to] = true;
          cnt[to]++;
          if (cnt[to] > n)
            return false; // Negative weight cycle detected
        }
      }
    }
  }

  return true; // No negative cycles; shortest paths computed
}
