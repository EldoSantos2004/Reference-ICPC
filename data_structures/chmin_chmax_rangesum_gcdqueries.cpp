// Segment tree for chmin, chmax, add and query sum.
// Complexity is O (n (log n) ^ 2)

// Range chmin (l, r, v) -> a[l], ...., a[r] = min(a[i], v) call update with 1
// Range chmax (l, r, v) -> a[l], ...., a[r] = max(a[i], v) call update with 2
// Range set (l, r, v) -> a[l], ...., a[r] = v call update with 3 (this calls chmax and chmin on the interval)
// Range add (l, r, v) -> a[l], ...., a[r] += v call update with 4
// You can obtain sum, max, min, gcd in segment

typedef long long ll;

const ll inf = 1e17;

ll gcd(ll a, ll b){
  a = abs(a);
  b = abs(b);
  if(a == 0) return b;
  return gcd(b % a, a);
}

struct sum_t {
  ll sum, mx, mx2, cnt_mx, mn, mn2, cnt_mn, gcd_no_max_no_min;
  static const ll null_v = 0;
  sum_t(): sum(null_v), mx(-inf), mx2(-inf), cnt_mx(0), mn(inf), mn2(inf), cnt_mn(0), gcd_no_max_no_min(0) {}
  sum_t(ll v): sum(v), mx(v), mx2(-inf), cnt_mx(1), mn(v), mn2(inf), cnt_mn(1), gcd_no_max_no_min(0) {}
  sum_t(ll _sum, ll _mx, ll _mx2, ll _cnt_mx, ll _mn, ll _mn2, ll _cnt_mn, ll _gcd_no_max_no_min): 
    sum(_sum), mx(_mx), mx2(_mx2), cnt_mx(_cnt_mx), mn(_mn), mn2(_mn2), cnt_mn(_cnt_mn), gcd_no_max_no_min(_gcd_no_max_no_min) {}
  sum_t op(sum_t& other) {
    sum_t res;
    res.sum = sum + other.sum;
    res.gcd_no_max_no_min = gcd(gcd_no_max_no_min, other.gcd_no_max_no_min);

    if(mx == other.mx){
      res.mx = mx;
      res.cnt_mx = cnt_mx + other.cnt_mx;
      res.mx2 = max(mx2, other.mx2);
    }
    else if(mx > other.mx){
      res.mx = mx;
      res.cnt_mx = cnt_mx;
      res.mx2 = max(mx2, other.mx);      
    }
    else{
      res.mx = other.mx;
      res.cnt_mx = other.cnt_mx;
      res.mx2 = max(mx, other.mx2); 
    }

    if(mn == other.mn){
      res.mn = mn;
      res.cnt_mn = cnt_mn + other.cnt_mn;
      res.mn2 = min(mn2, other.mn2);
    }
    else if(mn < other.mn){
      res.mn = mn;
      res.cnt_mn = cnt_mn;
      res.mn2 = min(mn2, other.mn);
    }
    else{
      res.mn = other.mn;
      res.cnt_mn = other.cnt_mn;
      res.mn2 = min(mn, other.mn2);
    }

    if(mx2 != -inf && mx2 != mn && other.mx2 != -inf && other.mx2 != other.mn){
      res.gcd_no_max_no_min = gcd(res.gcd_no_max_no_min, mx2 - other.mx2);
    }

    ll any = -1;

    if(mx2 != -inf && mx2 != mn) any = mx2;
    if(other.mx2 != -inf && other.mx2 != other.mn) any = other.mx2;

    vector<ll> diff_max_min = {mx, mn, other.mx, other.mn};
    for(ll val: diff_max_min){
      if(val != res.mn && val != res.mx){
        if(any != -1) res.gcd_no_max_no_min = gcd(res.gcd_no_max_no_min, val - any);
        else any = val;
      }
    }
    
    return res;
  }
};

template <typename num_t> 
struct segtree {
  int n;
  vector<num_t> tree, lazy;

  void init(int s, const vector<ll> &A) {
    n = s;
    tree.assign(4 * n, num_t());
    lazy.assign(4 * n, num_t());
    init(0, 0, n - 1, A);
  }

  num_t init(int i, int l, int r, const vector<ll> &A) {
    if (l == r) return tree[i] = num_t(A[l]);

    int mid = (l + r) / 2;
    num_t left = init(2 * i + 1, l, mid, A);
    num_t right = init(2 * i + 2, mid + 1, r, A);
    return tree[i] = left.op(right);
  }

