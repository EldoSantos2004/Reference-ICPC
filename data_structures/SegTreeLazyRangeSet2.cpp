#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct sum_t {
  ll val;
  static const ll null_v = 0;
  sum_t(): val(null_v) {}
  sum_t(ll v): val(v) {}
  sum_t op(sum_t& other) {
    return sum_t(val + other.val);
  }
  sum_t lazy_op(sum_t& v, int size) {
    return v.val * size;
  }
  sum_t lazy_op1(sum_t& v, int size) {
    return val + v.val * size;
  }
};

template <typename num_t> 
struct segtree {
  int n;
  vector<num_t> tree, lazy, lazy1;

  void init(int s) {
    n = s;
    tree.assign(4 * n, num_t(0));
    lazy.assign(4 * n, num_t(-1));
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

  void update(int l, int r, num_t v) {
    if (l > r) return;
    update(0, 0, n - 1, l, r, v);
  }

  num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
    eval_lazy(i, tl, tr);

    if (tr < ql || qr < tl) return tree[i]; 
    if (ql <= tl && tr <= qr) {
      lazy[i].val = v.val;
      lazy1[i].val = 0;
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  void update1(int l, int r, num_t v) {
    if (l > r) return;
    update1(0, 0, n - 1, l, r, v);
  }

  num_t update1(int i, int tl, int tr, int ql, int qr, num_t v) {

    if (tr < ql || qr < tl){
      eval_lazy(i, tl, tr);
      return tree[i]; 
    }
    if (ql <= tl && tr <= qr) {
      lazy1[i].val += v.val;
      if(lazy[i].val != -1){
        lazy[i].val += lazy1[i].val;
        lazy1[i].val = 0;
      }
      eval_lazy(i, tl, tr);
      return tree[i];
    }

    eval_lazy(i, tl, tr);
    int mid = (tl + tr) / 2;
    num_t a = update1(2 * i + 1, tl, mid, ql, qr, v);
    num_t b = update1(2 * i + 2, mid + 1, tr, ql, qr, v);
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
    if(lazy[i].val != -1){
      tree[i] = tree[i].lazy_op(lazy[i], r - l + 1);
      if (l != r) {
        lazy[2 * i + 1].val = lazy[i].val;
        lazy[2 * i + 2].val = lazy[i].val;
        lazy1[2 * i + 1].val = lazy1[2 * i + 2].val = 0;
      }
      lazy[i] = num_t(-1); 
      lazy1[i] = num_t(0);
    }
    else{
      tree[i] = tree[i].lazy_op1(lazy1[i], r - l + 1);
      if(l != r){
        if(lazy[2 * i + 1].val == -1) lazy1[2 * i + 1].val += lazy1[i].val;
        else{
          lazy[2 * i + 1].val += lazy1[i].val + lazy1[2 * i + 1].val;
          lazy1[2 * i + 1].val = 0;
        }
        if(lazy[2 * i + 2].val == -1) lazy1[2 * i + 2].val += lazy1[i].val;
        else{
          lazy[2 * i + 2].val += lazy1[i].val + lazy1[2 * i + 2].val;
          lazy1[2 * i + 2].val = 0;
        }
      }
      lazy1[i] = num_t(0);
    }
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
      int l, r, x; cin >> l >> r >> x;
      r--;
      st.update(l, r, x);
    }
    else if(t == 2){
      int l, r, x; cin >> l >> r >> x;
      r--;
      st.update1(l, r, x);
    }
    else{
      int l, r; cin >> l >> r;
      r--;
      cout << st.query(l, r).val << endl;
    }
  }
}
