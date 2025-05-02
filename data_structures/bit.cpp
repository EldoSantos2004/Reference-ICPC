/*
  Binary Indexed Tree (Fenwick Tree) Fast Implementation
  ----------------------------------
  Indexing: 1-based
  Bounds: [1, MAXN)
  Time Complexity:
    - update(x, val): O(log n) -> adds val to index x
    - get(x): O(log n) -> prefix sum from 1 to x
  Space Complexity: O(n)
*/

const int MAXN = 10000;
int bit[MAXN];

// Add `val` to index `x`
void update(int x, int val) {
  for (; x < MAXN; x += x & -x) {
    bit[x] += val;
  }
}

// Get prefix sum from 1 to `x`
int get(int x) {
  int ans = 0;
  for (; x > 0; x -= x & -x) {
    ans += bit[x];
  }
  return ans;
}
