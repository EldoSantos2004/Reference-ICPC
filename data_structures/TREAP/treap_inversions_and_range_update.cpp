#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;

const int mod = 998244353;

template<int MOD>
struct ModInt {
  ll v;
  ModInt(ll _v = 0) {v = (-MOD < _v && _v < MOD) ? _v : _v % MOD; if (v < 0) v += MOD;}
  ModInt& operator += (const ModInt &other) {v += other.v; if (v >= MOD) v -= MOD; return *this;}
  ModInt& operator -= (const ModInt &other) {v -= other.v; if (v < 0) v += MOD; return *this;}
  ModInt& operator *= (const ModInt &other) {v = v * other.v % MOD; return *this;}
  ModInt& operator /= (const ModInt &other) {return *this *= inverse(other);}
  bool operator == (const ModInt &other) const {return v == other.v;}
  bool operator != (const ModInt &other) const {return v != other.v;}
  friend ModInt operator + (ModInt a, const ModInt &b) {return a += b;}
  friend ModInt operator - (ModInt a, const ModInt &b) {return a -= b;}
  friend ModInt operator * (ModInt a, const ModInt &b) {return a *= b;}
  friend ModInt operator / (ModInt a, const ModInt &b) {return a /= b;}
  friend ModInt operator - (const ModInt &a) {return 0 - a;}
  friend ModInt power(ModInt a, ll b) {ModInt ret(1); while (b > 0) {if (b & 1) ret *= a; a *= a; b >>= 1;} return ret;}
  friend ModInt inverse(ModInt a) {return power(a, MOD - 2);}
  friend istream& operator >> (istream &is, ModInt &m) {is >> m.v; m.v = (-MOD < m.v && m.v < MOD) ? m.v : m.v % MOD; if (m.v < 0) m.v += MOD; return is;}
  friend ostream& operator << (ostream &os, const ModInt &m) {return os << m.v;}
};

struct Line{
  ModInt<mod> b = 1, c = 0;
  ModInt<mod> operator()(ModInt<mod> x){ return b * x + c;} 
  Line operator()(Line other) {return Line{b * other.b, other.c * b + c};}
  operator bool() const{
    return b != 1 || c != 0;
  };
};

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
	Node *l = 0, *r = 0;
	int y, c = 1;
  ModInt<mod> val, sum;
  Line line;
  bool rev = 0;
	Node(int val) : val(val), sum(val), y(rng()) {}
	void recalc();
  void push();
};
 
int cnt(Node* n) { return n ? n->c : 0; }
ModInt<mod> sum1(Node* n) { return n ? n->sum : ModInt<mod>(0); }
void Node::recalc() { if(l) l -> push(); if(r) r -> push(); c = cnt(l) + cnt(r) + 1; sum = sum1(l) + sum1(r) + val;}
void Node::push(){
  if(rev){
    rev = 0;
    swap(l, r);
    if(l) l -> rev ^= 1;
    if(r) r -> rev ^= 1;
  }
  if(line){
    val = line(val);
    sum = sum * line.b + line.c * c;
    if(l){
      l -> line = line(l -> line);
    }
    if(r){
      r -> line = line(r -> line);
    }
    line = {1, 0};
  }
}
 
template<class F> void each(Node* n, F f) {
	if (n) { n -> push(); each(n->l, f); f(n->val); each(n->r, f); }
}
 
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
  n -> push();
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}
 
Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
  l -> push();
  r -> push();
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}
 
Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}
 
void move(Node*& t, int l, int r, int k){
  Node *a, *b, *c;
  tie(a, b) = split(t, l); tie(b, c) = split(b, r - l);
  if(k <= l) t = merge(ins(a, b, k), c);
  else t = merge(a, ins(c, b, k - r));
}
 
void revv(Node*& t, int l, int r){
  Node *a, *b, *c;
  tie(a, b) = split(t, l); tie(b, c) = split(b, r - l);
  b -> rev ^= 1;
  t = merge(merge(a, b), c);
}
 
ModInt<mod> query(Node*& t, int l, int r){
  Node *a, *b, *c;
  tie(a, b) = split(t, l); tie(b, c) = split(b, r - l);
  ModInt<mod> res = sum1(b);
  t = merge(merge(a, b), c);
  return res;
}

void remove(Node*& t, int x){
  Node *a, *b, *c;
  tie(a, b) = split(t, x); tie(b, c) = split(b, 1);
  t = merge(a, c);
}

void update(Node*& t, int l, int r, ll X, ll Y){
  Node *a, *b, *c;
  tie(a, b) = split(t, l); tie(b, c) = split(b, r - l);
  b -> line = Line{X, Y}(b -> line);
  t = merge(a, merge(b, c));
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }
  Node* treap = nullptr;
  for(int i = 0; i < n; i++){
    treap = ins(treap, new Node(a[i]), i);
  }
  while(q--){
    int t; cin >> t;
    if(t == 0){
      int i, x; cin >> i >> x;
      treap = ins(treap, new Node(x), i);
    }
    else if(t == 1){
      int x; cin >> x;
      remove(treap, x);
    }
    else if(t == 2){
      int l, r; cin >> l >> r;
      revv(treap, l, r);
    }
    else if(t == 3){
      int l, r, b, c; cin >> l >> r >> b >> c;
      update(treap, l, r, b, c);
    }
    else{
      int l, r; cin >> l >> r;
      cout << query(treap, l, r) << endl;
    }
  }
}
