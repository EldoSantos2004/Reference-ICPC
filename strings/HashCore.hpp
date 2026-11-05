#pragma once
#include <bits/stdc++.h>
#include <cassert>

namespace hashing_ref {
using u64 = uint64_t;
using u128 = __uint128_t;
inline constexpr u64 MOD = (1ULL << 61) - 1;
inline u64 add(u64 a, u64 b) {
    u64 s = a + b;
    return s >= MOD ? s - MOD : s;
}
inline u64 sub(u64 a, u64 b) {
    return a >= b ? a - b : a + MOD - b;
}
inline u64 mul(u64 a, u64 b) {
    return (u128)a * b % MOD;
}
inline u64 power(u64 a, u64 e) {
    u64 r = 1;
    for (; e; e >>= 1, a = mul(a, a))
        if (e & 1) r = mul(r, a);
    return r;
}
inline std::mt19937_64& rng() {
    static std::mt19937_64 gen(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return gen;
}
inline u64 splitmix64(u64 x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
inline u64 checked_length(u128 n) {
    if (n > std::numeric_limits<u64>::max())
        throw std::overflow_error("hash length overflow");
    return (u64)n;
}
} // namespace hashing_ref
