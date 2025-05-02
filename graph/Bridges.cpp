/*
  Bridge-Finding in an Undirected Graph
  -------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity: O(V + E)
  Space Complexity: O(V)

  Input:
    n    - Number of nodes in the graph
    adj  - Adjacency list of the undirected graph

  Output:
    - Call `find_bridges()` to populate bridge information.
    - Modify the DFS `Bridge` section to store or print the bridges.
      A bridge is an edge (v, to) such that removing it increases the number of connected components.
*/

int n; // Number of nodes
vector<vector<int>> adj; // Adjacency list

vector<bool> visited; // Marks visited nodes
vector<int> tin, low; // tin[v]: discovery time; low[v]: lowest ancestor reachable
int timer; // Global DFS timer

// DFS to detect bridges
void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  for (int to : adj[v]) {
    if (to == p) continue; // Skip edge to parent
    if (visited[to]) {
      // Back edge
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      // Bridge condition: if no back edge connects subtree rooted at `to` to ancestors of `v`
      if (low[to] > tin[v]) {
        // (v, to) is a bridge
        // Example: bridges.push_back({v, to});
      }
    }
  }
}

// Initialize tracking structures and run DFS
void find_bridges() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}
