vector<vector<pair<ll,ll>>> g;  // u->[(v,cost)]
vector<ll> dist;
int n; // be careful with redeclaration of n, works 0 indexed
void dijkstra(int x){
	dist.assign(n,-1);
	priority_queue<pair<ll,int> > q;
	dist[x]=0;
	q.push({0,x});
	while(!q.empty()){
		x=q.top().second;
		ll c=-q.top().first;
		q.pop();
		if(dist[x]!=c)continue;
		for(int i=0;i<g[x].size();i++){
			int y=g[x][i].first; 
			ll c=g[x][i].second;
			if(dist[y]<0||dist[x]+c<dist[y])
				dist[y]=dist[x]+c,q.push({-dist[y],y});
		}
	}
}

void solve(){
  g.assign(n,vector<pair<ll,ll>>());
}
