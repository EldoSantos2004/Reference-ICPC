#pragma once
#include "HashCore.hpp"

namespace hashing_ref {
struct Matrix3 {
    u64 a[3][3]{};
    static Matrix3 identity() {
        Matrix3 r;
        for (int i = 0; i < 3; ++i) r.a[i][i] = 1;
        return r;
    }
    friend Matrix3 operator*(const Matrix3& x, const Matrix3& y) {
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int k = 0; k < 3; ++k)
                for (int j = 0; j < 3; ++j)
                    r.a[i][j] = add(r.a[i][j], mul(x.a[i][k], y.a[k][j]));
        return r;
    }
    u64 trace() const { return add(add(a[0][0], a[1][1]), a[2][2]); }
    std::optional<Matrix3> inverse() const {
        u64 b[3][6]{};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) b[i][j] = a[i][j];
            b[i][i + 3] = 1;
        }
        for (int c = 0; c < 3; ++c) {
            int pivot = c;
            while (pivot < 3 && b[pivot][c] == 0) ++pivot;
            if (pivot == 3) return std::nullopt;
            for (int j = 0; j < 6; ++j) std::swap(b[c][j], b[pivot][j]);
            u64 inv = power(b[c][c], MOD - 2);
            for (int j = 0; j < 6; ++j) b[c][j] = mul(b[c][j], inv);
            for (int i = 0; i < 3; ++i) if (i != c) {
                u64 factor = b[i][c];
                for (int j = 0; j < 6; ++j)
                    b[i][j] = sub(b[i][j], mul(factor, b[c][j]));
            }
        }
        Matrix3 r;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) r.a[i][j] = b[i][j + 3];
        return r;
    }
};
struct RotationParameters {
    std::array<Matrix3, 256> letter, inverse;
    RotationParameters() {
        std::uniform_int_distribution<u64> dist(0, MOD - 1);
        for (int c = 0; c < 256; ++c) {
            while (true) {
                for (auto& row : letter[c].a)
                    for (u64& x : row) x = dist(rng());
                auto inv = letter[c].inverse();
                if (inv) { inverse[c] = *inv; break; }
            }
        }
    }
};
inline const RotationParameters& rotation_parameters() {
    static const RotationParameters p;
    return p;
}
// Exact fallback, independent of the fingerprint. O(|a|+|b|).
inline bool exact_rotation(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) return false;
    if (a.empty()) return true;
    assert(a.size() < (size_t)INT_MAX);
    int n = (int)a.size();
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j && b[i] != b[j]) j = pi[j - 1];
        if (b[i] == b[j]) ++j;
        pi[i] = j;
    }
    int matched = 0;
    for (size_t i = 0; i < 2 * a.size() - 1; ++i) {
        char c = a[i % a.size()];
        while (matched && c != b[matched]) matched = pi[matched - 1];
        if (c == b[matched]) ++matched;
        if (matched == n) return true;
    }
    return false;
}

// Rotation invariant FILTER, not an equivalence certificate.
// Same trace family components are not independent random hashes.
class RotationTraceHash {
    std::string text;
    std::vector<Matrix3> pref, inv;
public:
    explicit RotationTraceHash(std::string_view s) : text(s),
        pref(s.size() + 1, Matrix3::identity()), inv(pref) {
        assert(s.size() < (size_t)INT_MAX);
        const auto& p = rotation_parameters();
        for (int i = 0; i < (int)s.size(); ++i) {
            unsigned char c = s[i];
            pref[i + 1] = pref[i] * p.letter[c];
            inv[i + 1] = p.inverse[c] * inv[i];
        }
    }
    std::array<u64, 3> fingerprint(int l, int r) const {
        assert(0 <= l && l <= r && r <= (int)text.size());
        Matrix3 m = inv[l] * pref[r];
        return {(u64)(r - l), m.trace(), (m * m).trace()};
    }
    bool same_rotation(int l, int r, const RotationTraceHash& b,
                       int i, int j) const {
        if (fingerprint(l, r) != b.fingerprint(i, j)) return false;
        return exact_rotation(std::string_view(text).substr(l, r - l),
                              std::string_view(b.text).substr(i, j - i));
    }
};
} // namespace hashing_ref
