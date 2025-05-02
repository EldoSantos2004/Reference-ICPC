/*
																	Centroid Decomposition
  --------------------------------------------------------------------------------------------
  Finds the centroid decomposition of a given tree. 
	Any vertex can have at most log n centroid ancestors

	The code below is the solution to Xenia and tree.
	Given tree, queries of two types:
	1) u - color vertex u
	2) v - print minimum distance of vertex v to any colored vertex before


  Time Complexity: O(n log n)
  Space Complexity: O(n log n)
*/
const int MAXN=200005;

vector<int> adj[MAXN];
vector<bool> is_removed(MAXN, false);
vector<int> subtree_size(MAXN, 0);
vector<int> dis(MAXN, 1e9);
vector<vector<pair<int, int>>> ancestor(MAXN);
 
int get_subtree_size(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		subtree_size[node] += get_subtree_size(child, node);
	}
	return subtree_size[node];
}
 
int get_centroid(int node, int tree_size, int parent = -1) {
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		if (subtree_size[child] * 2 > tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}
 
void getDist(int cur, int centroid, int p=-1, int dist=1){
    for (int child:adj[cur]){
        if(child==p ||is_removed[child])
            continue;
        dist++;
        getDist(child, centroid, cur, dist);
        dist--;
    }
    ancestor[cur].push_back(make_pair(centroid, dist));
}
 
void update(int cur){
    for (int i=0;i<ancestor[cur].size();i++){
        dis[ancestor[cur][i].first]=min(dis[ancestor[cur][i].first], ancestor[cur][i].second);
    }
    dis[cur]=0;
}
 
int query(int cur){
    int mini=dis[cur];
    for (int i=0;i<ancestor[cur].size();i++){
       mini=min(mini, ancestor[cur][i].second+dis[ancestor[cur][i].first]);
    }
    return mini;
}
 
void build_centroid_decomp(int node = 1) {
	int centroid = get_centroid(node, get_subtree_size(node));
	
	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		getDist(child, centroid, centroid);
	}
 
	is_removed[centroid] = true;
 
	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}
