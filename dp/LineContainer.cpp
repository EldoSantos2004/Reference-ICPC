/*
  Line Container (Dynamic Convex Hull Trick)
  -----------------------------------------
  Supports:
    - Adding lines: y = k * x + m
    - Querying maximum y at given x
  Indexing: arbitrary, supports any x
  Time Complexity:
    - add(): amortized O(log n)
    - query(x): O(log n)
  Space Complexity: O(n)
  For min queries: negate slopes and intercepts on insert and result on query
  Structure:
    - Stores lines in slope-sorted order (k)
    - Each line keeps its intersection point `p` with the next line
    - Binary search on `p` to answer queries
*/
struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }  // Sort by slope
  bool operator<(ll x) const { return p < x; }             // Query comparator
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // Floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  // Update intersection point x->p with y
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, false;
    if (x->k == y->k)
      x->p = (x->m > y->m ? inf : -inf); // higher line wins
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  // Add new line: y = k * x + m
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    // Remove dominated lines after y
    while (isect(y, z)) z = erase(z);
    // Remove dominated lines before y
    if (x != begin() && isect(--x, y))
      isect(x, y = erase(y));
    // Further cleanup to preserve order
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  // Query max y at given x
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};
// Example usage:
LineContainer cht;
cht.add(3, 5);      // y = 3x + 5
cht.add(2, 7);      // y = 2x + 7
cout << cht.query(4) << '\n'; // max y at x = 4
