const int MAXN=100005;
vector<int> adj[MAXN];
vector<int> adj1[MAXN];
int comp[MAXN];
bool vis[MAXN];
vector<int> order;
int component=0;

void dfs(int cur){
  vis[cur]=1;
  for (int x: adj[cur]){
    if(!vis[x]){
      dfs(x);
    }
  }
  order.push_back(cur);
}
 
void dfs1(int cur){
  vis[cur]=1;
  comp[cur]=component;
  for (int x: adj1[cur]){
    if(!vis[x]){
      dfs1(x);
    }
  }
}
