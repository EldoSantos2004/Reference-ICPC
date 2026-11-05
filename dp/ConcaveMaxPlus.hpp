#pragma once
#include <bits/stdc++.h>

namespace knapsack_ref {
// Return row maxima of a totally monotone implicit matrix.
// better(row, old_col, new_col) chooses new_col on ties.
// All column comparisons below have old_col < new_col.
template<class Better>
void smawk(const std::vector<int>& rows,
           const std::vector<int>& cols,
           std::vector<int>& arg, const Better& better) {
    if (rows.empty()) return;
    std::vector<int> reduced;
    for (int col : cols) {
        while (!reduced.empty() &&
               better(rows[reduced.size() - 1], reduced.back(), col))
            reduced.pop_back();
        if (reduced.size() < rows.size()) reduced.push_back(col);
    }
    std::vector<int> odd;
    for (int i = 1; i < (int)rows.size(); i += 2)
        odd.push_back(rows[i]);
    smawk(odd, reduced, arg, better);
    int left = 0;
    for (int i = 0; i < (int)rows.size(); i += 2) {
        int right = (int)reduced.size() - 1;
        if (i + 1 < (int)rows.size()) {
            right = left;
            while (reduced[right] != arg[rows[i + 1]]) ++right;
        }
        int best = reduced[left];
        for (int j = left + 1; j <= right; ++j)
            if (better(rows[i], best, reduced[j])) best = reduced[j];
        arg[rows[i]] = best;
        left = right;
    }
}

// Finite entries only. B's successive differences must not increase.
// Empty input -> empty output. Arithmetic must fit long long.
// O(A.size()+B.size()) time and space.
std::vector<long long> max_plus_concave(
    const std::vector<long long>& A,
    const std::vector<long long>& B) {
    if (A.empty() || B.empty()) return {};
    int n = (int)A.size(), m = (int)B.size();
    std::vector<int> rows(n + m - 1), cols(n), arg(n + m - 1);
    std::iota(rows.begin(), rows.end(), 0);
    std::iota(cols.begin(), cols.end(), 0);
    auto better = [&](int k, int i, int j) {
        // i < j. Invalid cells have a directional ordering.
        if (k < j) return false;      // j is too far right
        if (k - i >= m) return true;  // i is too far left
        return A[i] + B[k - i] <= A[j] + B[k - j];
    };
    smawk(rows, cols, arg, better);
    std::vector<long long> out(n + m - 1);
    for (int k = 0; k < n + m - 1; ++k)
        out[k] = A[arg[k]] + B[k - arg[k]];
    return out;
}

// Both arrays concave: merge their nonincreasing differences.
std::vector<long long> max_plus_both_concave(
    const std::vector<long long>& A,
    const std::vector<long long>& B) {
    if (A.empty() || B.empty()) return {};
    std::vector<long long> out{A[0] + B[0]};
    int i = 1, j = 1;
    while (i < (int)A.size() || j < (int)B.size()) {
        if (j == (int)B.size() ||
            (i < (int)A.size() && A[i] - A[i - 1] >= B[j] - B[j - 1])) {
            out.push_back(out.back() + A[i] - A[i - 1]);
            ++i;
        } else {
            out.push_back(out.back() + B[j] - B[j - 1]);
            ++j;
        }
    }
    return out;
}
} // namespace knapsack_ref
