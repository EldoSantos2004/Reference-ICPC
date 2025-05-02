/*
  Divide and Conquer DP Optimization
  ----------------------------------
  Problem:
    - dp[i][j] = min over k <= j of { dp[i-1][k] + C(k, j) }
    - C(k, j) must satisfy the quadrangle inequality:
        - C(a, c) + C(b, d) <= C(a, d) + C(b, c) for a <= b <= c <= d
    - or monotonicity of opt[i][j] <= opt[i][j+1]

  Indexing: 0-based
  Time Complexity: O(m * n * log n)
  Space Complexity: O(n)

  dp_cur[j]: current dp[i][j] layer
  dp_before[j]: previous dp[i-1][j] layer
*/

int n, m;
vector<ll> dp_before, dp_cur;
ll C(int i, int j); // Cost function defined by user

// Recursively compute dp_cur[l..r] with optimal k in [optl, optr]
void compute(int l, int r, int optl, int optr) {
  if (l > r) return;
  int mid = (l + r) / 2;
  pair<ll, int> best = {LLONG_MAX, -1};
  for (int k = optl; k <= min(mid, optr); k++) {
    ll val = (k > 0 ? dp_before[k - 1] : 0) + C(k, mid);
    if (val < best.first) best = {val, k};
  }
  dp_cur[mid] = best.first;
  int opt = best.second;
  compute(l, mid - 1, optl, opt);
  compute(mid + 1, r, opt, optr);
}

// Entry point: computes dp[m-1][n-1]
ll solve() {
  dp_before.assign(n, 0);
  dp_cur.assign(n, 0);
  for (int i = 0; i < n; i++) {
    dp_before[i] = C(0, i);
  }
  for (int i = 1; i < m; i++) {
    compute(0, n - 1, 0, n - 1);
    dp_before = dp_cur;
  }
  return dp_before[n - 1];
}
