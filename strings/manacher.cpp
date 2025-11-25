/*
                              Manacher
  ----------------------------------------------------------------
  Computes the length of the longest palindrome centered at position i.

  p[i] is length of biggest palindrome centered in this position.
  Be careful with characters that are inserted to account for odd and even palindromes

  Time Complexity: O(n)
  Space Complexity: O(n)

*/

// Number of palindromes centered at each position

vector<int> manacher_odd(string s)
{
  int n = s.size();
  s = "$" + s + "^";
  vector<int> p(n + 2);
  int l = 1, r = 1;
  for (int i = 1; i <= n; i++)
  {
    p[i] = max(0, min(r - i, p[l + (r - i)]));
    while (s[i - p[i]] == s[i + p[i]])
    {
      p[i]++;
    }
    if (i + p[i] > r)
    {
      l = i - p[i], r = i + p[i];
    }
  }
  return vector<int>(begin(p) + 1, end(p) - 1);
}
vector<int> manacher(string s)
{
  string t;
  for (auto c : s)
  {
    t += string("#") + c;
  }
  auto res = manacher_odd(t + "#");
  return vector<int>(begin(res) + 1, end(res) - 1);
}

// example use. Longest palindrome that ends at each position
int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  int n = sz(s);
  auto man = manacher(s);
  vector<int> a(n), b(n);
  // a[i] is how many odd palindromes - 1 with this center 
  // b[i] is how many even palindromes with this center + 1 as 
  for(int i = 0; i < sz(man); i += 2){
    a[i / 2] = (man[i] - 1) / 2;
    if(i) b[i / 2] = (man[i - 1]) / 2;
  }
  vector<int> ans(n + 1, 1);
  for(int i = 0; i < n; i++){
    ans[i + a[i]] = max(ans[i + a[i]], a[i] * 2 + 1);
    if(b[i])ans[i + b[i] - 1] = max(ans[i + b[i] - 1], b[i] * 2);
  }
  for(int i = n - 2; i >= 0; i--){
    ans[i] = max(ans[i], ans[i + 1] - 2);
  }
  for(int i = 0; i < n; i++){
    cout << ans[i] << " ";
  }
  cout << endl;
}

// usage
// vector<int> p = manacher("abacaba");
// this will return {2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2}
// vector<int> p = manacher("abaaba");
// this will return {2, 1, 4, 1, 2, 7, 2, 1, 4, 1, 2}
