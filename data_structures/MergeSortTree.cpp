vector<int> t[200005];
int a[100005];
int n;

void build(){
  for(int i=0;i<n;i++){
    t[i+n].push_back(a[i]);
  }
  for(int i=n-1;i;i--){
    auto b=t[2*i], c=t[2*i+1];
    merge(b.begin(), b.end(), c.begin(), c.end(), back_inserter(t[i]));
  }
}


int q(int l, int r, int mid) {  
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1){
        res+=upper_bound(all(t[l]), mid)-t[l].begin();
        l++;
    }
    if (r&1){
        r--;
        res+=upper_bound(all(t[r]), mid)-t[r].begin();
    }
  }
  return res;
}
