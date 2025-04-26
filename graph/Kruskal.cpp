template <class T> T kruskal(int N, vector<pair<T, pair<int, int>>> edges) {
	sort(edges.begin(), edges.end());
	T ans = 0;
	DSU D(N + 1);  // edges that unite are in MST
	for (pair<T, pair<int, int>> &e : edges) {
		if (D.unite(e.second.first, e.second.second)) { ans += e.first; }
	}
	// -1 if the graph is not connected, otherwise the sum of the edge lengths
	return (D.size(1) == N ? ans : -1);
}
