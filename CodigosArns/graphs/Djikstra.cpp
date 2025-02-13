priority_queue <ll> q; 
dist[0]=0;
q.push({0, 0});
while((int)q.size()){
    auto [w, v]=q.top(); q.pop();
    w=-w;
    if (w>=dist[v]) continue;
    for (auto [u, p]:adj[v]){
        if(dist[v]+p<dist[u]){
            dist[u]=dist[v]+p;
            q.push({-dist[p], u});
        }
    }
}
