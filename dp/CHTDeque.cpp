/*
  Convex Hull Trick (CHT) - Min Query with Increasing Slopes
  ----------------------------------------------------------
  Indexing: 1-based for `a`, `dp`, `s`
  Bounds:
    - i from 1 to m // number of elements in the array
    - j from 1 to p // number of transitions
  Time Complexity: O(m * p)
  Requires:
    - Lines inserted in increasing slope order for min query
    - Queries made with increasing x values

  dp[i][j] = min over k < i of { dp[k][j-1] + a[i] * (i - k) + s[i] - s[k+1] }
  dp[i][j] = min over k < i of { dp[k][j-1] + cost(k, i) }

  We reformulate:
    y = m * x + c
    line: m = -k - 1, c = dp[k][j-1] - s[k+1]
    eval: m * a[i] + c + a[i] * i + s[i]
*/

struct Line {
  ll a, b; // y = ax + b
  Line(ll A, ll B) : a(A), b(B) {}
  ll eval(ll x) const {
    return a * x + b;
  }
  // Returns intersection x-coordinate with another line
  double intersect(const Line& other) const {
    return (double)(other.b - b) / (a - other.a);
  }
};

// this finds the minimum and slope in increasing
// Deques for each dp stage
deque<Line> cht[p+1];
// Fill dp
cht[0].push_back(Line(-1, -s[1])); // base case
for (int i = 1; i <= m; i++) {
  for (int j = p; j >= 1; j--) {
    if (j > i) continue;
    // Maintain front of deque to find minimum
    while (cht[j - 1].size() >= 2 && cht[j - 1][1].eval(a[i]) <= cht[j - 1][0].eval(a[i])) {
      cht[j - 1].pop_front();
    }
    // Evaluate best line
    dp[i][j] = cht[j - 1].front().eval(a[i]) + a[i] * i + s[i];
    // Create new line for current i
    Line curr(-i - 1, dp[i][j] - s[i + 1]);
    // Maintain convexity: remove worse lines from back
    while (cht[j].size() >= 2) {
      Line& l1 = cht[j][cht[j].size() - 2];
      Line& l2 = cht[j].back();
      if (curr.intersect(l1) <= l2.intersect(l1)) {
        cht[j].pop_back();
      } else break;
    }
    cht[j].push_back(curr);
  }
}
