// Sum segment tree
struct sum_t{
  ll val;
  static const long long null_v = 0;
  
  sum_t(): val(null_v) {}
  sum_t(long long v): val(v) {}
  
  sum_t operator + (const sum_t &a) const {
    sum_t ans;
    ans.val = val + a.val;
    return ans;
  }
};
// Min segment tree
struct min_t{
  ll val;
  static const long long null_v = 1e18;
  
  min_t(): val(null_v) {}
  min_t(long long v): val(v) {}
  
  min_t operator + (const min_t &a) const {
    min_t ans;
    ans.val = min(val, a.val);
    return ans;
  }
};
// Max segment tree
struct max_t{
  ll val;
  static const long long null_v = -1e18;
  
  max_t(): val(null_v) {}
  max_t(long long v): val(v) {}
  
  max_t operator + (const max_t &a) const {
    max_t ans;
    ans.val = max(val, a.val);
    return ans;
  }
};
// GCD segment tree
struct gcd_t{
  ll val;
  static const long long null_v = 0;
  
  gcd_t(): val(null_v) {}
  gcd_t(long long v): val(v) {}
  
  gcd_t operator + (const gcd_t &a) const {
    gcd_t ans;
    ans.val = gcd(val, a.val);
    return ans;
  }
};
