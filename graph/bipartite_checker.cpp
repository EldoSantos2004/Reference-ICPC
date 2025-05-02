/*
  Bipartite Graph Checker (BFS-based)
  -----------------------------------
  Indexing: 0-based
  Time Complexity: O(V + E)
  Space Complexity: O(V)

  Handles disconnected graphs
*/

int n; // Number of nodes
vector<vector<int>> adj; // Adjacency list of the undirected graph

vector<int> side(n, -1); // -1 = unvisited, 0/1 = sides of bipartition
bool is_bipartite = true;
queue<int> q;

for (int st = 0; st < n; ++st) {
  if (side[st] == -1) {
    q.push(st);
    side[st] = 0; // Start with side 0
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int u : adj[v]) {
        if (side[u] == -1) {
          // Assign opposite side to neighbor
          side[u] = side[v] ^ 1;
          q.push(u);
        } else {
          // Conflict: adjacent nodes on same side
          is_bipartite &= side[u] != side[v];
        }
      }
    }
  }
}

cout << (is_bipartite ? "YES" : "NO") << endl;
