vector<int> nextSmaller(vector<int> a, int n){
  stack<int> s;
  vector<int> res(n, n);
  for(int i=0;i<n;i++){
    while(s.size() && a[s.top()]>a[i]){
      res[s.top()]=i;
      s.pop();
    }
    s.push(i);
  }
  return res;
}

vector<int> prevSmaller(vector<int> a, int n){
  stack<int> s;
  vector<int> res(n, -1);
  for(int i=n-1;i>=0;i--){
    while(s.size() && a[s.top()]>a[i]){
      res[s.top()]=i;
      s.pop();
    }
    s.push(i);
  }
  return res;
}
