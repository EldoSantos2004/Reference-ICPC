/*
  Parallel Binary Search
  ----------------------
  Solves: k independent queries where each answer lies in range [lo, hi]
  - At each iteration, test the midpoint for a batch of queries
  Indexing: 0-based
  Bounds:
    - i in [0, m-1] for the structure version
    - q in [0, k-1] for each of the k queries
  Time Complexity: O((m + k) * log M)
  Space Complexity: O(k + m)
  You must:
    - Reset data structures before each iteration
    - Implement apply_change(i) and check_query(q)
*/
int lo[MAXN], hi[MAXN];     // binary search bounds for each query
vector<int> tocheck[MAXN];  // tocheck[mid] = list of queries to check at mid

bool done = false;
while (!done) {
  done = true;
   // Reset changes of structure to 0 before each iteration
  // Assign queries to current midpoint
  for (int q = 0; q < k; q++) {
    if (lo[q] < hi[q]) {
      tocheck[(lo[q] + hi[q]) / 2].push_back(q);
    }
  }
  // Apply changes and evaluate queries
  for (int i = 0; i < m; i++) {
    // Apply change for ith query to your data structure
    apply_change(i);
    for (int q : tocheck[i]) {
      done = false; // at least one query is not done
      // Evaluate query q using the updated structure
      if (operationToCheck(q)) {
        hi[q] = i; // condition is true, try earlier
      } else {
        lo[q] = i + 1; // condition false, try later
      }
    }
  }
}
