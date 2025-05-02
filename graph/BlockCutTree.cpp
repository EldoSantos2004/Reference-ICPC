/*
  Block-Cut Tree from Biconnected Components
  ------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity: O(V + E)
  Space Complexity: O(V + E)

  Features:
    - Identifies articulation points (cut vertices)
    - Extracts all biconnected components (BCCs)
    - Constructs the Block-Cut Tree:
        - Each BCC becomes a node in the tree
        - Each articulation point becomes its own node
        - An edge connects a BCC-node to each cutpoint in it

  Output:
    - `is_cutpoint`: true if node is an articulation point
    - `id[v]`: node ID of `v` in the block-cut tree
    - Returns the block-cut tree as an adjacency list
*/

vector<vector<int>> biconnected_components(vector<vector<int>> &g, // Adjacency list of the undirected graph
                                           vector<bool> &is_cutpoint, // Output vector (resized internally)
                                           vector<int> &id) { // Output vector (resized internally)

  int n = g.size();
  vector<vector<int>> comps; // Stores all biconnected components
  vector<int> stk;           // Stack of visited nodes for current component
  vector<int> num(n), low(n); // DFS discovery time and low-link values
  is_cutpoint.assign(n, false);

  // DFS to find BCCs and articulation points
  function<void(int, int, int&)> dfs = [&](int node, int parent, int &timer) {
    num[node] = low[node] = ++timer;
    stk.push_back(node);
    for (int son : g[node]) {
      if (son == parent) continue;
      if (num[son]) {
        // Back edge
        low[node] = min(low[node], num[son]);
      } else {
        dfs(son, node, timer);
        low[node] = min(low[node], low[son]);
        // Check articulation point condition
        if (low[son] >= num[node]) {
          is_cutpoint[node] = (num[node] > 1 || num[son] > 2); // For root and non-root
          comps.push_back({node});
          while (comps.back().back() != son) {
            comps.back().push_back(stk.back());
            stk.pop_back();
          }
        }
      }
    }
  };

  int timer = 0;
  dfs(0, -1, timer);

  id.resize(n); // Maps each original node to its block-cut tree node ID

  // Build block-cut tree using articulation points and BCCs
  function<vector<vector<int>>()> build_tree = [&]() {
    vector<vector<int>> t(1); // Dummy index 0 (not used)
    int node_id = 1; // Start assigning block-cut tree IDs from 1
    // Assign unique tree node IDs to cutpoints
    for (int node = 0; node < n; ++node) {
      if (is_cutpoint[node]) {
        id[node] = node_id++;
        t.push_back({});
      }
    }
    // Assign each component a new node and connect it to its cutpoints
    for (auto &comp : comps) {
      int bcc_node = node_id++;
      t.push_back({});
      for (int u : comp) {
        if (!is_cutpoint[u]) {
          id[u] = bcc_node;
        } else {
          t[bcc_node].push_back(id[u]);
          t[id[u]].push_back(bcc_node);
        }
      }
    }
    return t;
  };

  return build_tree(); // Return the block-cut tree
}
