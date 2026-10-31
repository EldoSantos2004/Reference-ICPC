#include <bits/stdc++.h>

template<bool MIN_QUERY = true, bool INCREASING_SLOPES = false>
struct CHT {
    using i128 = __int128_t;
    using u128 = __uint128_t;

    static constexpr bool FLIP_X =
        MIN_QUERY == INCREASING_SLOPES;

    struct Line {
        i128 m, b;

        i128 eval(i128 x) const {
            return m * x + b;
        }
    };

    std::vector<Line> hull;
    int ptr = 0;

    void clear() {
        hull.clear();
        ptr = 0;
    }

    bool empty() const {
        return hull.empty();
    }

    static bool bad(const Line& a, const Line& b, const Line& c) {
        // Internally: decreasing slopes, minimum queries.
        i128 x = b.b - a.b;
        i128 y = c.b - b.b;

        if ((x < 0) != (y < 0))
            return x >= 0;

        // Unsigned magnitudes avoid signed cross-product overflow.
        u128 lhs = (u128)(x < 0 ? -x : x)
                 * (u128)(b.m - c.m);

        u128 rhs = (u128)(y < 0 ? -y : y)
                 * (u128)(a.m - b.m);

        return x < 0 ? lhs <= rhs : lhs >= rhs;
    }

    // Amortized O(1).
    void add(long long slope, long long intercept) {
        i128 m = slope, b = intercept;

        if constexpr (!MIN_QUERY) {
            m = -m;
            b = -b;
        }
        if constexpr (FLIP_X)
            m = -m;

        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b)
                return;

            hull.pop_back();
        }

        Line line{m, b};

        while (hull.size() >= 2 &&
               bad(hull[hull.size() - 2], hull.back(), line)) {
            hull.pop_back();
        }

        hull.push_back(line);
        ptr = std::min(ptr, (int)hull.size() - 1);
    }

    // Amortized O(1). Requires the query order from the table.
    i128 query(long long x) {
        i128 X = x;

        if constexpr (FLIP_X)
            X = -X;

        while (ptr + 1 < (int)hull.size() &&
               hull[ptr + 1].eval(X) <= hull[ptr].eval(X)) {
            ++ptr;
        }

        i128 value = hull[ptr].eval(X);
        return MIN_QUERY ? value : -value;
    }

    // O(log n). Arbitrary query order; does not change ptr.
    i128 query_bs(long long x) const {
        i128 X = x;

        if constexpr (FLIP_X)
            X = -X;

        int l = 0, r = (int)hull.size() - 1;

        while (l < r) {
            int mid = l + (r - l) / 2;

            if (hull[mid + 1].eval(X) <= hull[mid].eval(X))
                l = mid + 1;
            else
                r = mid;
        }

        i128 value = hull[l].eval(X);
        return MIN_QUERY ? value : -value;
    }
};

/* Example (inside main): minimum, nondecreasing slopes.
CHT<true, true> cht;
cht.add(1, 0);  // y = x
cht.add(2, -1); // y = 2x - 1
cht.add(3, 0);  // y = 3x
auto a = cht.query(2);  // 2
auto b = cht.query(0);  // -1; nonincreasing x
auto c = cht.query_bs(4); // 4; arbitrary x; ptr unchanged
auto d = cht.query(-2); // -6
*/
