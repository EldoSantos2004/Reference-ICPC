struct DSU {
	vector<int> e;
	vector<pair<int, int>> st;

	DSU(int N) : e(N, -1) {}

	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool connected(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) { return false; }
		if (e[x] > e[y]) { swap(x, y); }
		st.push_back({x, e[x]});
		st.push_back({y, e[y]});
		e[x] += e[y];
		e[y] = x;
		return true;
	}

	//skip if no rollback
	int time() {return (int)st.size()};

	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
};
