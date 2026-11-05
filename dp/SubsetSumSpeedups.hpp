#pragma once
#include <bits/stdc++.h>

namespace knapsack_ref {
// Positive weights; total sum S must fit int and memory.
// Bit s of the returned words says whether sum s is possible.
std::vector<uint64_t> subset_sum_all(
    const std::vector<int>& weights) {
    int S = std::accumulate(weights.begin(), weights.end(), 0);
    std::vector<int> count(S + 1);
    for (int w : weights) ++count[w];
    std::vector<uint64_t> bits(S / 64 + 1);
    bits[0] = 1;
    auto shift_or = [&](int w) {
        int whole = w / 64, part = w % 64;
        // Descend: every source still belongs to the old bitset.
        for (int j = (int)bits.size() - 1; j >= whole; --j) {
            uint64_t moved = bits[j - whole] << part;
            if (part && j > whole)
                moved |= bits[j - whole - 1] >> (64 - part);
            bits[j] |= moved;
        }
    };
    for (int w = 1; w <= S; ++w) {
        int c = count[w];
        if (!c) continue;
        int keep = (c % 2 ? 1 : 2);
        int pairs = (c - keep) / 2;
        if (pairs) count[2 * w] += pairs;
        for (int j = 0; j < keep; ++j) shift_or(w);
    }
    return bits;
}

// Positive weights; target >= 0; returns exact feasibility.
// O(N*D) time, O(D) extra space, D = maximum weight.
bool subset_sum_small_weights(const std::vector<int>& w,
                              long long target) {
    if (target == 0) return true;
    long long total = std::accumulate(w.begin(), w.end(), 0LL);
    if (target > total || w.empty()) return false;
    int n = (int)w.size();
    int D = *std::max_element(w.begin(), w.end());
    int k = 0;
    long long base = 0;
    while (k < n && base + w[k] < target) base += w[k++];
    // Index t represents total target + t - D.
    // dp[t] = largest boundary l in [0,k], or -1.
    std::vector<int> dp(2 * D + 1, -1);
    dp[(int)(base - target + D)] = k;
    for (int r = k; r < n; ++r) {
        auto old = dp;
        // Add item r only from totals below the target.
        for (int t = 0; t < D; ++t)
            if (old[t] >= 0)
                dp[t + w[r]] = std::max(dp[t + w[r]], old[t]);
        // Remove a still-fixed prefix item only above target.
        // Descending totals close all chains of removals.
        for (int t = 2 * D; t > D; --t) {
            int stop = std::max(0, old[t]);
            for (int j = dp[t] - 1; j >= stop; --j)
                dp[t - w[j]] = std::max(dp[t - w[j]], j);
        }
        if (dp[D] >= 0) return true;
    }
    return false;
}
} // namespace knapsack_ref
