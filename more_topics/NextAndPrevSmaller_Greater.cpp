/*
  Next and Previous Smaller Elements
  ----------------------------------
  Given: array a[0..n-1]
  nextSmaller[i]: index of next element smaller than a[i], or n if none
  prevSmaller[i]: index of previous element smaller than a[i], or -1 if none
  Indexing: 0-based
*/
vector<int> nextSmaller(vector<int> a, int n) {
  stack<int> s;
  vector<int> res(n, n); // default: no smaller to right
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) {
      res[s.top()] = i;
      s.pop();
    }
    s.push(i);
  }
  return res;
}
vector<int> prevSmaller(vector<int> a, int n) {
  stack<int> s;
  vector<int> res(n, -1); // default: no smaller to left
  for (int i = n - 1; i >= 0; i--) {
    while (!s.empty() && a[s.top()] > a[i]) {
      res[s.top()] = i;
      s.pop();
    }
    s.push(i);
  }
  return res;
}
