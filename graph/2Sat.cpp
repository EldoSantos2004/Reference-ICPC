struct TwoSatSolver {
  int n_vars;                     // Number of boolean variables
  int n_vertices;                 // Total vertices in the implication graph (2 per variable)
  vector<vector<int>> adj;       // Implication graph: adj[i] contains edges from node i
  vector<vector<int>> adj_t;     // Transposed graph for Kosaraju's algorithm
  vector<bool> used;             // Visited marker for DFS
  vector<int> order;             // Finishing order of vertices (DFS1)
  vector<int> comp;              // Component ID for each node (DFS2)
  vector<bool> assignment;       // Final truth assignment for each variable

  // Constructor initializes all data structures
  TwoSatSolver(int _n_vars)
    : n_vars(_n_vars),
      n_vertices(2 * _n_vars),
      adj(n_vertices),
      adj_t(n_vertices),
      used(n_vertices),
      comp(n_vertices, -1),
      assignment(n_vars) {
    order.reserve(n_vertices); // Pre-allocate memory for efficiency
  }

  // First DFS pass for Kosaraju's algorithm (on original graph)
  void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
      if (!used[u])
        dfs1(u);
    }
    order.push_back(v); // Save the vertex post-DFS for reverse ordering
  }

  // Second DFS pass on the transposed graph to label components
  void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
      if (comp[u] == -1)
        dfs2(u, cl);
    }
  }

  // Solves the 2-SAT problem using Kosaraju’s algorithm
  bool solve_2SAT() {
    // 1st pass: fill the order vector
    order.clear();
    used.assign(n_vertices, false);
    for (int i = 0; i < n_vertices; ++i) {
      if (!used[i])
        dfs1(i);
    }

    // 2nd pass: find SCCs in reverse postorder
    comp.assign(n_vertices, -1);
    for (int i = 0, j = 0; i < n_vertices; ++i) {
      int v = order[n_vertices - i - 1]; // Reverse postorder
      if (comp[v] == -1)
        dfs2(v, j++);
    }

    // Assign values to variables based on component comparison
    assignment.assign(n_vars, false);
    for (int i = 0; i < n_vertices; i += 2) {
      if (comp[i] == comp[i + 1])
        return false; // Contradiction: variable and its negation are in the same SCC
      assignment[i / 2] = comp[i] > comp[i + 1]; // True if var's component comes after its negation
    }
    return true;
  }

  // Adds a disjunction (a ∨ b) to the implication graph
  // `na` and `nb` indicate negation: if true means ¬a or ¬b
  // Variables are 0-indexed. Bounds are inclusive for each literal (i.e., 0 to n_vars - 1)
  void add_disjunction(int a, bool na, int b, bool nb) {
    // Each variable `x` has two nodes:
    // x => 2*x, ¬x => 2*x + 1
    // We encode (a ∨ b) as (¬a ⇒ b) and (¬b ⇒ a)
    a = 2 * a ^ na;
    b = 2 * b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;

    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
  }
};