  // update 3 is setting values to v
  void update(int l, int r, ll v, int op) {
    if (l > r) return;
    if(op == 1){
      update_chmin(0, 0, n - 1, l, r, v);
    }
    if(op == 2){
      update_chmax(0, 0, n - 1, l, r, v);
    }
    if(op == 3){
      update_chmin(0, 0, n - 1, l, r, v);
      update_chmax(0, 0, n - 1, l, r, v);
    }
    if(op == 4){
      update_add(0, 0, n - 1, l, r, v);
    }
  }

  num_t update_chmin(int i, int tl, int tr, int ql, int qr, ll v) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl || tree[i].mx <= v) return tree[i]; 
    if (ql <= tl && tr <= qr && tree[i].mx2 < v) {
      push_min(i, v);
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update_chmin(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update_chmin(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t update_chmax(int i, int tl, int tr, int ql, int qr, ll v) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl || tree[i].mn >= v) return tree[i]; 
    if (ql <= tl && tr <= qr && tree[i].mn2 > v) {
      push_max(i, v);
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update_chmax(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update_chmax(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t update_add(int i, int tl, int tr, int ql, int qr, ll v) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl) return tree[i]; 
    if (ql <= tl && tr <= qr) {
      push_add(i, tl, tr, v);
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update_add(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update_add(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t query(int l, int r){
    if (l > r) return num_t();
    return query(0, 0, n - 1, l , r);
  }

  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr) return tree[i]; 
    if (tr < ql || qr < tl) return num_t();

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr);
    num_t b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  ll query_gcd(int l, int r){
    if(l > r) return 0;
    return query_gcd(0, 0, n - 1, l, r);
  }

  ll query_gcd(int i, int tl, int tr, int ql, int qr){
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr){
      ll res = gcd(tree[i].mx, tree[i].gcd_no_max_no_min);
      if(tree[i].mn2 != inf) res = gcd(res, tree[i].mn2 - tree[i].mn);
      if(tree[i].mx2 != -inf) res = gcd(res, tree[i].mx - tree[i].mx2);
      return res;
    }
    if (tr < ql || qr < tl) return 0;

    int mid = (tl + tr) / 2;
    ll a = query_gcd(2 * i + 1, tl, mid, ql, qr);
    ll b = query_gcd(2 * i + 2, mid + 1, tr, ql, qr);
    return gcd(a, b);
  }

  void eval_lazy(int i, int l, int r) {
    if (l != r) {
      int mid = (l + r) / 2;

      push_add(2 * i + 1, l, mid, lazy[i].sum);
      push_add(2 * i + 2, mid + 1, r, lazy[i].sum);

      push_min(2 * i + 1, tree[i].mx);
      push_min(2 * i + 2, tree[i].mx);

      push_max(2 * i + 1, tree[i].mn);
      push_max(2 * i + 2, tree[i].mn);

    }
    lazy[i] = num_t(); 
  }

  void push_add(int i, int l, int r, ll v){
    if(v == 0) return;
    tree[i].mx += v;
    tree[i].sum += v * (r - l + 1);
    tree[i].mx2 += (tree[i].mx2 == -inf ? 0 : v);
    tree[i].mn += v;
    tree[i].mn2 += (tree[i].mn2 == inf ? 0 : v);
    lazy[i].sum += v;
  }

  void push_min(int i, ll v){
    if (tree[i].mx <= v) return;
    if(tree[i].mn == tree[i].mx){
      tree[i].mn = v;
    }
    else if(tree[i].mn2 == tree[i].mx){
      tree[i].mn2 = v;
    }
    tree[i].sum -= tree[i].mx * tree[i].cnt_mx;
    tree[i].mx = v;
    tree[i].sum += tree[i].mx * tree[i].cnt_mx;
  }

  void push_max(int i, ll v){
    if (tree[i].mn >= v) return;
    if(tree[i].mx == tree[i].mn){
      tree[i].mx = v;
    }
    else if(tree[i].mx2 == tree[i].mn){
      tree[i].mx2 = v;
    }
    tree[i].sum -= tree[i].mn * tree[i].cnt_mn;
    tree[i].mn = v;
    tree[i].sum += tree[i].mn * tree[i].cnt_mn;
  }
};

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<ll> A(n);
  for(int i = 0; i < n; i++) cin >> A[i];
  segtree <sum_t> st;
  st.init(n, A);
  int q; cin >> q;
  while(q--){
    int t, l, r; cin >> t >> l >> r;
    l--; r--;
    if(t < 5){
      ll x; cin >> x;
      st.update(l, r, x, t);
    }
    else{
      if(t == 8){
        cout << st.query_gcd(l, r) << endl;
      }
      else{
        auto ans = st.query(l, r);
        if(t == 5) cout << ans.sum << endl;
        else if (t == 6) cout << ans.mn << endl;
        else if(t == 7) cout << ans.mx << endl;
      }
    }
  }
}
