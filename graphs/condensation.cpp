//after scc
vector<vector<int>> adj_scc;

void cndstn(int c){
  adj_scc.assign(c,vector<int>());
  for(ll i=0;i<n;i++){
    for(auto u:adj[i]){
      if(comp[u]!=comp[i]){
        adj_scc[comp[i]].pb(comp[u]);
      }
    }
  }
}