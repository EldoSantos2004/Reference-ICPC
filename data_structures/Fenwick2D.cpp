/*
  2D Fenwick Tree (Binary Indexed Tree)
  -------------------------------------
  Indexing: 1-based
  Bounds: [1, n] inclusive
  Time Complexity:
    -update(x, y, v): O(log^2 n)
    -get(x, y): sum of rectangle [1,1] to [x,y]
    -get1(x1, y1, x2, y2): sum over rectangle [x1,y1] to [x2,y2]
  Space Complexity: O(n^2)

  -Can be adapted for rectangular grids by using n, m separately
*/

struct Fenwick2D {
  vector<vector<ll>> b; // 2D BIT array
  int n;                // Grid size (1-based)

  Fenwick2D(int _n) : b(_n + 5, vector<ll>(_n + 5, 0)), n(_n) {}

  // Add `val` to cell (x, y)
  void update(int x, int y, int val) {
    for (; x <= n; x += (x & -x)) {
      for (int j = y; j <= n; j += (j & -j)) {
        b[x][j] += val;
      }
    }
  }

  // Get sum of rectangle [(1,1) to (x,y)]
  ll get(int x, int y) {
    ll ans = 0;
    for (; x > 0; x -= x & -x) {
      for (int j = y; j > 0; j -= j & -j) {
        ans += b[x][j];
      }
    }
    return ans;
  }

  // Get sum over subrectangle [(x1,y1) to (x2,y2)]
  ll get1(int x1, int y1, int x2, int y2) {
    return get(x2, y2)-get(x1-1, y2)-get(x2, y1-1) + get(x1-1, y1-1);
  }
};
// Usage example:
Fenwick2D fw(n);
fw.update(3, 4, 5);                 // add 5 to (3, 4)
ll sum = fw.get(3, 4);             // sum from (1,1) to (3,4)
ll range = fw.get1(2, 2, 5, 5);    // sum in rectangle [(2,2)-(5,5)]
