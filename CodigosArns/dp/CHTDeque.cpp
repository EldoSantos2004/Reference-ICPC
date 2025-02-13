// needs fixing

struct line {
  ll a, b;
  line(ll A, ll B) : a(A), b(B) {}
  double intersect(const line &line1) const {
      return 1.0 * (line1.b - b) / (a - line1.a);
  }
  ll eval(ll x) {
      return a * x + b;
  }
};

// this finds the minimum and slope in increasing
deque<line> l[p+1];
l[0].push_front({-1, -s[1]});
for(int i=1;i<=m;i++){
  for(int j=p;j>0;j--){
    if(j>i) continue;
    while((int)l[j-1].size()>=2 && l[j-1].back().eval(a[i])>=l[j-1][(int)l[j-1].size()-2].eval(a[i])){
l[j-1].pop_back();
    }
    dp[i][j]=l[j-1].back().eval(a[i])+(a[i]*(i))+s[i];
    line cur(-i-1, dp[i][j]-s[i+1]);
    while((int)l[j].size()>=2 && cur.intersect(l[j][1])<=l[j][0].intersect(l[j][1])){
l[j].pop_front();
    }
    l[j].push_front(cur);
  }
}
