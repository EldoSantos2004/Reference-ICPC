#pragma once
#include "HashCore.hpp"

namespace hashing_ref {
struct HashParameters {
    std::array<u64, 2> base, inverse;
    HashParameters() {
        std::uniform_int_distribution<u64> dist(257, MOD - 2);
        for (int k = 0; k < 2; ++k) {
            base[k] = dist(rng());
            inverse[k] = power(base[k], MOD - 2);
        }
    }
};
inline const HashParameters& parameters() {
    static const HashParameters p;
    return p;
}

// Two independent bases in one prime field; byte values are 1..256.
// Same process-wide parameters for every object. Do not edit fields.
struct Hash {
    std::array<u64, 2> h{0, 0}, b{1, 1}, bi{1, 1};
    u64 len = 0; // Empty string is the identity.
    static Hash character(unsigned char c) {
        Hash r;
        r.len = 1;
        r.h.fill((u64)c + 1);
        r.b = parameters().base;
        r.bi = parameters().inverse;
        return r;
    }
    // Concatenate a then c. Order matters.
    friend Hash operator*(const Hash& a, const Hash& c) {
        Hash r;
        r.len = checked_length((u128)a.len + c.len);
        for (int k = 0; k < 2; ++k) {
            r.h[k] = add(a.h[k], mul(a.b[k], c.h[k]));
            r.b[k] = mul(a.b[k], c.b[k]);
            r.bi[k] = mul(a.bi[k], c.bi[k]);
        }
        return r;
    }
    // Remove prefix a from whole c. Caller guarantees it IS a prefix.
    friend Hash operator/(const Hash& c, const Hash& a) {
        assert(a.len <= c.len);
        Hash r;
        r.len = c.len - a.len;
        for (int k = 0; k < 2; ++k) {
            r.h[k] = mul(sub(c.h[k], a.h[k]), a.bi[k]);
            r.b[k] = mul(c.b[k], a.bi[k]);
            r.bi[k] = mul(c.bi[k], a.b[k]);
        }
        return r;
    }
    auto key() const { return std::make_tuple(len, h[0], h[1]); }
    friend bool operator==(const Hash& a, const Hash& b) {
        return a.len == b.len && a.h == b.h;
    }
    friend bool operator!=(const Hash& a, const Hash& b) {
        return !(a == b);
    }
};
inline Hash repeated(Hash a, u64 copies) {
    checked_length((u128)a.len * copies);
    Hash r;
    while (copies) {
        if (copies & 1) r = r * a;
        copies >>= 1;
        if (copies) a = a * a;
    }
    return r;
}

struct PrefixHash {
    std::string text;
    std::vector<Hash> pref{Hash{}};
    explicit PrefixHash(std::string_view s) : text(s) {
        assert(s.size() < (size_t)INT_MAX);
        pref.reserve(s.size() + 1);
        for (unsigned char c : s)
            pref.push_back(pref.back() * Hash::character(c));
    }
    int size() const { return (int)text.size(); }
    Hash get(int l, int r) const { // Zero-based [l,r), empty allowed.
        assert(0 <= l && l <= r && r <= size());
        return pref[r] / pref[l];
    }
    Hash whole() const { return pref.back(); }
};
} // namespace hashing_ref
