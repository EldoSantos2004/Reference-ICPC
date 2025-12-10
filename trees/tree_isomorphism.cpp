// Code to check if two trees are isomorphic (any root)
// Currently uses two moduli, can add an extra one to reduce collision probability

mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const int mod = 1e9 + 9;
const int mod1 = 2013265921;

void solve(){
  int n; cin >> n;
  vector<vector<vector<int>>> adj(2, vector<vector<int>>(n));
  for(int ii = 0; ii < 2; ii++){
    for(int i = 0; i < n - 1; i++){
      int u, v; cin >> u >> v;
      u--; v--;
      adj[ii][u].push_back(v);
      adj[ii][v].push_back(u);
    }
  }
  uniform_int_distribution<int> rng(0, numeric_limits<int>::max());
  vector<int> h(n, 1);
  vector<vector<int>> d(2, vector<int>(n, 0));
  vector<vector<ModInt<mod>>> val(2, vector<ModInt<mod>>(n));
  vector<vector<ModInt<mod1>>> val1(2, vector<ModInt<mod1>>(n));
  for(int i = 1; i < n; i++){
    h[i] = rng(mt);
  }
  auto dfs = [&](auto &&self, int cur, int p, int which) -> void{
    val[which][cur] = 1;
    val1[which][cur] = 1;
    for(int x: adj[which][cur]){
      if(x == p) continue;
      self(self, x, cur, which);
      d[which][cur] = max(d[which][cur], d[which][x] + 1);
    }
    for(int x: adj[which][cur]){
      if(x == p) continue;
      val[which][cur] *= (val[which][x] + h[d[which][cur]]);
      val1[which][cur] *= (val1[which][x] + h[d[which][cur]]);
    }
  };
  vector<set<array<ll, 2>>> st(2);
  auto dfs1 = [&](auto &&self, int cur, int p, int which) -> void{
    int mx = 0, mx1 = 0;
    ModInt<mod> with_mx = 1, with_mx1 = 1;
    ModInt<mod1> with_mx_mod1 = 1, with_mx1_mod1 = 1;
    for(int x: adj[which][cur]){
      if(d[which][x] + 1 > mx){
        mx1 = mx;
        mx = d[which][x] + 1;
      }
      else if(d[which][x] + 1 == mx){
        mx1 = mx;
      }
      else if(d[which][x] + 1 > mx1){
        mx1 = d[which][x] + 1;
      }
    }
    for(int x: adj[which][cur]){
      with_mx *= (val[which][x] + h[mx]);
      with_mx1 *= (val[which][x] + h[mx1]);
      with_mx_mod1 *= (val1[which][x] + h[mx]);
      with_mx1_mod1 *= (val1[which][x] + h[mx1]);
    }
    st[which].insert({with_mx.v, with_mx_mod1.v});
    vector<int> pre(sz(adj[which][cur]), 0), suf(sz(adj[which][cur]), 0);
    for(int i = 0; i < sz(adj[which][cur]); i++){
      if(adj[which][cur][i] != p) pre[i] = d[which][adj[which][cur][i]];
      if(i) pre[i] = max(pre[i], pre[i - 1]);
    }
    for(int i = sz(adj[which][cur]) - 1; i >= 0; i--){
      if(adj[which][cur][i] != p) suf[i] = d[which][adj[which][cur][i]];
      if(i < sz(adj[which][cur]) - 1) suf[i] = max(suf[i], suf[i + 1]);
    }
    for(int i = 0; i < sz(adj[which][cur]); i++){
      if(adj[which][cur][i] == p) continue;
      int cur_mx = max((i ? pre[i - 1] : 0), (i < sz(adj[which][cur]) - 1 ? suf[i + 1]: 0)); 
      if(cur_mx == mx){
        d[which][cur] = mx;
        val[which][cur] = with_mx / (val[which][adj[which][cur][i]] + h[mx]);
        val1[which][cur] = with_mx_mod1 / (val1[which][adj[which][cur][i]] + h[mx]);
      }
      else{
        d[which][cur] = mx1;
        val[which][cur] = with_mx1 / (val[which][adj[which][cur][i]] + h[mx1]);
        val1[which][cur] = with_mx1_mod1 / (val1[which][adj[which][cur][i]] + h[mx1]);
      }
      self(self, adj[which][cur][i], cur, which);
    }
  };
  dfs(dfs, 0, -1, 0);
  dfs(dfs, 0, -1, 1);
  dfs1(dfs1, 0, -1, 0);
  dfs1(dfs1, 0, -1, 1);
  for(auto x: st[0]){
    if(st[1].count(x)){
      cout << "YES" << endl;
      return;
    }
  }
  cout << "NO" << endl;
}
