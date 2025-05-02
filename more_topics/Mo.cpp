/*
  Mo's Algorithm (Sqrt Decomposition for Offline Queries)
  -------------------------------------------------------
  Problem: Answer q range queries [L, R] over array of length n
            using add/remove operations efficiently
  Indexing: 0-based
  Bounds:
    - arr[0..n-1]
    - queries input as 1-based and converted to 0-based
  Time Complexity: O((n + q) * sqrt(n)) per query batch
  Space Complexity: O(n + q)
  Usage:
    - Fill in logic for add/remove operations (update cur)
    - Fill answers[] indexed by original query order
*/

const int MAXN = 200500;
ll n, q;
ll arr[MAXN];      // input array
ll cnt[1000005];   // frequency count
ll answers[MAXN];  // output array
ll cur = 0;        // current query result
ll BLOCK_SIZE;

pair< pair<ll, ll>, ll> queries[MAXN]; // {{L, R}, query_index}

// Sort by block and then by R
inline bool cmp(const pair< pair<ll, ll>, ll> &x, const pair< pair<ll, ll>, ll> &y) {
  ll block_x = x.first.first / BLOCK_SIZE;
  ll block_y = y.first.first / BLOCK_SIZE;
  if (block_x != block_y) return block_x < block_y;
  return x.first.second < y.first.second;
}

int main() {
  cin >> n >> q;
  BLOCK_SIZE = sqrt(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    --l; --r; // convert to 0-based
    queries[i] = {{l, r}, i};
  }
  sort(queries, queries + q, cmp);
  ll l = 0, r = -1;
  for (int i = 0; i < q; i++) {
    int left = queries[i].first.first;
    int right = queries[i].first.second;
    // Expand to right
    while (r < right) {
      r++;
      // Operations to add arr[r], implement exactly here
    }
    // Shrink from right
    while (r > right) {
      // Operations to remove arr[r], implement exactly here
      r--;
    }
    // Expand to left
    while (l < left) {
      // Operations to remove arr[l], implement exactly here
      l++;
    }
    // Shrink from left
    while (l > left) {
      l--;
      // Operations to add arr[l], implement exactly here
    }
    answers[queries[i].second] = cur; // Current answer
  }
  for (int i = 0; i < q; i++) cout << answers[i] << '\n';
}
