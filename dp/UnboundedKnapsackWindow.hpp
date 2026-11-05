#pragma once
#include <bits/stdc++.h>

namespace knapsack_ref {
// Unbounded items (weight,value); positive integer weights <= D.
// Capacity 0 <= C <= 10^18. Intermediate values fit long long.
// O(N + D^2 log(C+2)) time, O(D + log(C+2)) extra space.
long long unbounded_knapsack_window(
    long long C, int D,
    const std::vector<std::pair<int, long long>>& items) {
    using ll = long long;
    const ll NEG = std::numeric_limits<ll>::lowest();
    std::vector<ll> value(D + 1, NEG);
    value[1] = 0; // Dummy unit item fills unused capacity.
    for (auto [w, v] : items) value[w] = std::max(value[w], v);
    std::vector<ll> base(3 * D + 1, 0);
    for (int c = 1; c <= 3 * D; ++c)
        for (int w = 1; w <= D && w <= c; ++w)
            if (value[w] != NEG)
                base[c] = std::max(base[c], base[c - w] + value[w]);
    // A block stores exact padded answers at lo,lo+1,... .
    struct Block { ll lo; std::vector<ll> a; };
    std::function<Block(ll)> solve = [&](ll T) -> Block {
        ll lo = std::max(0LL, T - D), hi = T + D;
        if (T <= 2LL * D)
            return {lo, std::vector<ll>(base.begin() + lo,
                                       base.begin() + hi + 1)};
        Block child = solve(T / 2);
        std::vector<ll> out(hi - lo + 1, NEG);
        for (int i = 0; i < (int)child.a.size(); ++i)
            for (int j = 0; j < (int)child.a.size(); ++j) {
                ll s = 2 * child.lo + i + j;
                if (lo <= s && s <= hi)
                    out[s - lo] = std::max(out[s - lo],
                                          child.a[i] + child.a[j]);
            }
        return {lo, std::move(out)};
    };
    Block answer = solve(C);
    return answer.a[C - answer.lo];
}
} // namespace knapsack_ref
