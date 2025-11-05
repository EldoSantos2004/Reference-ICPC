// adds d * (i - l + 1) + a to range [l, r]
// d * (i - l + 1) = d*(1-l) + d*i
// Sum = A x segment_length + B x sum_of_indices_in_segment 

struct sum_t {
  ll val;
  static const ll null_v = 0;
  sum_t(): val(null_v) {}
  sum_t(ll v): val(v) {}
  sum_t op(sum_t& other) {
    return sum_t(val + other.val);
  }
  sum_t lazy_op(sum_t& v, int size) {
    return val + v.val * size;
  }
  sum_t lazy_op(sum_t& v, ll l, ll r) {
    return val + v.val * ((l + r) * (r - l + 1)) / 2;
  }
};

template <typename num_t> 
struct segtree {
  int n;
  vector<num_t> tree, lazy, lazy1;

  void init(int s) {
    n = s;
    tree.assign(4 * n, num_t(0));
    lazy.assign(4 * n, num_t(0));
    lazy1.assign(4 * n, num_t(0));
    init(0, 0, n - 1);
  }

  num_t init(int i, int l, int r) {
    if (l == r) return tree[i] = num_t(0);

    int mid = (l + r) / 2;
    num_t left = init(2 * i + 1, l, mid);
    num_t right = init(2 * i + 2, mid + 1, r);
    return tree[i] = left.op(right);
  }

  // do -l if you want it to add 0 to l. adds d * (i - l + 1) + a to range [l, r]
  void update(int l, int r, ll d, ll a) {
    if (l > r) return;
    ll dd = d;
    d = (1 - l) * d + a;
    a = dd;
    update(0, 0, n - 1, l, r, d, a);
  }

  num_t update(int i, int tl, int tr, int ql, int qr, ll D, ll A) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl) return tree[i]; 
    if (ql <= tl && tr <= qr) {
      lazy[i].val += D;
      lazy1[i].val += A;
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, D, A);
    num_t b = update(2 * i + 2, mid + 1, tr, ql, qr, D, A);
    return tree[i] = a.op(b);
  }

  num_t query(int l, int r) {
    if (l > r) return num_t::null_v;
    return query(0, 0, n - 1, l, r);
  }

  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr) return tree[i]; 
    if (tr < ql || qr < tl) return num_t::null_v; 

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr);
    num_t b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  void eval_lazy(int i, int l, int r) {
    tree[i] = tree[i].lazy_op(lazy1[i], l, r);
    tree[i] = tree[i].lazy_op(lazy[i], r - l + 1);
    if (l != r) {
      lazy[2 * i + 1].val += lazy[i].val;
      lazy[2 * i + 2].val += lazy[i].val;
      lazy1[2 * i + 1].val += lazy1[i].val;
      lazy1[2 * i + 2].val += lazy1[i].val;
    }
    lazy[i] = lazy1[i] = num_t(0); 
  }
};

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  segtree <sum_t> st;
  st.init(n);
  while(q--){
    int t; cin >> t;
    if(t == 1){
      int l, r, a, d; cin >> l >> r >> a >> d;
      l--; r--;
      st.update(l, r, d, a);
    }
    else{
      int l; cin >> l;
      l--;
      cout << st.query(l, l).val << endl;
    }
  }
}
