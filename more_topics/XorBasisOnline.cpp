int rebuild_and_delete (int id) {
  int pos = 0, mn = inf, p2 = 0;
  for (int i = 0; i < basis.size(); i++) {
      if (basis[i].id == id) {
          pos = i;
      }
  }
  int bits = 0;
  for (int i = 0; i < basis.size(); i++) {
      if (basis[i].mask & (1 << pos)) {
          if (mn > basis[i].high) {
              mn = basis[i].high;
              p2 = i;
          }
          bits ^= 1 << basis[i].high;
      }
  }

  if (p2 != pos) {
      swap(basis[p2].id, basis[pos].id);
      for (auto &i : basis) {
          swap_bits(i.mask, pos, p2); // just swaps pos-th and p2-th bit in i.mask
      }
      pos = p2;
  }
  for (int i = 0; i < basis.size(); i++) {
      if (i != pos) {
          if (basis[i].mask & (1 << pos)) {
              basis[i].val ^= basis[pos].val;
              basis[i].mask ^= basis[pos].mask;
          }
      }
  }
  int good = (1 << pos) - 1;
  int other = ((1 << len(basis)) - 1) ^ (good | (1 << pos));
  basis.erase(basis.begin() + pos);
  for (auto &i : basis) {
      i.mask = ((i.mask & other) >> 1) | (i.mask & good);
  }
  return bits;
}

C++
41 lines
1161 bytes

Next, we need to find y from Statement 1 in O(m) or say that it does not exist. For y, the following condition must hold: span((Xj​∖{v})∪{y})=span(Xj​). We know which highest bit disappeared when deleting the integer v from Xj​. Therefore, when adding y∈Xj+1​ to Xj​∖{v}, y must "be responsible" for this disappeared bit.

Then, we can check for each x∈Xj+1​ in O(1) whether it is suitable as y. It is not difficult to verify that x is suitable if and only if cnt(bits & x) mod 2=1, where cnt(t) is a function that returns the integer of set bits in the integer.

int get_the_same_high_bit (int bits, vector <int> &val) {
  for (auto &i : basis) {
      if (__builtin_popcount(val[i.id] & bits) & 1) {
          return i.id;
      }
  }
  return -1;
}

C++
8 lines
200 bytes

Thus, we have learned to delete in O(m2).

Here is full version of the code:
Code

//#pragma GCC optimize("Ofast", "unroll-loops")
//#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4")

#include <bits/stdc++.h>

#define all(a) a.begin(),a.end()
#define len(a) (int)(a.size())
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define fi first
#define se second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;

template<typename T>
bool umin(T &a, T b) {
  if (b < a) {
      a = b;
      return true;
  }
  return false;
}
template<typename T>
bool umax(T &a, T b) {
  if (a < b) {
      a = b;
      return true;
  }
  return false;
}

#ifdef KIVI
#define DEBUG for (bool _FLAG = true; _FLAG; _FLAG = false)
#define LOG(...) print(#__VA_ARGS__" ::", __VA_ARGS__) << endl
template <class ...Ts> auto &print(Ts ...ts) { return ((cerr << ts << " "), ...); }
#else
#define DEBUG while (false)
#define LOG(...)
#endif

const int max_n = -1, inf = 1000111222;


const int C = 20;

struct node {
  int val, id, mask, high;
};


inline int get_high (int x) {
  if (x == 0) {
      return -1;
  }
  return 31 - __builtin_clz(x);
}

inline void swap_bits (int &x, int a, int b) {
  int x1 = bool(x & (1 << a));
  int x2 = bool(x & (1 << b));
  x ^= (x1 ^ x2) << a;
  x ^= (x1 ^ x2) << b;
}

struct xor_basis {
  vector <node> basis;

  inline bool add (int x, int id) {
      int mask = 0;
      for (auto &i : basis) {
          if (umin(x, x ^ i.val)) {
              mask ^= i.mask;
          }
      }
      if (x) {
          mask |= 1 << len(basis);
          for (auto &i : basis) {
              if (umin(i.val, i.val ^ x)) {
                  i.mask ^= mask;
              }
          }
          basis.pb(node{val: x, id: id, mask: mask, high: get_high(x)});
          return true;
      }
      return false;
  }



  inline int get_the_same_high_bit (int bits, const vector <int> &val) {
      for (auto &i : basis) {
          if (__builtin_popcount(val[i.id] & bits) & 1) {
              return i.id;
          }
      }
      return -1;
  }


