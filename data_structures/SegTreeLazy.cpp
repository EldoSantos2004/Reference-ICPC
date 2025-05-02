/*
  Lazy Segment Tree (Range Update, Range Query)
  ---------------------------------------------
  Indexing: 0-based
  Bounds: [0, n-1]
  Time Complexity:
    - build: O(n)
    - update(l, r, v): O(log n)
    - query(l, r): O(log n)
  Space Complexity: O(4n)
*/

// Example num_t struct for sum queries
struct num_t {
  long long val;
  static const num_t null_v;
  num_t(long long x = 0) : val(x) {}
  num_t op(const num_t& other) const {
    return num_t(val + other.val);
  }
  num_t lazy_op(const num_t& lazy_val, int len) const {
    return num_t(val + lazy_val.val * len);
  }
};

const num_t num_t::null_v = num_t(0);


template <typename num_t> 
struct segtree {
  int n;
  vector<num_t> tree, lazy;

  // Initialize segment tree with array of size s
  void init(int s, long long* arr) {
    n = s;
    tree.assign(4 * n, num_t());
    lazy.assign(4 * n, num_t());
    init(0, 0, n - 1, arr);
  }

  // Build segment tree from array
  num_t init(int i, int l, int r, long long* arr) {
    if (l == r) return tree[i] = num_t(arr[l]);

    int mid = (l + r) / 2;
    num_t left = init(2 * i + 1, l, mid, arr);
    num_t right = init(2 * i + 2, mid + 1, r, arr);
    return tree[i] = left.op(right);
  }

  // Public wrapper: update range [l, r] with value v
  void update(int l, int r, num_t v) {
    if (l > r) return;
    update(0, 0, n - 1, l, r, v);
  }

  // Internal recursive update
  num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl) return tree[i]; // no overlap
    if (ql <= tl && tr <= qr) {
      lazy[i].val += v.val;
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  // Public wrapper: query sum in range [l, r]
  num_t query(int l, int r) {
    if (l > r) return num_t::null_v;
    return query(0, 0, n - 1, l, r);
  }

  // Internal recursive query
  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr) return tree[i]; // total overlap
    if (tr < ql || qr < tl) return num_t::null_v; // no overlap

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr);
    num_t b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  // Push down pending lazy updates to children
  void eval_lazy(int i, int l, int r) {
    tree[i] = tree[i].lazy_op(lazy[i], r - l + 1);
    if (l != r) {
      lazy[2 * i + 1].val += lazy[i].val;
      lazy[2 * i + 2].val += lazy[i].val;
    }
    lazy[i] = num_t(); // reset lazy at this node
  }
};
