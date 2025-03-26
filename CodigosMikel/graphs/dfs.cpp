vector<vector<int>> adj;
vector<bool> vis;
void dfs(int a){
  vis[a]=1;
  for(auto u:adj[a]){
    if(!vis[u]){
      dfs(u);
    }
  }
}

//inside solve()

adj.assign(n,vector<int>());
vis.assign(n,0);