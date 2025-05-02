/*
  Longest Increasing Subsequence + (Recover Sequence) O(n log n)
  -------------------------------------------------
  If no recovery is needed, use dp[] only.
  dp.size() gives the length of LIS.
  For non-decreasing use upper_bound instead of lower_bound.
*/
vector<int> dp;    // smallest tail values of LIS length i+1
vector<int> dp_index;    // index in original array
vector<int> parent(n, -1);    // parent[i] = index of previous element in LIS
vector<int> last_pos(n + 1);  // last_pos[len] = index in v[] ending LIS of length len
for (int i = 0; i < n; i++) {
  auto it = lower_bound(dp.begin(), dp.end(), v[i]);
  int len = it - dp.begin();
  if (it == dp.end()) {
    dp.push_back(v[i]);
    dp_index.push_back(i); // Ignore if no recovery
  } else {
    *it = v[i];
    dp_index[len] = i; // Ignore if no recovery
  }
  if (len > 0) parent[i] = dp_index[len - 1]; // Ignore if no recovery
}
// Reconstruct LIS
vector<int> lis;
int pos = dp_index.back();
while (pos != -1) {
  lis.push_back(v[pos]);
  pos = parent[pos];
}
reverse(lis.begin(), lis.end());
