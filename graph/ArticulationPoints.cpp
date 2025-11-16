/*
  Articulation Points (Cut Vertices) in an Undirected Graph
  ----------------------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity: O(V + E)
  Space Complexity: O(V)

  Use Case:
    - Identifies vertices whose removal increases the number of connected components.
    - Works on undirected graphs (connected or disconnected).
*/

int n; // Number of nodes in the graph
vector<vector<int>> adj; // Adjacency list of the undirected graph

vector<bool> visited; // Marks if a node was visited during DFS
vector<int> tin, low; // tin[v]: discovery time; low[v]: lowest discovery time reachable from subtree
int timer; // Global time counter for DFS

// DFS traversal to identify articulation points
void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  int children = 0;
  for (int to : adj[v]) {
    if (to == p) continue; // Skip the parent edge
    if (visited[to]) {
      // Back edge
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      // Articulation point condition for non-root
      if (low[to] >= tin[v] && p != -1) {
        // be careful as this may make the same articulation point appear many times
        // v is an articulation point
        // handle_cutpoint(v);
      }
      ++children;
    }
  }
  // Articulation point condition for root
  if (p == -1 && children > 1) {
    // v is an articulation point
    // handle_cutpoint(v);
  }
}

// Initializes structures and launches DFS
void find_cutpoints() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);

  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}

