vector<vector<int>> adj,adjr;
vector<bool> vis;
vector<int> order,comp;
void dfs(int a){
  vis[a]=1;
  for(auto u:adj[a]){
    if(!vis[u]){
      dfs(u);
    }
  }
  order.pb(a);
}
void dfsr(int a,int k){
  vis[a]=1;
  comp[a]=k;
  for(auto u:adjr[a]){
    if(!vis[u]){
      dfsr(u,k);
    }
  }
}

void solve() {
  int n,m;cin>>n>>m;
  adj.assing(n,vector<int>());
  adjr.assing(n,vector<int>());
  comp.resize(n);
  for(int i=0;i<m;i++){
    int a,b;cin>>a>>b;a--;b--;
    adj[a].pb(b);
    adjr[b].pb(a);
  }
  vis.assign(n,0);
  for(int i=0;i<n;i++){
    if(!vis[i])dfs(i);
  }
  vis.assign(n,0);
  int c=0;
  for(int i=n-1;i>=0;i--){
    if(!vis[order[i]]){
      dfsr(order[i],c);
      c++;
    }
  }

}