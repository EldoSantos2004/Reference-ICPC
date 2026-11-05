template <class M1, class M2> vector<bool> MatroidIsect(M1 m1, M2 m2, int n) {
	vector<bool> in_S(n);
	auto augment = [&] {
		vector<int> S, E_S;  // E_S has indices of all edges not in S
		for (int i = 0; i < n; i++) {
			if (in_S[i]) S.push_back(i);
			else E_S.push_back(i);
		}
		// build exchange graph
		vector<vector<int>> adj(n);
		for (int y : S) {
			m1.clear(), m2.clear();
			for (int i : S) {
				if (i != y) m1.add(i), m2.add(i);
			}
			// optional precomputation, can be an empty function
			m1.precomp(), m2.precomp();
			for (int x : E_S) {
				if (m1.check(x)) adj[y].push_back(x);
				if (m2.check(x)) adj[x].push_back(y);
			}
		}
		// identify sources and sinks for BFS
		vector<bool> is_sink(n);
		queue<int> q;
		vector<bool> vis(n);

		m1.clear(), m2.clear();
		for (int y : S) m1.add(y), m2.add(y);
		m1.precomp(), m2.precomp();  // optional precomp
		for (int x : E_S) {
			if (m1.check(x)) vis[x] = 1, q.push(x);  // x is a source
			is_sink[x] = m2.check(x);
		}
		// BFS to find augmenting path from source to sink
		vector<int> prev(n, -1);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (is_sink[u]) {
				// augmenting path found
				for (int v = u; v != -1; v = prev[v]) { in_S[v] = !in_S[v]; }
				return true;
			}
			for (int v : adj[u]) {
				if (vis[v]) continue;
				q.push(v);
				vis[v] = 1;
				prev[v] = u;
			}
		}
		return false;
	};
	while (augment());
	return in_S;
}