/*
  Given strings s and t, compute the minimum number of operations
  (insert, delete, substitute) to convert s into t.
  Indexing: 0-based (strings), DP is 1-based with offset
  dp[i][j] = cost to convert s[0..i-1] into t[0..j-1]
  Time Complexity: O(n * m)
  Transitions:
    - insert: dp[i][j-1] + 1
    - delete: dp[i-1][j] + 1
    - replace/match: dp[i-1][j-1] + (s[i-1] != t[j-1])
*/
const int MAXN = 5005;
int dp[MAXN][MAXN];

string s, t; cin >> s >> t;
int n = s.length(), m = t.length();
// Initialize all to a large number
for (int i = 0; i <= n; i++) {
  fill(dp[i], dp[i] + m + 1, 1e9);
}
dp[0][0] = 0;
for (int i = 0; i <= n; i++) {
  for (int j = 0; j <= m; j++) {
    if (j) { // insert
      dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
    }
    if (i) { // delete
      dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
    }
    if (i && j) { // replace or match
      int cost = (s[i - 1] != t[j - 1]) ? 1 : 0;
      dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + cost);
    }
  }
}
