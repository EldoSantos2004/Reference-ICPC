struct Fenwick2D{
  vector<vector<ll>> b;
  int n;

  Fenwick2D(int _n) : b(_n+5, vector<ll>(_n+5, 0)), n(_n) {}

  void update(int x, int y, int val){
    for(; x<=n; x+=(x&-x)){
      for(int j=y;j<=n;j+=(j&-j)){
        b[x][j]+=val;
      }
    }
  }

  ll get(int x, int y){
    ll ans=0;
    for(; x; x-=x&-x){
      for(int j=y; j ;j-=j&-j){
        ans+=b[x][j];
      }
    }
    return ans;
  }

  ll get1(int x1, int y1, int x2, int y2){
    return get(x2, y2)-get(x1-1, y2)-get(x2, y1-1)+ get(x1-1, y1-1);
  }

};
