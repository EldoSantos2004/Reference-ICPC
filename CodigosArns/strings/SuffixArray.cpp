//beware of first element of p being $
vector<int> suffixArray(string s){
  int n, k=0;
  s+="$";
  n=s.size();
  vector <int> p(n), c(n);
  vector <pair<char, int>> a(n);
  for (int i=0;i<n;i++)a[i]= {s[i], i};
  sort(a.begin(), a.end());
  for (int i=0;i<n;i++) p[i]=a[i].second;
  c[p[0]]=0;
  for (int i=1;i<n;i++){
    if(a[i].first!=a[i-1].first)  c[p[i]]=c[p[i-1]]+1;
    else c[p[i]]=c[p[i-1]];
  }  
  while((1<<k)<n){
    for(int i=0;i<n;i++){
      p[i]=(p[i]-(1<<k)+n)%n;
    }
    vector<int> cnt(n);
    for(auto x:c){
      cnt[x]++;
    }
    vector<int> p1(n), pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++){
      pos[i]=pos[i-1]+cnt[i-1];
    }
    for(auto x:p){
      int i=c[x];
      p1[pos[i]]=x;
      pos[i]++;
    }
    p=p1;
    vector<int> c1(n);
    c1[p[0]]=0;
    for(int i=1;i<n;i++){
      pair<int, int> aa={c[p[i]], c[(p[i]+(1<<k))%n]};
      pair<int, int> bb={c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
      if(bb==aa){
        c1[p[i]]=c1[p[i-1]];
      }
      else{
        c1[p[i]]=c1[p[i-1]]+1;
      }
    }
    c=c1;
    k++;
  }
  return p;
}

vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

