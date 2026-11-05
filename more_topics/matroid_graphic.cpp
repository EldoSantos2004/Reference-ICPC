struct DSU {
	vector<int> dsu, sz;
	DSU(int n) : dsu(n), sz(n) { iota(begin(dsu), end(dsu), 0); }
	int find(int x) {
		if (x == dsu[x]) return x;
		return dsu[x] = find(dsu[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] < sz[y]) swap(x, y);
		dsu[y] = x;
		sz[x] += sz[y];
	}
};

struct GraphicMatroid {
	int n;  // nodes of the graph must be in [0..n-1]
	DSU dsu;
	vector<pair<int, int>> edges;
	GraphicMatroid(int n, const vector<pair<int, int>> &edges)
	    : n(n), dsu(n), edges(edges) {
		clear();
	}
	void clear() { dsu = DSU(n); }
	bool check(int x) { return dsu.find(edges[x].first) != dsu.find(edges[x].second); }
	void add(int x) { dsu.merge(edges[x].first, edges[x].second); }
	void precomp() {}
};