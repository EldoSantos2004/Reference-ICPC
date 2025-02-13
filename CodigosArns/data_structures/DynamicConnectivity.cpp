#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU {
	vector<int> e;
	vector<pair<int, int>> st;
	int cnt;

  DSU(){}

	DSU(int N) : e(N, -1), cnt(N) {}

	int get(int x) { return e[x] < 0 ? x : get(e[x]);}

	bool connected(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) { return false; }
		if (e[x] > e[y]) { swap(x, y); }
		st.push_back({x, e[x]});
		st.push_back({y, e[y]});
		e[x] += e[y];
		e[y] = x;
		cnt--;
		return true;
	}

	void rollback(){
    auto [x, y]=st.back();
    st.pop_back();
		e[x] = y;
		auto [a, b]=st.back();
		st.pop_back();
		e[a]=b;
		cnt++;
	}
};

struct query {
  int v, u;
  bool united;
  query(int _v, int _u) : v(_v), u(_u) {}
};

struct QueryTree {
  vector<vector<query>> t;
  DSU dsu;
  int T;
  
  QueryTree(){}

  QueryTree(int _T, int n) : T(_T) {
    dsu = DSU(n);
    t.resize(4 * T + 4);
  }

  void add(int v, int l, int r, int ul, int ur, query& q) {
    if (ul > ur)
      return;
    if (l == ul && r == ur) {
      t[v].push_back(q);
      return;
    }
    int mid = (l + r) / 2;
    add(2 * v, l, mid, ul, min(ur, mid), q);
    add(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
  }

  void add_query(query q, int l, int r) {
    add(1, 0, T - 1, l, r, q);
  }

  void dfs(int v, int l, int r, vector<int>& ans) {
    for (query& q : t[v]) {
      q.united = dsu.unite(q.v, q.u);
    }
    if (l == r)
      ans[l] = dsu.cnt;
    else {
      int mid = (l + r) / 2;
      dfs(2 * v, l, mid, ans);
      dfs(2 * v + 1, mid + 1, r, ans);
    }
    for (query q : t[v]) {
      if (q.united)
        dsu.rollback();
    }
  }
};


int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  //freopen("connect.in", "r", stdin);
  //freopen("connect.out", "w", stdout);
  int n, k; cin >> n >> k;
  if(k==0) return 0;
  QueryTree st=QueryTree(k, n);
  map<pair<int, int>, int> mp;
  vector<int> ans(k), q;
  for(int i=0;i<k;i++){
    char c; cin >> c;
    if(c=='?'){
      q.push_back(i);
      continue;
    }
    int u, v; cin >> u >> v;
    u--; v--;
    if(u>v) swap(u, v);
    if(c=='+'){
      mp[{u, v}]=i;
    }
    else{
      st.add_query(query(u, v), mp[{u, v}], i);
      mp[{u, v}]=-1;
    }
  }
  for(auto [x, y]:mp){
    if(y!=-1){
      st.add_query(query(x.first, x.second), y, k-1);
    }
  }
  st.dfs(1, 0, k-1, ans);
  for(int x:q){
    cout << ans[x] << endl;
  }
}
