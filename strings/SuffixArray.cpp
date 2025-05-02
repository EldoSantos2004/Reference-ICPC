/*
                              Suffix Array 
  ---------------------------------------------------------------
  Computes the suffix array of a string in O(n log n).
  Sorted array of all cyclic shifts of a string.
  If you want sorted suffixes append $ to the end of the string.
  lc is longest common prefix. Lcp of two substrings j > i
  is min(lc[i], ....., lc[j - 1]).

  To compute Largest common substring of multiple strings
  Join all strings separating them with special character like $ 
  (it has to be different for each string)
  Sliding window on lcp array (all string have to appear on 
  the sliding window and 
  the lcp of the interval will give the length of the substring 
  that appears on all strings)

  Time Complexity: O(n log n)
  Space Complexity: O(n)

*/

struct SuffixArray
{
  int n;
  string t;
  vector<int> sa, rk, lc;
  SuffixArray(const std::string &s)
  {
    n = s.length();
    t = s;
    sa.resize(n);
    lc.resize(n - 1);
    rk.resize(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int a, int b)
              { return s[a] < s[b]; });
    rk[sa[0]] = 0;
    for (int i = 1; i < n; ++i)
      rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    int k = 1;
    std::vector<int> tmp, cnt(n);
    tmp.reserve(n);
    while (rk[sa[n - 1]] < n - 1)
    {
      tmp.clear();
      for (int i = 0; i < k; ++i)
        tmp.push_back(n - k + i);
      for (auto i : sa)
        if (i >= k)
          tmp.push_back(i - k);
      std::fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < n; ++i)
        ++cnt[rk[i]];
      for (int i = 1; i < n; ++i)
        cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; --i)
        sa[--cnt[rk[tmp[i]]]] = tmp[i];
      std::swap(rk, tmp);
      rk[sa[0]] = 0;
      for (int i = 1; i < n; ++i)
        rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
      k *= 2;
    }
    for (int i = 0, j = 0; i < n; ++i)
    {
      if (rk[i] == 0)
      {
        j = 0;
      }
      else
      {
        for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j];)
          ++j;
        lc[rk[i] - 1] = j;
      }
    }
  }
  
  // Finds if string p appears as substring in the string
  // might now work perfectly
  int search(string &p){
      int tam = p.size();
      int l = 0, r = n;
      
      string tmp = "";
      while(r > l) {
          int m = l + (r-l)/2;
          tmp = t.substr(sa[m], min(n-sa[m], tam));
          if(tmp >= p){
              r = m;
          } else {
              l = m + 1;
          }
      }
      if(l < n) {
          tmp = t.substr(sa[l], min(n-sa[l], tam));
      } else{
          return -1;
      }
      if(tmp == p){
          return l;
      } else {
          return -1;
      }
  }
  

  // Counts number of times a string p appears as substring in string
  int count(string &p) {
      int x = search(p);
      if(x == -1) return 0;
      int cnt = 0;
      int tam = p.size();
      int maxx = 0;
      while((1 << maxx) + x < n) maxx++;
      int y = x;
      for(int i = maxx-1; i >= 0; i--) {
          if(x + (1 << i) >= n) continue;
          string tmp = t.substr(sa[x + (1 << i)], min(n-sa[x + (1 << i)], tam));
          if(tmp == p) x += (1 << i);
      }
      return x-y+1;
  }
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    SuffixArray SA(s);
    
    int q; cin >> q;
    for(int t = 0; t < q; t++) {
        string tmp; cin >> tmp;
        cout << SA.count(tmp) << endl;
    }
    
    return 0;
}
