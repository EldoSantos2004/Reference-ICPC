/*
  Lazy Segment Tree (Range Set + Range Add + Range Sum)
  -----------------------------------------------------
  Indexing: 0-based
  Bounds: [0, N-1]

  Features:
    - Supports range set (assign value), range add (increment), and range sum queries
    - Properly prioritizes lazy set > lazy add
*/

const int maxN = 1e5 + 5;
int N, Q;
int a[maxN];

struct node {
  ll val = 0;      // range sum
  ll lzAdd = 0;    // pending addition
  ll lzSet = 0;    // pending set (non-zero means active)
};

node tree[maxN << 2];

#define lc (p << 1)
#define rc ((p << 1) | 1)

// Update current node based on its children
inline void pushup(int p) {
  tree[p].val = tree[lc].val + tree[rc].val;
}

// Push lazy values down to children
void pushdown(int p, int l, int mid, int r) {
  // Range set overrides any pending add
  if (tree[p].lzSet != 0) {
    tree[lc].lzSet = tree[rc].lzSet = tree[p].lzSet;
    tree[lc].val = (mid - l + 1) * tree[p].lzSet;
    tree[rc].val = (r - mid) * tree[p].lzSet;
    tree[lc].lzAdd = tree[rc].lzAdd = 0;
    tree[p].lzSet = 0;
  }
  // Otherwise propagate add
  else if (tree[p].lzAdd != 0) {
    if (tree[lc].lzSet == 0) tree[lc].lzAdd += tree[p].lzAdd;
    else {
      tree[lc].lzSet += tree[p].lzAdd;
      tree[lc].lzAdd = 0;
    }
    if (tree[rc].lzSet == 0) tree[rc].lzAdd += tree[p].lzAdd;
    else {
      tree[rc].lzSet += tree[p].lzAdd;
      tree[rc].lzAdd = 0;
    }
    tree[lc].val += (mid - l + 1) * tree[p].lzAdd;
    tree[rc].val += (r - mid) * tree[p].lzAdd;
    tree[p].lzAdd = 0;
  }
}

// Build tree from array a[0..N-1]
void build(int p, int l, int r) {
  tree[p].lzAdd = tree[p].lzSet = 0;
  if (l == r) {
    tree[p].val = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lc, l, mid);
  build(rc, mid + 1, r);
  pushup(p);
}

// Add `val` to all elements in [a, b]
void add(int p, int l, int r, int a, int b, ll val) {
  if (a > r || b < l) return;
  if (a <= l && r <= b) {
    tree[p].val += (r - l + 1) * val;
    if (tree[p].lzSet == 0) tree[p].lzAdd += val;
    else tree[p].lzSet += val;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  add(lc, l, mid, a, b, val);
  add(rc, mid + 1, r, a, b, val);
  pushup(p);
}

// Set all elements in [a, b] to `val`
void set(int p, int l, int r, int a, int b, ll val) {
  if (a > r || b < l) return;
  if (a <= l && r <= b) {
    tree[p].val = (r - l + 1) * val;
    tree[p].lzAdd = 0;
    tree[p].lzSet = val;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  set(lc, l, mid, a, b, val);
  set(rc, mid + 1, r, a, b, val);
  pushup(p);
}

// Query sum over [a, b]
ll query(int p, int l, int r, int a, int b) {
  if (a > r || b < l) return 0;
  if (a <= l && r <= b) return tree[p].val;
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  return query(lc, l, mid, a, b) + query(rc, mid + 1, r, a, b);
}
// Example usage
N = 5;
a[0] = 2, a[1] = 4, a[2] = 3, a[3] = 1, a[4] = 5;
build(1, 0, N - 1);
set(1, 0, N - 1, 1, 3, 7);     // a[1..3] = 7
add(1, 0, N - 1, 2, 4, 2);     // a[2..4] += 2
cout << query(1, 0, N - 1, 0, 4) << '\n'; // total sum
