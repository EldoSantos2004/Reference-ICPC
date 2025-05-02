/*
  THIS CODE HAS NOT BEEN TESTED BEFOREHAND
  Maximum Bipartite Matching - Hopcroft-Karp Algorithm
  -----------------------------------------------------
  Indexing: 0-based
  Time Complexity: O(sqrt(V) * E)
  Space Complexity: O(V + E)

  Input:
    - n: number of nodes on the left
    - m: number of nodes on the right
    - g[l]: adjacency list for left node l (list of right-side neighbors)

  Output:
    - match_right[r] = l means right node r is matched to left node l
    - match_left[l] = r means left node l is matched to right node r
    - Function returns total number of matching pairs
*/

const int INF = 1e9;

int n, m; // Number of nodes on left and right
vector<vector<int>> g;       // Adjacency list: g[l] contains neighbors of left node l
vector<int> match_left, match_right; // match_left[l], match_right[r]
vector<int> dist;            // Distance levels for BFS

// BFS to build layer graph, returns true if there's at least one unmatched node on the right reachable from left
bool bfs() {
  queue<int> q;
  dist.assign(n, INF);

  for (int l = 0; l < n; ++l) {
    if (match_left[l] == -1) {
      dist[l] = 0;
      q.push(l);
    }
  }

  bool found = false;

  while (!q.empty()) {
    int l = q.front(); q.pop();
    for (int r : g[l]) {
      int matched_l = match_right[r];
      if (matched_l == -1) {
        found = true; // Free right node reachable -> potential augmenting path
      } else if (dist[matched_l] == INF) {
        dist[matched_l] = dist[l] + 1;
        q.push(matched_l);
      }
    }
  }

  return found;
}

// DFS to find augmenting paths in the layered graph
bool dfs(int l) {
  for (int r : g[l]) {
    int matched_l = match_right[r];
    if (matched_l == -1 || (dist[matched_l] == dist[l] + 1 && dfs(matched_l))) {
      match_left[l] = r;
      match_right[r] = l;
      return true;
    }
  }
  dist[l] = INF;
  return false;
}

// Main function to compute maximum matching
int hopcroft_karp() {
  match_left.assign(n, -1);
  match_right.assign(m, -1);

  int matching = 0;
  while (bfs()) {
    for (int l = 0; l < n; ++l) {
      if (match_left[l] == -1 && dfs(l)) {
        ++matching;
      }
    }
  }
  return matching;
}

int main() {
  cin >> n >> m;
  g.assign(n, {});
  int e; cin >> e;
  while (e--) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v); // u in [0, n-1], v in [0, m-1]
  }

  int res = hopcroft_karp();
  cout << "Maximum matching size: " << res << '\n';
  for (int r = 0; r < m; ++r) {
    if (match_right[r] != -1) {
      cout << match_right[r] + 1 << " " << r + 1 << '\n'; // 1-based output
    }
  }
}
