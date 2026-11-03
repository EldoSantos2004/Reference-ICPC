#include <bits/stdc++.h>

template<bool MIN_QUERY = true, bool INCREASING_SLOPES = false>
struct CHT {
    using ld = long double;

    static constexpr bool FLIP_X =
        MIN_QUERY == INCREASING_SLOPES;

    struct Line {
        ld m, b;
        int cnt;

        std::pair<ld, int> eval(ld x) const {
            return {m * x + b, cnt};
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
        // Treat each intercept symbolically as b + eps * cnt.
        // Compare the cost products first, then count products.
        std::pair<ld, ld> lhs{
            (b.b - a.b) * (b.m - c.m),
            ((ld)b.cnt - a.cnt) * (b.m - c.m)
        };

        std::pair<ld, ld> rhs{
            (c.b - b.b) * (a.m - b.m),
            ((ld)c.cnt - b.cnt) * (a.m - b.m)
        };

        return lhs >= rhs;
    }

    // Slopes follow INCREASING_SLOPES; equal slopes are allowed.
    void add(ld slope, ld intercept, int cnt) {
        ld m = slope, b = intercept;

        if constexpr (!MIN_QUERY) {
            m = -m;
            b = -b;
        }

        if constexpr (FLIP_X)
            m = -m;

        if (!hull.empty() && hull.back().m == m) {
            if (std::pair<ld, int>{hull.back().b, hull.back().cnt}
                <= std::pair<ld, int>{b, cnt}) {
                return;
            }

            hull.pop_back();
        }

        Line line{m, b, cnt};

        while (hull.size() >= 2 &&
               bad(hull[hull.size() - 2], hull.back(), line)) {
            hull.pop_back();
        }

        hull.push_back(line);
        ptr = std::min(ptr, (int)hull.size() - 1);
    }

    // Requires a nonempty hull.
    // x must be nonincreasing if FLIP_X, nondecreasing otherwise.
    std::pair<ld, int> query(ld x) {
        ld X = x;

        if constexpr (FLIP_X)
            X = -X;

        while (ptr + 1 < (int)hull.size() &&
               hull[ptr + 1].eval(X) <= hull[ptr].eval(X)) {
            ++ptr;
        }

        auto [value, cnt] = hull[ptr].eval(X);

        // Counts remain unchanged: both modes prefer fewer on ties.
        if constexpr (!MIN_QUERY)
            value = -value;

        return {value, cnt};
    }
};

/* Example (inside main): minimum, nonincreasing slopes.
CHT<true, false> cht;
cht.add(3, 0, 4);
cht.add(2, 0, 1);
cht.add(1, 0, 3);
auto a = cht.query(-1); // {-3, 4}
auto b = cht.query(0);  // {0, 1}; all values tie, fewer wins
auto c = cht.query(1);  // {1, 3}
*/
