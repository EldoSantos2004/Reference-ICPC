const ll inf = 2e18;

struct Line {
  ll m, c;
  ll eval(ll x) {
    return m * x + c;
  }
};
struct node {
  Line line;
  node* left = nullptr;
  node* right = nullptr;
  node(Line line) : line(line) {}
  void add_segment(Line nw, int l, int r, int L, int R) {
    if (l > r || r < L || l > R) return;
    int m = (l + 1 == r ? l : (l + r) / 2);
    if (l >= L and r <= R) {
      bool lef = nw.eval(l) < line.eval(l);
      bool mid = nw.eval(m) < line.eval(m);
      if (mid) swap(line, nw);
      if (l == r) return;
      if (lef != mid) {
        if (left == nullptr) left = new node(nw);
        else left -> add_segment(nw, l, m, L, R);
      }
      else {
        if (right == nullptr) right = new node(nw);
        else right -> add_segment(nw, m + 1, r, L, R);
      }
      return;
    }
    if (max(l, L) <= min(m, R)) {
      if (left == nullptr) left = new node({0, inf});
      left -> add_segment(nw, l, m, L, R);
    }
    if (max(m + 1, L) <= min(r, R)) {
      if (right == nullptr) right = new node ({0, inf});
      right -> add_segment(nw, m + 1, r, L, R);
    }
  }
  ll query_segment(ll x, int l, int r, int L, int R) {
    if (l > r || r < L || l > R) return inf;
    int m = (l + 1 == r ? l : (l + r) / 2);
    if (l >= L and r <= R) {
      ll ans = line.eval(x);
      if (l < r) {
        if (x <= m && left != nullptr) ans = min(ans, left -> query_segment(x, l, m, L, R));
        if (x > m && right != nullptr) ans = min(ans, right -> query_segment(x, m + 1, r, L, R));
      }
      return ans;
    }
    ll ans = inf;
    if (max(l, L) <= min(m, R)) {
      if (left == nullptr) left = new node({0, inf});
      ans = min(ans, left -> query_segment(x, l, m, L, R));
    }
    if (max(m + 1, L) <= min(r, R)) {
      if (right == nullptr) right = new node ({0, inf});
      ans = min(ans, right -> query_segment(x, m + 1, r, L, R));
    }
    return ans;
  }
};

struct LiChaoTree {
  int L, R;
  node* root;
  LiChaoTree() : L(numeric_limits<int>::min() / 2), R(numeric_limits<int>::max() / 2), root(nullptr) {}
  LiChaoTree(int L, int R) : L(L), R(R) {
    root = new node({0, inf});
  }
  void add_line(Line line) {
    root -> add_segment(line, L, R, L, R);
  }
  // y = mx + b: x in [l, r]
  void add_segment(Line line, int l, int r) {
    root -> add_segment(line, L, R, l, r);
  }
  ll query(ll x) {
    return root -> query_segment(x, L, R, L, R);
  }
  ll query_segment(ll x, int l, int r) {
    return root -> query_segment(x, l, r, L, R);
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  LiChaoTree t = LiChaoTree((int)-1e9, (int) 1e9);
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++) {
    ll l, r, a, b; cin >> l >> r >> a >> b;
    r--;
    t.add_segment({a, b}, l, r);
  }
  while (q--) {
    int ty; cin >> ty;
    if (ty == 0) {
      ll l, r, a, b; cin >> l >> r >> a >> b;
      r--;
      t.add_segment({a, b}, l, r);
    }
    else {
      ll x; cin >> x;
      ll ans = t.query(x);
      if (ans >= inf) cout << "INFINITY\n";
      else cout << ans << '\n';
    }
  }
}


// min of a * x^3 + b * x ^2 + c * x + d

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const int C = (int)1e5 + 5;
const int T = 10;
const int M = 350; // sqrt(10^5)
const ll inf = (ll)1e19;

namespace segtree {
  struct Poly {
    ll a, b, c, d = inf;
    ll operator()(ll x) { return a * x * x * x + b * x * x + c * x + d; }
  } a[T][C * 4];
  int t = -1;

  void insert(int l, int r, Poly poly, int o=0) {
    if(l + 1 == r) {
      if(poly(l) < a[t][o](l)) a[t][o] = poly;
      return;
    }
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    bool b1 = poly(mid) < a[t][o](mid), b2 = poly(l) < a[t][o](l);
    if(b1) swap(poly, a[t][o]);
    if(b1 != b2) insert(l, mid, poly, lson);
    else insert(mid, r, poly, rson);
  }
  ll query(int l, int r, int x, int o=0) {
    if(l + 1 == r) return a[t][o](x);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(x < mid) return min(a[t][o](x), query(l, mid, x, lson));
    else return min(a[t][o](x), query(mid, r, x, rson));
  }
}

ll ans[M];

void init() {
  int n; cin >> n;
  fill(ans, ans + M, inf);
  segtree::t++;
  while(n--) {
    int a, b, c, d; cin >> d >> c >> b >> a;
    segtree::Poly p = {a, b, c, d};
    segtree::insert(M, C, p);
    for(int i = 0 ; i < M ; ++i) ans[i] = min(ans[i], p(i));
  }
}
void solve() {
  int q; cin >> q;
  while(q--) {
    int x; cin >> x;
    if(x < M) cout << ans[x] << '\n';
    else cout << segtree::query(M, C, x) << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}

