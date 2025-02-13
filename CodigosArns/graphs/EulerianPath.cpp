// check if all edges are visite
// directed
void dfs(int node) {
	while (!g[node].empty()) {
		auto [son, idx] = g[node].back();
		g[node].pop_back();
		if (seen[idx]) { continue; }
		seen[idx] = true;
		dfs(son);
	}
	path.push_back(node);
}
//undirected
void dfs(int node) {
	while (!g[node].empty()) {
		int son = g[node].back();
		g[node].pop_back();
		dfs(son);
	}
	path.push_back(node);
}
