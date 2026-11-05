struct PartitionMatroid {
	vector<int> cap, cat, used;
	PartitionMatroid(const vector<int> &cap, const vector<int> &cat)
	    : cap(cap), cat(cat), used(size(cap)) {}
	void clear() { fill(begin(used), end(used), 0); }
	bool check(int x) { return used[cat[x]] < cap[cat[x]]; }
	void add(int x) { used[cat[x]]++; }
	void precomp() {}
};