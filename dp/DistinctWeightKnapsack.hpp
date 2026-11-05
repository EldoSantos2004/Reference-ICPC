#pragma once
#include "ConcaveMaxPlus.hpp"

namespace knapsack_ref {
// 0/1 items (weight,value), capacity C. Positive weights.
// O(N log N + D*C) time, D = #distinct usable weights.
// dp[c] uses weight AT MOST c; negative values may be skipped.
std::vector<long long> distinct_weight_knapsack(
    int C, const std::vector<std::pair<int, long long>>& items) {
    using ll = long long;
    std::map<int, std::vector<ll>> groups;
    for (auto [w, v] : items)
        if (w <= C) groups[w].push_back(v);
    std::vector<ll> dp(C + 1, 0);
    for (auto& [w, values] : groups) {
        std::sort(values.rbegin(), values.rend());
        int K = std::min((int)values.size(), C / w);
        std::vector<ll> prefix(K + 1, 0);
        for (int t = 1; t <= K; ++t)
            prefix[t] = prefix[t - 1] + values[t - 1];
        auto old = dp;
        for (int r = 0; r < w && r <= C; ++r) {
            std::vector<ll> A;
            for (int c = r; c <= C; c += w) A.push_back(old[c]);
            auto merged = max_plus_concave(A, prefix);
            for (int t = 0; t < (int)A.size(); ++t)
                dp[r + t * w] = merged[t];
        }
    }
    return dp;
}
} // namespace knapsack_ref
