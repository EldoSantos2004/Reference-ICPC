/*
  DSU with Parity — Bipartite Checker
  -----------------------------------
  Indexing: 0-based
  Node Bounds: [0, n-1] inclusive

  Features:
    - Tracks parity (even/odd length) of paths in each component
    - Can be used to detect odd-length cycles (non-bipartite components)
    - Supports dynamic edge additions

  Functions:
    - make_set(v): initializes singleton component
    - find_set(v): returns root of v and its parity relative to root
    - add_edge(a, b): merges two components and checks for bipartite violation
    - is_bipartite(v): returns whether component containing v is bipartite
*/

const int MAXN = 100005; // Set according to constraints

pair<int, int> parent[MAXN]; // parent[v] = {root, parity_from_root_to_v}
int rank[MAXN];              // Union by rank
bool bipartite[MAXN];        // bipartite[root] = true if component is bipartite

// Create a new set for node v
void make_set(int v) {
  parent[v] = {v, 0};   // Self-rooted, even parity to self
  rank[v] = 0;
  bipartite[v] = true;
}

// Find the root of v and track parity along the path (0 = even, 1 = odd)
pair<int, int> find_set(int v) {
  if (v != parent[v].first) {
    auto [par, parity] = parent[v];
    auto root = find_set(par);
    parent[v] = {root.first, parity ^ root.second}; // Path compression with parity update
  }
  return parent[v];
}

// Adds an edge between a and b, merges components and checks for odd cycles
void add_edge(int a, int b) {
  auto [ra, pa] = find_set(a); // ra = root of a, pa = parity from root to a
  auto [rb, pb] = find_set(b); // rb = root of b, pb = parity from root to b

  if (ra == rb) {
    // Same component: edge (a, b) adds a cycle → check parity
    if ((pa ^ pb) == 0) {
      bipartite[ra] = false; // Found odd-length cycle
    }
  } else {
    // Merge smaller rank under larger
    if (rank[ra] < rank[rb]) swap(ra, rb), swap(pa, pb);

    // Make rb child of ra; update parity of root
    parent[rb] = {ra, pa ^ pb ^ 1};

    bipartite[ra] &= bipartite[rb]; // Component is only bipartite if both were
    if (rank[ra] == rank[rb]) rank[ra]++;
  }
}

// Check if the component containing v is bipartite
bool is_bipartite(int v) {
  return bipartite[find_set(v).first];
}
