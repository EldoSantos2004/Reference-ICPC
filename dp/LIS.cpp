/*
  Longest Increasing Subsequence (LIS) - O(n log n)
  -------------------------------------------------
  Given: array v[0..n-1]
  Goal: find the length of the longest strictly increasing subsequence
  For non-decreasing use upper_bound instead of lower_bound
  Indexing: 0-based
*/
vector<int> dp;
for (int i = 0; i < n; i++) {
  auto it = lower_bound(dp.begin(), dp.end(), v[i]);
  if (it == dp.end()) {
    dp.push_back(v[i]); // extend LIS
  } else {
    *it = v[i]; // replace to maintain minimal tail
  }
}
cout << dp.size() << '\n'; // length of LIS

/*
  -------------------------------------------------
  Longest Increasing Subsequence (Recover Sequence)
  -------------------------------------------------
*/
vector<int> dp;    // smallest tail values of increasing subsequences length i+1
vector<int> dp_index;    // index in original array
vector<int> parent(n, -1);    // parent[i] = index of previous element in LIS
vector<int> last_pos(n + 1);  // last_pos[len] = index in v[] ending LIS of length len
for (int i = 0; i < n; i++) {
  int val = v[i];
  auto it = lower_bound(dp.begin(), dp.end(), val);
  int len = it - dp.begin();
  if (it == dp.end()) {
    dp.push_back(val);
    dp_index.push_back(i);
  } else {
    *it = val;
    dp_index[len] = i;
  }
  if (len > 0) parent[i] = dp_index[len - 1];
}
// Reconstruct LIS
vector<int> lis;
int pos = dp_index.back();
while (pos != -1) {
  lis.push_back(v[pos]);
  pos = parent[pos];
}
reverse(lis.begin(), lis.end());
