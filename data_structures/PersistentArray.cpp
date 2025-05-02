/*
  Persistent Array (via Persistent Segment Tree)
  ----------------------------------------------
  Indexing: 0-based
  Bounds: [0, n-1]
  Time Complexity:
    - point update: O(log n)
    - point query: O(log n)
  Space Complexity: O(log n) per update/version

  Features:
    - Supports point updates with full version history
    - Allows querying any version at any index
*/

struct Node {
  int val;
  Node *l, *r;

  // Leaf node with value
  Node(int x) : val(x), l(nullptr), r(nullptr) {}

  // Internal node with children (value is not used)
  Node(Node *ll, Node *rr) : val(0), l(ll), r(rr) {}
};

int n;
int a[100001];        // Initial array
Node *roots[100001];  // Roots of all versions (0-based)

// Build version 0 from initial array
Node *build(int l = 0, int r = n - 1) {
  if (l == r) return new Node(a[l]);
  int mid = (l + r) / 2;
  return new Node(build(l, mid), build(mid + 1, r));
}

// Create new version with a[pos] = val
Node *update(Node *node, int pos, int val, int l = 0, int r = n - 1) {
  if (l == r) return new Node(val);
  int mid = (l + r) / 2;
  if (pos <= mid)
    return new Node(update(node->l, pos, val, l, mid), node->r);
  else
    return new Node(node->l, update(node->r, pos, val, mid + 1, r));
}

// Query value at position `pos` in a given version (node)
int query(Node *node, int pos, int l = 0, int r = n - 1) {
  if (l == r) return node->val;
  int mid = (l + r) / 2;
  if (pos <= mid) return query(node->l, pos, l, mid);
  else return query(node->r, pos, mid + 1, r);
}

// External helper: get value at index in version
int get_item(int index, int version) {
  return query(roots[version], index);
}

// External helper: make new version based on `prev_version`, updating one index
void update_item(int index, int value, int prev_version, int new_version) {
  roots[new_version] = update(roots[prev_version], index, value);
}

// Initializes version 0 from given array
void init_arr(int nn, int *init) {
  n = nn;
  for (int i = 0; i < n; i++) a[i] = init[i];
  roots[0] = build();
}
