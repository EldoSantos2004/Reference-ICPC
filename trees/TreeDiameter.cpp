/*
                            	Tree Diameter
  --------------------------------------------------------------------------------------------
  Finds the vertex most distant to vertex on which function is called.
	
	The first value is the vertex itself and the second value is the distance.
	
	To find diameter run algorithm twice, first on random vertex and then on the vertex that is farthest away.

	The vertex that is the farthest away from any vertex in tree must be an endpoint of the diameter.

  Time Complexity: O(n)
  Space Complexity: O(n)
*/

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
