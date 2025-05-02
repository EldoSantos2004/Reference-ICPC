/*
  Sparse Table (Range Minimum Query)
  ----------------------------------
  Indexing: 0-based
  Bounds: [0, n-1]
  Time Complexity:
    - Build: O(n log n)
    - Query: O(1)
  Space Complexity: O(n log n)

  Features:
    - Immutable RMQ (no updates)
    - Works for idempotent operations like min, max, gcd
*/

const int MAXN = 100005;
const int K = 30; // floor(log2(MAXN))
int lg[MAXN + 1]; // log base 2 of each i
int st[K + 1][MAXN]; // st[k][i] = min in [i, i + 2^k - 1]

vector<int> a; // input array
int n;

// Returns min in range [L, R]
int mini(int L, int R) {
  int len = R - L + 1;
  int i = lg[len];
  return min(st[i][L], st[i][R - (1 << i) + 1]);
}

int main() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  // Precompute binary logs
  lg[1] = 0;
  for (int i = 2; i <= n; i++) {
    lg[i] = lg[i / 2] + 1;
  }
  // Initialize 2^0 intervals
  for (int i = 0; i < n; i++) {
    st[0][i] = a[i];
  }
  // Build sparse table
  for (int k = 1; k <= K; k++) {
    for (int i = 0; i + (1 << k) <= n; i++) {
      st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
  }
  // Example usage
  int q; cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << mini(l, r) << '\n';
  }
  return 0;
}
