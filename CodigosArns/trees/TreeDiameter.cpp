pair<int, int> dfs(const vector<vector<int>> &tree, int node = 1,
  int previous = 0, int length = 0) {
	pair<int, int> max_path = {node, length};
	for (const int &i : tree[node]) {
		if (i == previous) { continue; }
		pair<int, int> other = dfs(tree, i, node, length + 1);
		if (other.second > max_path.second) { max_path = other; }
	}
	return max_path;
}
