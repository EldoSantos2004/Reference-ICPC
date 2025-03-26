vector <tuple <ll, ll, ll>> edges(m);
for(int i = 0; i < m; i++){
  ll a, b, c; cin >> a >> b >> c;
  edges[i] ={a, b, c};
}

ll distance[n + 1];
for(int i = 0; i <= n; i++) distance[i] = INF;
distance[1] = 0;
for(int i = 1; i <= n - 1; i++){
  bool change = false;
  for(auto e: edges){
    ll a, b, w;
    tie(a, b, w) = e;
    ll temp = distance[b];
    distance[b] = min(distance[b], distance[a] + w);
    if(temp != distance[b]) change = true;
  }
  if(!change) break;
}