  inline int rebuild_and_delete (int id) {
      int pos = 0, mn = inf, p2 = 0;
      for (int i = 0; i < len(basis); i++) {
          if (basis[i].id == id) {
              pos = i;
          }
      }
      int bits = 0;
      for (int i = 0; i < len(basis); i++) {
          if (basis[i].mask & (1 << pos)) {
              if (umin(mn, basis[i].high)) {
                  p2 = i;
              }
              bits ^= 1 << basis[i].high;
          }
      }

      if (p2 != pos) {
          swap(basis[p2].id, basis[pos].id);
          for (auto &i : basis) {
              swap_bits(i.mask, pos, p2);
          }
          pos = p2;
      }
      for (int i = 0; i < len(basis); i++) {
          if (i != pos) {
              if (basis[i].mask & (1 << pos)) {
                  basis[i].val ^= basis[pos].val;
                  basis[i].mask ^= basis[pos].mask;
              }
          }
      }
      int good = (1 << pos) - 1;
      int other = ((1 << len(basis)) - 1) ^ (good | (1 << pos));
      basis.erase(basis.begin() + pos);
      for (auto &i : basis) {
          i.mask = ((i.mask & other) >> 1) | (i.mask & good);
      }
      return bits;
  }

};

template<int max_bit> // not inclusive
struct xor_basis_online {

  vector <xor_basis> basises[max_bit + 1];

  int mx;

  vector <pii> where;
  vector <int> val;

  xor_basis_online() : mx(0), cur_id(0) {}

  int cur_id;

  inline int add (int x) {
      val.pb(x);
      where.pb(make_pair(-1, -1));
      int id = cur_id++;
      if (x == 0) {
          return id;
      }
      for (int i = mx; i >= 0; i--) {
          if (basises[i].empty()) {
              continue;
          }
          if (basises[i].back().add(x, id)) {
              basises[i + 1].pb(basises[i].back());
              basises[i].pop_back();
              umax(mx, i + 1);
              for (auto &j : basises[i + 1].back().basis) {
                  where[j.id] = make_pair(i + 1, len(basises[i + 1]) - 1);
              }
              return id;
          }
      }
      basises[1].pb(xor_basis());
      basises[1].back().add(x, id);
      where.back() = make_pair(1, len(basises[1]) - 1);
      umax(mx, 1);
      return id;
  }

  inline int move_back (int sz, int pos) {
      int to = len(basises[sz]) - 1;
      if (to == pos) {
          return pos;
      }
      for (auto &i : basises[sz][pos].basis) {
          where[i.id].second = to;
      }
      for (auto &i : basises[sz][to].basis) {
          where[i.id].second = pos;
      }
      swap(basises[sz][pos], basises[sz][to]);
      return to;
  }

  inline void del (int id) {
      if (val[id] == 0) {
          return;
      }
      int sz, pos;
      tie(sz, pos) = where[id];
      pos = move_back(sz, pos);
      while (true) {
          int bits = basises[sz].back().rebuild_and_delete(id);
          int i = sz - 1;
          while (i > 0 && basises[i].empty()) {
              --i;
          }
          int new_id = -1;
          if (i > 0) {
              new_id = basises[i].back().get_the_same_high_bit(bits, val);
          }
          if (new_id == -1) {
              if (sz > 1) {
                  basises[sz - 1].pb(basises[sz].back());
                  for (auto &j : basises[sz - 1].back().basis) {
                      where[j.id] = make_pair(sz - 1, len(basises[sz - 1]) - 1);
                  }
              }
              basises[sz].pop_back();
              if (mx > 0 && basises[mx].empty()) {
                  --mx;
              }
              return;
          }
          int cur = val[new_id];
          assert(basises[sz].back().add(cur, new_id));
          int new_sz = i;
          int new_pos = len(basises[i]) - 1;
          where[new_id] = make_pair(sz, pos);
          id = new_id;
          sz = new_sz;
          pos = new_pos;
      }
  }

  inline int size () {
      return mx;
  }
};

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

  ios_base::sync_with_stdio(0);
  cin.tie(0);


  // solution to https://basecamp.eolymp.com/uk/problems/11732
  int n, q, add;
  cin >> n >> add;
  vector <int> p(n);
  xor_basis_online<19> t;
  vector <int> now(n);
  for (int i = 0; i < n; i++) {
      cin >> p[i];
      now[i] = t.add(i ^ p[i]);
  }
  cin >> q;
  int ans = t.size();
  cout << ans << '\n';
  for (int i = 0, l, r; i < q; i++) {
      cin >> l >> r;
      l = (l + ans * add) % n;
      r = (r + ans * add) % n;
      if (l != r) {
          t.del(now[l]);
          t.del(now[r]);
          swap(p[l], p[r]);
          now[l] = t.add(l ^ p[l]);
          now[r] = t.add(r ^ p[r]);
      }
      ans = t.size();
      cout << ans << '\n';
  }
}