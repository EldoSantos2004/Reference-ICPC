/*
  Persistent Segment Tree (Point Updates, Range Queries)
  ------------------------------------------------------
  Indexing: 1-based
  Bounds: [1, n]
  Time Complexity:
    - Build: O(n)
    - Point update: O(log n) -> returns new version
    - Range query: O(log n)
    - Copy version: O(1)

  Features:
    - Each update creates a new tree version with shared unchanged nodes
    - Supports querying over any version
    - Useful in rollback problems, version history, and functional programming
*/

struct Node {
  ll val;     // segment sum
  Node *l, *r;

  // Leaf node
  Node(ll x) : val(x), l(nullptr), r(nullptr) {}

  // Internal node with children
  Node(Node *_l, Node *_r) {
    l = _l;
    r = _r;
    val = 0;
    if (l) val += l->val;
    if (r) val += r->val;
  }

  // Version clone (used when copying tree version directly)
  Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

int n, sz = 1;
ll a[200001];         // Input array (1-indexed)
Node *t[200001];      // Roots of different versions (t[version_id])

// Build initial segment tree from array a[1..n]
Node *build(int l = 1, int r = n) {
  if (l == r) return new Node(a[l]);
  int mid = (l + r) / 2;
  return new Node(build(l, mid), build(mid + 1, r));
}

// Update position `pos` with `val` in given `node` version
Node *update(Node *node, int pos, int val, int l = 1, int r = n) {
  if (l == r) return new Node(val); // replace leaf
  int mid = (l + r) / 2;
  if (pos <= mid)
    return new Node(update(node->l, pos, val, l, mid), node->r);
  else
    return new Node(node->l, update(node->r, pos, val, mid + 1, r));
}

// Query sum over range [a, b] in given version
ll query(Node *node, int a, int b, int l = 1, int r = n) {
  if (r < a || l > b) return 0;         // No overlap
  if (l >= a && r <= b) return node->val; // Total overlap
  int mid = (l + r) / 2;
  return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  // Build version 0
  t[0] = build();
  sz = 1;

  while (q--) {
    int ty;
    cin >> ty;

    if (ty == 1) {
      // Point update: create new version from t[k] with a[pos] = x
      int k, pos, x;
      cin >> k >> pos >> x;
      t[k] = update(t[k], pos, x);

    } else if (ty == 2) {
      // Range query on version k over [l, r]
      int k, l, r;
      cin >> k >> l >> r;
      cout << query(t[k], l, r) << '\n';

    } else if (ty == 3) {
      // Clone version k into new version
      int k;
      cin >> k;
      t[sz++] = new Node(t[k]);
    }
  }
  return 0;
}
