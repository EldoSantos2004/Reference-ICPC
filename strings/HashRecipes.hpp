#pragma once
#include "ComposableHash.hpp"

namespace hashing_ref {
// Hash-based answers are Monte Carlo: collisions can affect results.
inline int lcp(const PrefixHash& a, int i,
               const PrefixHash& b, int j, int limit = INT_MAX) {
    assert(0 <= i && i <= a.size() && 0 <= j && j <= b.size());
    assert(limit >= 0);
    int lo = 0, hi = std::min({a.size() - i, b.size() - j, limit});
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (a.get(i, i + mid) == b.get(j, j + mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
inline int compare(const PrefixHash& a, int l, int r,
                   const PrefixHash& b, int i, int j) {
    assert(0 <= l && l <= r && r <= a.size());
    assert(0 <= i && i <= j && j <= b.size());
    int n = r - l, m = j - i, k = lcp(a, l, b, i, std::min(n, m));
    if (k == std::min(n, m)) return (n > m) - (n < m);
    unsigned char x = a.text[l + k], y = b.text[i + k];
    return (x > y) - (x < y);
}
inline bool has_period(const PrefixHash& s, int l, int r, int k) {
    assert(0 <= l && l <= r && r <= s.size());
    if (k <= 0 || k > r - l) return false;
    return s.get(l, r - k) == s.get(l + k, r);
}
inline bool is_block_power(const PrefixHash& s, int l, int r, int k) {
    return has_period(s, l, r, k) && (r - l) % k == 0;
}
// First L bytes of the infinite repetition of nonempty s.
inline Hash periodic_prefix(const PrefixHash& s, u64 L) {
    if (L == 0) return {};
    assert(s.size() > 0);
    return repeated(s.whole(), L / s.size()) *
           s.get(0, (int)(L % s.size()));
}
// Compare a^p and b^q without constructing them. Return -1, 0 or 1.
inline int compare_repeated(const PrefixHash& a, u64 p,
                            const PrefixHash& b, u64 q) {
    u64 n = checked_length((u128)a.size() * p);
    u64 m = checked_length((u128)b.size() * q);
    u64 lo = 0, hi = std::min(n, m);
    while (lo < hi) {
        u64 d = hi - lo, mid = lo + d / 2 + d % 2;
        if (periodic_prefix(a, mid) == periodic_prefix(b, mid)) lo = mid;
        else hi = mid - 1;
    }
    if (lo == std::min(n, m)) return (n > m) - (n < m);
    unsigned char x = a.text[lo % a.size()];
    unsigned char y = b.text[lo % b.size()];
    return (x > y) - (x < y);
}
// Exact alternative for comparing just two powers (Fine-Wilf).
inline int compare_repeated_exact(const PrefixHash& a, u64 p,
                                  const PrefixHash& b, u64 q) {
    u64 n = checked_length((u128)a.size() * p);
    u64 m = checked_length((u128)b.size() * q);
    if (n == 0 || m == 0) return (n > m) - (n < m);
    u64 bound = (u64)a.size() + b.size() - std::gcd(a.size(), b.size());
    u64 scan = std::min({n, m, bound});
    for (u64 k = 0; k < scan; ++k) {
        unsigned char x = a.text[k % a.size()], y = b.text[k % b.size()];
        if (x != y) return (x > y) - (x < y);
    }
    return (n > m) - (n < m);
}
} // namespace hashing_ref
