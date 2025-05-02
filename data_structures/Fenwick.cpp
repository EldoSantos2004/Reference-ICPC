/*
  Fenwick Tree (Binary Indexed Tree)
  ----------------------------------
  Indexing: 0-based
  Bounds: [0, n-1] inclusive
  Time Complexity:
    - add(x, v): O(log n)
    - sum(x): O(log n) -> prefix sum over [0, x)
    - rangeSum(l, r): O(log n) -> sum over [l, r)
    - select(k): O(log n) -> smallest x such that prefix sum >= k (works for monotonic cumulative sums)

  Space Complexity: O(n)
*/

template <typename T>
struct Fenwick {
  int n;
  std::vector<T> a;

  Fenwick(int n_ = 0) {
    init(n_);
  }

  // Initialize BIT of size n
  void init(int n_) {
    n = n_;
    a.assign(n, T{});
  }

  // Add value `v` to position `x`
  void add(int x, const T &v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] = a[i - 1] + v;
    }
  }

  // Compute prefix sum on range [0, x)
  T sum(int x) const {
    T ans{};
    for (int i = x; i > 0; i -= i & -i) {
      ans = ans + a[i - 1];
    }
    return ans;
  }

  // Compute sum over range [l, r)
  T rangeSum(int l, int r) const {
    return sum(r) - sum(l);
  }

  // Find the smallest x such that sum[0, x) > k (if exists), or returns n
  int select(const T &k) const {
    int x = 0;
    T cur{};
    for (int i = 1 << std::__lg(n); i; i >>= 1) {
      if (x + i <= n && cur + a[x + i - 1] <= k) {
        cur = cur + a[x + i - 1];
        x += i;
      }
    }
    return x;
  }
};
// Fenwick<int> bit(n);
