/*
  Palindromic Tree (Eertree)
  --------------------------
  Indexing: 0-based
  Time Complexity:
    - extend(i): O(1) amortized
    - calc_occurrences(): O(n)
  Space Complexity: O(n)

  Features:
    - Each node represents a unique palindromic substring
    - Efficient online construction
    - `oc`: how many times this palindrome occurs as suffix
    - `cnt`: number of palindromic suffixes in its subtree
    - `link`: suffix link to longest proper palindromic suffix
*/

const int N = 3e5 + 9;

struct PalindromicTree {
  struct node {
    int nxt[26];     // transitions by character
    int len;         // length of palindrome
    int st, en;      // start and end indices in string
    int link;        // suffix link
    int cnt = 0;     // number of palindromic suffixes
    int oc = 0;      // occurrences of the palindrome
  };

  string s;
  vector<node> t;
  int sz, last;

  PalindromicTree() {}
  PalindromicTree(const string &_s) {
    s = _s;
    int n = s.size();
    t.clear();
    t.resize(n + 5); // up to n + 2 distinct palindromes
    sz = 2;
    last = 2;
    // Root 1: imaginary (-1 length), simplifies links
    t[1].len = -1;
    t[1].link = 1;
    // Root 2: length 0, link to root 1
    t[2].len = 0;
    t[2].link = 1;
  }

  // Extend tree with s[pos], returns 1 if a new node is created
  int extend(int pos) {
    int cur = last;
    int ch = s[pos] - 'a';
    // Find longest suffix palindrome that can be extended
    while (true) {
      int curlen = t[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
      cur = t[cur].link;
    }

    if (t[cur].nxt[ch]) {
      // Already exists
      last = t[cur].nxt[ch];
      t[last].oc++;
      return 0;
    }
    // Create new node
    sz++;
    last = sz;
    t[sz].oc = 1;
    t[sz].len = t[cur].len + 2;
    t[cur].nxt[ch] = sz;
    t[sz].en = pos;
    t[sz].st = pos - t[sz].len + 1;

    if (t[sz].len == 1) {
      t[sz].link = 2;
      t[sz].cnt = 1;
      return 1;
    }
    // Compute suffix link
    while (true) {
      cur = t[cur].link;
      int curlen = t[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
        t[sz].link = t[cur].nxt[ch];
        break;
      }
    }
    t[sz].cnt = 1 + t[t[sz].link].cnt;
    return 1;
  }
  // Accumulate total occurrences for each palindrome node
  void calc_occurrences() {
    for (int i = sz; i >= 3; i--) {
      t[t[i].link].oc += t[i].oc;
    }
  }
};

int main() {
  string s;
  cin >> s;
  PalindromicTree t(s);
  for (int i = 0; i < s.size(); i++) {
    t.extend(i);
  }
  t.calc_occurrences();
  long long total = 0;
  for (int i = 3; i <= t.sz; i++) {
    total += t.t[i].oc;
  }
  cout << total << '\n'; // Total palindromic substrings
  return 0;
}
