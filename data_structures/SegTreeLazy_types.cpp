struct max_t {
  ll val;
  static const ll null_v = -1LL << 61;
  max_t(): val(0) {}
  max_t(ll v): val(v) {}
  max_t op(max_t& other) {
    return max_t(max(val, other.val));
  }
  max_t lazy_op(max_t& v, int size) {
    return max_t(val + v.val);
  }
};

struct min_t {
  ll val;
  static const ll null_v = 1LL << 61;
  min_t(): val(0) {}
  min_t(ll v): val(v) {}
  min_t op(min_t& other) {
    return min_t(min(val, other.val));
  }
  min_t lazy_op(min_t& v, int size) {
    return min_t(val + v.val);
  }
};

struct sum_t {
  ll val;
  static const ll null_v = 0;
  sum_t(): val(0) {}
  sum_t(ll v): val(v) {}
  sum_t op(sum_t& other) {
    return sum_t(val + other.val);
  }
  sum_t lazy_op(sum_t& v, int size) {
    return sum_t(val + v.val * size);
  }
};
