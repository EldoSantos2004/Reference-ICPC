vector<pair<int, int>> antipodalPairs(vector<point> & P){
	vector<pair<int, int>> ans;
	int n = P.size(), k = 1;
	auto f = [&](int u, int v, int w){return abs((P[v%n]-P[u%n]).cross(P[w%n]-P[u%n]));};
	while(ge(f(n-1, 0, k+1), f(n-1, 0, k))) ++k;
	for(int i = 0, j = k; i <= k && j < n; ++i){
		ans.emplace_back(i, j);
		while(j < n-1 && ge(f(i, i+1, j+1), f(i, i+1, j)))
			ans.emplace_back(i, ++j);
	}
	return ans;
}