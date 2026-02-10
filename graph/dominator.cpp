vector<vector<int>> dominator(const vector<vector<int>>& adj){
  int n = sz(adj);
  vector<vector<int>> buck(n), R(n), tree(n);
  vector<int> P(n, -1), rev(n), L(n), DSU(n), pre(n), sdom(n), idom(n);
  int timer = 0;
 
  auto dfs = [&](auto &&self, int cur) -> void{
    P[cur] = timer, rev[timer] = cur, L[timer] = timer, DSU[timer] = timer, sdom[timer] = timer;
    timer++;
    for(int x : adj[cur]){
      if(P[x] == -1){
        self(self, x);
        pre[P[x]] = P[cur];
      }
      R[P[x]].push_back(P[cur]);
    }
  };
 
  auto find = [&](auto &&self, int u, int x = 0) -> int{
    if(DSU[u] == u) return x? -1 : u;
    int v = self(self, DSU[u], x + 1);
    if(v < 0) return u;
    if(sdom[L[DSU[u]]] < sdom[L[u]]) L[u] = L[DSU[u]];
    DSU[u] = v;
    return x? v : L[u];
  };
 
  auto merge = [&](int u, int v) -> void{
    DSU[v] = u;
  };
 
  dfs(dfs, 0);
 
  int w;
  for(int i = n - 1; i >= 0; i--){
    for(int v : R[i]){
      sdom[i] = min(sdom[i], sdom[find(find, v)]);
    }
    if(i > 1) buck[sdom[i]].push_back(i);
    for(int v : buck[i]){
      w = find(find, v);
      if(sdom[v] == sdom[w]) idom[v] = sdom[v];
      else idom[v] = w;
    }
    merge(pre[i], i);
  }
 
  for(int i = 1; i < n; i++){
    if(idom[i] != sdom[i]) idom[i] = idom[idom[i]];
    tree[rev[i]].push_back(rev[idom[i]]);
		tree[rev[idom[i]]].push_back(rev[i]);
  }
 
  return tree;
}
 
