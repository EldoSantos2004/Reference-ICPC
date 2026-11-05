#pragma once
#include "HashCore.hpp"

namespace hashing_ref {
// Fixed positions, states 0..states-1; -1 means empty.
// All positions contribute, including their empty state.
struct ZobristContext {
    int positions, states;
    std::vector<std::vector<std::array<u64, 2>>> token;
    ZobristContext(int n, int k) : positions(n), states(k),
        token(n, std::vector<std::array<u64, 2>>(k + 1)) {
        assert(n >= 0 && k > 0);
        for (auto& row : token)
            for (auto& x : row) x = {rng()(), rng()()};
    }
};
struct ZobristState {
    // Context must outlive the state and remain unchanged.
    const ZobristContext* context;
    std::vector<int> value;
    std::array<u64, 2> h{0, 0};
    explicit ZobristState(const ZobristContext& c) : context(&c),
        value(c.positions, -1) {
        for (int i = 0; i < c.positions; ++i)
            for (int k = 0; k < 2; ++k) h[k] ^= c.token[i][0][k];
    }
    ZobristState(ZobristContext&&) = delete;
    void set(int position, int state) {
        assert(0 <= position && position < context->positions);
        assert(-1 <= state && state < context->states);
        auto& old = context->token[position][value[position] + 1];
        auto& next = context->token[position][state + 1];
        for (int k = 0; k < 2; ++k) h[k] ^= old[k] ^ next[k];
        value[position] = state;
    }
    auto key() const { return h; } // Use with this context only.
    friend bool operator==(const ZobristState& a, const ZobristState& b) {
        assert(a.context == b.context);
        return a.h == b.h;
    }
};
} // namespace hashing_ref
