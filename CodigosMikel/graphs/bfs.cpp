queue<int> q;
q.push(x);
vis[x]=1;
dis[x]=0;
while(!q.empty()){
  int s=q.front();
  q.pop();
  for(auto u:adj[s]){
    if(!vis[u]){
      vis[u]=1;
      dis[u]=dis[s]+1;
      q.push(u);
    }
  }
}