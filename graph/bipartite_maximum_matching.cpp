/*
  Maximum Bipartite Matching (Kuhn's Algorithm)
  ---------------------------------------------
  Indexing: 0-based
  Time Complexity: O(N * (E + N)) worst case
  Space Complexity: O(N + K + E)

  Input:
    - n: number of nodes on the left side
    - k: number of nodes on the right side
    - g: adjacency list where g[v] contains all right nodes adjacent to left node v

  Output:
    - Prints the pairs (left, right) in the matching
    - mt[r] = l means right node r is matched to left node l
*/

int n, k; // n: number of left nodes, k: number of right nodes
vector<vector<int>> g; // g[l]: list of right-side neighbors of left node l
vector<int> mt;        // mt[r]: matched left node for right node r (or -1 if unmatched)
vector<bool> used;     // used[l]: visited status for left node l during DFS

// Try to find an augmenting path from left node v
bool try_kuhn(int v) {
  if (used[v])
    return false;
  used[v] = true;
  for (int to : g[v]) {
    if (mt[to] == -1 || try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  //... reading the graph ...

  mt.assign(k, -1); // Right-side nodes initially unmatched
  for (int v = 0; v < n; ++v) {
    used.assign(n, false); // Reset visited for each left node
    try_kuhn(v);
  }
  // Output matched pairs (left+1, right+1 for 1-based output)
  for (int i = 0; i < k; ++i) {
    if (mt[i] != -1)
      printf("%d %d\n", mt[i] + 1, i + 1);
  }
  return 0;
}
