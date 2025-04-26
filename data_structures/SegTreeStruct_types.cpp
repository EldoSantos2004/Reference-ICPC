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
// agregar max subarray sum 
