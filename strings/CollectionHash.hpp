#pragma once
#include "HashCore.hpp"

namespace hashing_ref {
// Same key -> same pair of words for the lifetime of this process.
// Random fingerprints, not cryptographic hashes or independent oracles.
inline std::array<u64, 2> random_id(u64 key) {
    static const std::array<u64, 2> seed{rng()(), rng()()};
    return {splitmix64(key + seed[0]), splitmix64(key + seed[1])};
}

// Multiplicities matter. Unsigned sums wrap modulo 2^64 intentionally.
struct MultisetHash {
    std::array<u64, 2> h{0, 0};
    u64 count = 0;
    void insert(u64 x) {
        u64 next_count = checked_length((u128)count + 1);
        auto r = random_id(x);
        for (int k = 0; k < 2; ++k) h[k] += r[k];
        count = next_count;
    }
    // Precondition: this occurrence of x is present.
    void erase(u64 x) {
        assert(count > 0);
        auto r = random_id(x);
        for (int k = 0; k < 2; ++k) h[k] -= r[k];
        --count;
    }
    friend MultisetHash operator+(MultisetHash a, const MultisetHash& b) {
        a.count = checked_length((u128)a.count + b.count);
        for (int k = 0; k < 2; ++k) a.h[k] += b.h[k];
        return a;
    }
    friend MultisetHash operator-(MultisetHash a, const MultisetHash& b) {
        assert(b.count <= a.count); // b is a submultiset of a.
        a.count -= b.count;
        for (int k = 0; k < 2; ++k) a.h[k] -= b.h[k];
        return a;
    }
    friend bool operator==(const MultisetHash& a, const MultisetHash& b) {
        return a.count == b.count && a.h == b.h;
    }
};
struct MultisetPrefix {
    std::vector<MultisetHash> pref{MultisetHash{}};
    explicit MultisetPrefix(const std::vector<long long>& a) {
        for (long long x : a) {
            pref.push_back(pref.back());
            pref.back().insert((u64)x);
        }
    }
    explicit MultisetPrefix(std::string_view s) {
        for (unsigned char c : s) {
            pref.push_back(pref.back());
            pref.back().insert(c);
        }
    }
    MultisetHash get(int l, int r) const {
        assert(0 <= l && l <= r && (size_t)r < pref.size());
        return pref[r] - pref[l];
    }
};

// A real set: duplicate insertion and absent deletion are ignored.
// Tracking membership prevents XOR from becoming a parity hash.
struct SetHash {
    struct KeyHash {
        size_t operator()(u64 x) const { return random_id(x)[0]; }
    };
    std::unordered_set<u64, KeyHash> present;
    std::array<u64, 2> h{0, 0};
    bool insert(u64 x) {
        if (!present.insert(x).second) return false;
        toggle(x);
        return true;
    }
    bool erase(u64 x) {
        if (!present.erase(x)) return false;
        toggle(x);
        return true;
    }
    friend bool operator==(const SetHash& a, const SetHash& b) {
        return a.present.size() == b.present.size() && a.h == b.h;
    }
private:
    void toggle(u64 x) {
        auto r = random_id(x);
        for (int k = 0; k < 2; ++k) h[k] ^= r[k];
    }
};
} // namespace hashing_ref
