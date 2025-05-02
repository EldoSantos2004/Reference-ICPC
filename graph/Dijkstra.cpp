vector<vector<pair<int, int>>> adj(n); // Adjacency list (node, weight)
vector<ll> dist(n, 1LL << 61); // Distance array initialized to infinity

priority_queue<pair<ll, int>> q; // Max-heap, so we push negative weights to simulate min-heap
dist[0] = 0; // Starting node distance
q.push({0, 0}); // (distance, vertex)

while (!q.empty()) {
  auto [w, v] = q.top(); q.pop();
  w = -w; // Convert back to positive
  if (w > dist[v]) continue; // Skip outdated entry
  for (auto [u, cost] : adj[v]) {
    if (dist[v] + cost < dist[u]) {
      dist[u] = dist[v] + cost;
      q.push({-dist[u], u}); // Push updated distance (negated)
    }
  }
}
