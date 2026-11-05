#pragma once
#include <bits/stdc++.h>

namespace knapsack_ref {
struct BoundedItem {
    int weight;
    long long value, copies;
};

// dp[c] = maximum value using weight AT MOST c.
// Positive weights, nonnegative copy counts; signed values allowed.
// Every intermediate value/product must fit long long.
std::vector<long long> bounded_knapsack(
    int C, const std::vector<BoundedItem>& items) {
    using ll = long long;
    std::vector<ll> dp(C + 1, 0);
    for (auto [w, v, copies] : items) {
        if (w > C || copies == 0) continue;
        int K = (int)std::min(copies, (ll)(C / w));
        auto old = dp;
        for (int r = 0; r < w && r <= C; ++r) {
            std::deque<std::pair<int, ll>> dq;
            for (int t = 0; r + t * w <= C; ++t) {
                while (!dq.empty() && dq.front().first < t - K)
                    dq.pop_front();
                ll candidate = old[r + t * w] - (ll)t * v;
                while (!dq.empty() && dq.back().second <= candidate)
                    dq.pop_back();
                dq.emplace_back(t, candidate);
                dp[r + t * w] = (ll)t * v + dq.front().second;
            }
        }
    }
    return dp;
}
} // namespace knapsack_ref
