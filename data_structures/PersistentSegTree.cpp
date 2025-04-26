struct Node {
	ll val;
	Node *l, *r;
 
	Node(ll x) : val(x), l(nullptr), r(nullptr) {}
	Node(Node *_l, Node *_r) {
		l = _l, r = _r;
		val = 0;
		if (l) val += l->val;
		if (r) val += r->val;
	}
	Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};
 
int n, sz = 1;
ll a[200001];
Node *t[200001];
 
Node *build(int l = 1, int r = n) {
	if (l == r) return new Node(a[l]);
	int mid = (l + r) / 2;
	return new Node(build(l, mid), build(mid + 1, r));
}
 
Node *update(Node *node, int pos, int val, int l = 1, int r = n) {
	if (l == r) return new Node(val);
	int mid = (l + r) / 2;
	if (pos > mid)
		return new Node(node->l, update(node->r, pos, val, mid + 1, r));
	else return new Node(update(node->l, pos, val, l, mid), node->r);
}
 
ll query(Node *node, int a, int b, int l = 1, int r = n) {
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return node->val;
	int mid = (l + r) / 2;
	return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}
 
int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int q; cin >> n >> q;
  for(int i=1;i<=n;i++){
    cin >> a[i];
  }
  t[sz++]=build();
  while(q--){
    int ty; cin >> ty;
    if(ty==1){
      int k, pos, x; cin >> k >> pos >> x;
      t[k]=update(t[k], pos, x);
    }
    else if(ty==2){
      int k, l, r; cin >> k >> l >> r;
      cout << query(t[k], l, r) << endl;
    }
    else{
      int k; cin >> k;
      t[sz++]=new Node(t[k]);
    }
  }
}
