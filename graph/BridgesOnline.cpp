/*
  Online Bridge-Finding (Dynamic Edge Insertion)
  ----------------------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive
  Time Complexity:
    - Amortized O(log^2N) per edge addition
  Space Complexity: O(V)

  Features:
    - Maintains the number of bridges dynamically as edges are added one by one.
    - Detects if adding an edge merges different 2-edge-connected components.
    - No deletions supported.

  Input:
    init(n)     - Initializes the data structure for a graph with n nodes.
    add_edge(a, b) - Adds an undirected edge between nodes a and b.

  Output:
    `bridges` - Global variable representing the current number of bridges.
*/

vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
int bridges; // Number of bridges in the graph
int lca_iteration;
vector<int> last_visit;

// Initializes the data structures
void init(int n) {
  par.resize(n);
  dsu_2ecc.resize(n);
  dsu_cc.resize(n);
  dsu_cc_size.resize(n);
  last_visit.assign(n, 0);
  lca_iteration = 0;
  bridges = 0;

  for (int i = 0; i < n; ++i) {
    par[i] = -1;
    dsu_2ecc[i] = i;
    dsu_cc[i] = i;
    dsu_cc_size[i] = 1;
  }
}

// Finds the representative of the 2-edge-connected component of node v
int find_2ecc(int v) {
  if (v == -1) return -1;
  return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}

// Finds the connected component representative of the component containing v
int find_cc(int v) {
  v = find_2ecc(v);
  return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(dsu_cc[v]);
}

// Makes node v the root of its tree, rerouting parent pointers upward
void make_root(int v) {
  int root = v;
  int child = -1;
  while (v != -1) {
    int p = find_2ecc(par[v]);
    par[v] = child;
    dsu_cc[v] = root;
    child = v;
    v = p;
  }
  dsu_cc_size[root] = dsu_cc_size[child];
}

// Merges paths from a and b to their lowest common ancestor in the 2ECC forest
void merge_path(int a, int b) {
  ++lca_iteration;
  vector<int> path_a, path_b;
  int lca = -1;

  while (lca == -1) {
    if (a != -1) {
      a = find_2ecc(a);
      path_a.push_back(a);
      if (last_visit[a] == lca_iteration) {
        lca = a;
        break;
      }
      last_visit[a] = lca_iteration;
      a = par[a];
    }
    if (b != -1) {
      b = find_2ecc(b);
      path_b.push_back(b);
      if (last_visit[b] == lca_iteration) {
        lca = b;
        break;
      }
      last_visit[b] = lca_iteration;
      b = par[b];
    }
  }

  // Merge all nodes on path_a and path_b into the same 2ECC
  for (int v : path_a) {
    dsu_2ecc[v] = lca;
    if (v == lca) break;
    --bridges;
  }
  for (int v : path_b) {
    dsu_2ecc[v] = lca;
    if (v == lca) break;
    --bridges;
  }
}

// Adds an undirected edge between a and b and updates bridge count
void add_edge(int a, int b) {
  a = find_2ecc(a);
  b = find_2ecc(b);
  if (a == b) return; // Already in the same 2ECC

  int ca = find_cc(a);
  int cb = find_cc(b);

  if (ca != cb) {
    // Bridge found - connects two different components
    ++bridges;
    // Union by size
    if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
      swap(a, b);
      swap(ca, cb);
    }
    make_root(a);
    par[a] = b;
    dsu_cc[a] = b;
    dsu_cc_size[cb] += dsu_cc_size[a];
  } else {
    // No new bridge, but must merge paths to unify 2ECCs
    merge_path(a, b);
  }
}

// Example usage
int main() {
  init(n);
  for (auto [u, v] : edges) {
    add_edge(u, v);
    cout << "Current bridge count: " << bridges << '\n';
  }
}
