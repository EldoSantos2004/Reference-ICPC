/*
    RECURSIVE SEGMENT TREE - C++17
    =============================

    Compile and run:
      g++ -std=c++17 -O2 -Wall -Wextra -pedantic segtree_examples.cpp -o segtree_examples
      ./segtree_examples

    Copy SegTree into your contest code, then choose:
      1. T: the value/summary stored in each node.
      2. merge(left, right): how to combine two consecutive segments.
      3. identity: the summary of an empty segment.

    Requirements:
      merge(merge(a, b), c) == merge(a, merge(b, c))   (associative)
      merge(identity, x) == merge(x, identity) == x

    Commutativity is NOT required. Left-to-right order is preserved.
    Subtraction and division are not associative, so cannot be used directly.

    API:
      SegTree st(values, identity, merge);   // type deduction in C++17
      st.update(pos, value);                // point assignment, NOT increment
      st.query(l, r);                       // 0-indexed, both endpoints included

    Nonempty queries require 0 <= l <= r < n. Updates require 0 <= pos < n.
    An empty query (l > r) returns identity; querying an empty tree does too.
    This implementation has point updates only; there is no lazy propagation.

    With constant-size T and constant-time merge:
      Build O(n), update/query O(log n), storage O(n).
    Otherwise multiply by the appropriate copy/merge cost; string concatenation
    and variable-size matrix multiplication are not constant-time operations.

    CONTENTS: 18 independent examples
      01 sum                      10 minimum + occurrence count
      02 minimum                  11 maximum + leftmost index
      03 maximum                  12 sum + count (range average)
      04 GCD                      13 maximum nonempty subarray sum
      05 LCM                      14 balanced parentheses
      06 product modulo MOD       15 string concatenation
      07 bitwise OR               16 matrix multiplication
      08 bitwise AND              17 affine-function composition
      09 bitwise XOR              18 permutation composition

    Each example prints its result and shows the expected output in comments.
    Arithmetic is assumed to fit its type unless modular arithmetic is used.
*/

#include <bits/stdc++.h>
using namespace std;

template<class T, class F>
struct SegTree {
    int n;
    vector<T> tree;
    T identity;
    F merge;

    SegTree(const vector<T>& a, T identity, F merge)
        : n(static_cast<int>(a.size())), tree(4 * max(1, n), identity),
          identity(identity), merge(merge) {
        if (n > 0) build(1, 0, n - 1, a);
    }

    void build(int p, int l, int r, const vector<T>& a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p) {
        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int pos, const T& value) {
        update(1, 0, n - 1, pos, value);
    }

    void update(int p, int l, int r, int pos, const T& value) {
        if (l == r) {
            tree[p] = value;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            update(p * 2, l, m, pos, value);
        else
            update(p * 2 + 1, m + 1, r, pos, value);
        pull(p);
    }

    T query(int l, int r) const {
        if (n == 0 || l > r) return identity;
        return query(1, 0, n - 1, l, r);
    }

    T query(int p, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return identity;
        if (ql <= l && r <= qr) return tree[p];
        int m = (l + r) / 2;
        return merge(
            query(p * 2, l, m, ql, qr),
            query(p * 2 + 1, m + 1, r, ql, qr)
        );
    }
};

constexpr long long MOD = 1'000'000'007;

// 01. SUM: identity = 0.
void example_sum() {
    vector<long long> a = {2, 5, 1, 4};
    SegTree st(a, 0LL, [](long long x, long long y) {
        return x + y;
    });
    cout << "01 sum: " << st.query(1, 3);  // 10
    st.update(2, 7);
    cout << " -> " << st.query(1, 3) << '\n';  // 16
}

// 02. MINIMUM: identity = largest representable value.
void example_minimum() {
    vector<long long> a = {8, 3, 6, 1};
    SegTree st(a, LLONG_MAX, [](long long x, long long y) {
        return min(x, y);
    });
    cout << "02 minimum: " << st.query(0, 2) << '\n';  // 3
}

// 03. MAXIMUM: identity = smallest representable value.
void example_maximum() {
    vector<long long> a = {-8, -3, -6, -1};
    SegTree st(a, LLONG_MIN, [](long long x, long long y) {
        return max(x, y);
    });
    cout << "03 maximum: " << st.query(0, 2) << '\n';  // -3
}

// 04. GCD: identity = 0, since gcd(0, x) = x for nonnegative x.
// Use nonnegative values; |LLONG_MIN| cannot be represented as long long.
void example_gcd() {
    vector<long long> a = {12, 18, 30, 42};
    SegTree st(a, 0LL, [](long long x, long long y) {
        return gcd(x, y);
    });
    cout << "04 gcd: " << st.query(0, 3) << '\n';  // 6
}

// 05. LCM: identity = 1. Every intermediate LCM must fit in long long.
// Do not take LCM modulo MOD: that would lose information needed for later merges.
void example_lcm() {
    vector<long long> a = {4, 6, 10};
    SegTree st(a, 1LL, [](long long x, long long y) {
        return lcm(x, y);
    });
    cout << "05 lcm: " << st.query(0, 2) << '\n';  // 60
}

// 06. MODULAR PRODUCT: identity = 1.
// Store residues in [0, MOD). This MOD allows two residues to multiply in long long.
void example_product() {
    vector<long long> a = {2, 3, 4, 5};
    SegTree st(a, 1LL, [](long long x, long long y) {
        return x * y % MOD;
    });
    cout << "06 product: " << st.query(1, 3) << '\n';  // 60
}

// 07. BITWISE OR: identity = 0.
void example_or() {
    vector<uint64_t> a = {1, 2, 4, 8};
    SegTree st(a, uint64_t{0}, [](uint64_t x, uint64_t y) {
        return x | y;
    });
    cout << "07 bitwise OR: " << st.query(0, 2) << '\n';  // 7
}

// 08. BITWISE AND: identity = all bits set.
void example_and() {
    vector<uint64_t> a = {15, 7, 3};
    SegTree st(a, ~uint64_t{0}, [](uint64_t x, uint64_t y) {
        return x & y;
    });
    cout << "08 bitwise AND: " << st.query(0, 2) << '\n';  // 3
}

// 09. BITWISE XOR: identity = 0.
void example_xor() {
    vector<uint64_t> a = {5, 3, 5};
    SegTree st(a, uint64_t{0}, [](uint64_t x, uint64_t y) {
        return x ^ y;
    });
    cout << "09 bitwise XOR: " << st.query(0, 2) << '\n';  // 3
}

// 10. MINIMUM + NUMBER OF OCCURRENCES.
struct MinCount {
    long long value;
    int count;
};

void example_min_count() {
    vector<long long> values = {4, 1, 3, 1, 1};
    vector<MinCount> a;
    for (long long x : values) a.push_back({x, 1});

    SegTree st(a, MinCount{LLONG_MAX, 0}, [](MinCount x, MinCount y) {
        if (x.value < y.value) return x;
        if (y.value < x.value) return y;
        return MinCount{x.value, x.count + y.count};
    });
    auto ans = st.query(0, 4);
    cout << "10 minimum + count: " << ans.value << ' ' << ans.count;
    st.update(1, MinCount{7, 1});
    ans = st.query(0, 4);
    cout << " -> " << ans.value << ' ' << ans.count << '\n';  // 1 3 -> 1 2
}

// 11. MAXIMUM + LEFTMOST INDEX. index = -1 marks the empty summary.
struct MaxIndex {
    long long value;
    int index;
};

void example_max_index() {
    vector<long long> values = {4, 9, 2, 9};
    vector<MaxIndex> a;
    for (int i = 0; i < static_cast<int>(values.size()); i++)
        a.push_back({values[i], i});

    SegTree st(a, MaxIndex{0, -1}, [](MaxIndex x, MaxIndex y) {
        if (x.index == -1) return y;
        if (y.index == -1) return x;
        if (x.value != y.value) return x.value > y.value ? x : y;
        return x.index < y.index ? x : y;
    });
    auto ans = st.query(0, 3);
    cout << "11 maximum + index: " << ans.value << ' ' << ans.index << '\n'; // 9 1
    st.update(1, MaxIndex{0, 1});  // Keep the updated position's index.
}

// 12. SUM + COUNT, then divide once to get the range average.
// Averaging two averages directly is not a valid associative merge.
struct SumCount {
    long long sum;
    int count;
};

void example_average() {
    vector<SumCount> a = {{2, 1}, {4, 1}, {9, 1}};
    SegTree st(a, SumCount{0, 0}, [](SumCount x, SumCount y) {
        return SumCount{x.sum + y.sum, x.count + y.count};
    });
    auto ans = st.query(0, 2);
    cout << "12 average: " << static_cast<double>(ans.sum) / ans.count << '\n'; // 5
}

// 13. MAXIMUM NONEMPTY SUBARRAY SUM.
// A node stores total sum, best nonempty prefix/suffix, and best nonempty subarray.
// len = 0 identifies the empty summary; this avoids fake infinity arithmetic.
struct MaxSubarray {
    long long sum, prefix, suffix, best;
    int len;
};

MaxSubarray subarray_leaf(long long x) {
    return {x, x, x, x, 1};
}

void example_max_subarray() {
    vector<long long> values = {-2, 3, -1, 4, -5};
    vector<MaxSubarray> a;
    for (long long x : values) a.push_back(subarray_leaf(x));

    SegTree st(a, MaxSubarray{0, 0, 0, 0, 0}, [](MaxSubarray x, MaxSubarray y) {
        if (x.len == 0) return y;
        if (y.len == 0) return x;
        return MaxSubarray{
            x.sum + y.sum,
            max(x.prefix, x.sum + y.prefix),
            max(y.suffix, y.sum + x.suffix),
            max({x.best, y.best, x.suffix + y.prefix}),
            x.len + y.len
        };
    });
    cout << "13 maximum subarray: " << st.query(0, 4).best; // 6: [3, -1, 4]
    st.update(2, subarray_leaf(-10));
    cout << " -> " << st.query(0, 4).best << '\n';  // 4
    // An all-negative, nonempty query returns its largest element, not 0.
}

// 14. BALANCED PARENTHESES: '(' = +1, ')' = -1.
// minimum_prefix includes the empty prefix, whose sum is 0.
// A queried substring is balanced iff sum == 0 and minimum_prefix >= 0.
struct Brackets {
    int sum, minimum_prefix;
};

Brackets bracket_leaf(char c) {
    int x = c == '(' ? 1 : -1;
    return {x, min(0, x)};
}

void example_brackets() {
    string s = "(())()";
    vector<Brackets> a;
    for (char c : s) a.push_back(bracket_leaf(c));

    SegTree st(a, Brackets{0, 0}, [](Brackets x, Brackets y) {
        return Brackets{
            x.sum + y.sum,
            min(x.minimum_prefix, x.sum + y.minimum_prefix)
        };
    });
    auto balanced = [](Brackets x) {
        return x.sum == 0 && x.minimum_prefix >= 0;
    };
    cout << "14 balanced parentheses: " << balanced(st.query(0, 3)); // 1: (())
    cout << ' ' << balanced(st.query(1, 4)) << '\n';               // 0: "())("
    st.update(0, bracket_leaf(')'));
}

// 15. STRING CONCATENATION: associative, but NOT commutative.
// Identity = empty string. Useful for demonstrating ordering.
// Concatenation/copying takes time proportional to string length: the usual
// O(log n) bound counts merges, not character work. Avoid large strings in CP.
void example_strings() {
    vector<string> a = {"ab", "C", "de", "F"};
    SegTree st(a, string{}, [](const string& x, const string& y) {
        return x + y;
    });
    cout << "15 concatenation: " << st.query(1, 3); // CdeF
    st.update(2, string{"XY"});
    cout << " -> " << st.query(1, 3) << '\n';     // CXYF
}

// 16. MATRIX MULTIPLICATION: query(l, r) = A[l] * ... * A[r].
// Fixed 2x2 matrices, entries stored as residues in [0, MOD).
// For d x d matrices with naive multiplication: O(d^3 log n) per query/update.
struct Matrix {
    long long a[2][2]{};
};

Matrix multiply(const Matrix& x, const Matrix& y) {
    Matrix z;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                z.a[i][j] = (z.a[i][j] + x.a[i][k] * y.a[k][j]) % MOD;
    return z;
}

void example_matrices() {
    vector<Matrix> a = {
        {{{1, 2}, {3, 4}}},
        {{{5, 6}, {7, 8}}},
        {{{2, 0}, {0, 2}}}
    };
    Matrix identity;
    identity.a[0][0] = identity.a[1][1] = 1;

    SegTree st(a, identity, multiply);
    Matrix ans = st.query(0, 1);
    cout << "16 matrix product: "
         << ans.a[0][0] << ' ' << ans.a[0][1] << "; "
         << ans.a[1][0] << ' ' << ans.a[1][1] << '\n'; // 19 22; 43 50
    st.update(1, identity);
    ans = st.query(1, 2);  // I * 2I = 2I.
    cout << "   after update: "
         << ans.a[0][0] << ' ' << ans.a[0][1] << "; "
         << ans.a[1][0] << ' ' << ans.a[1][1] << '\n'; // 2 0; 0 2
}

// 17. AFFINE-FUNCTION COMPOSITION: f(x) = a*x + b modulo MOD.
// Query applies f[l] FIRST, then f[l+1], ..., then f[r].
// Thus merge(left, right) represents right(left(x)), not left(right(x)).
// Coefficients and inputs are stored as residues in [0, MOD).
struct Affine {
    long long a, b;
    long long apply(long long x) const {
        return (a * x + b) % MOD;
    }
};

void example_affine() {
    vector<Affine> a = {{2, 1}, {3, 4}}; // f0(x)=2x+1, f1(x)=3x+4
    SegTree st(a, Affine{1, 0}, [](Affine left, Affine right) {
        return Affine{
            right.a * left.a % MOD,
            (right.a * left.b + right.b) % MOD
        };
    });
    Affine result = st.query(0, 1); // f1(f0(x)) = 6x+7
    cout << "17 affine composition: " << result.apply(5); // 37
    st.update(0, Affine{1, 10});  // f0(x) = x+10
    cout << " -> " << st.query(0, 1).apply(5) << '\n'; // 49
}

// 18. PERMUTATION COMPOSITION on {0, 1, 2}.
// p[i] = where input i is sent. Apply the left permutation first, then right.
// Therefore merge(left, right)[i] = right[left[i]]. Identity sends i to i.
void example_permutations() {
    using Permutation = array<int, 3>;
    vector<Permutation> a = {
        {1, 0, 2},  // Swap 0 and 1.
        {0, 2, 1}   // Swap 1 and 2.
    };
    Permutation identity = {0, 1, 2};
    SegTree st(a, identity, [](const Permutation& left, const Permutation& right) {
        Permutation result{};
        for (int i = 0; i < 3; i++) result[i] = right[left[i]];
        return result;
    });
    auto ans = st.query(0, 1);
    cout << "18 permutation composition:";
    for (int x : ans) cout << ' ' << x;
    cout << '\n'; // 2 0 1
    st.update(0, identity);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    example_sum();
    example_minimum();
    example_maximum();
    example_gcd();
    example_lcm();
    example_product();
    example_or();
    example_and();
    example_xor();
    example_min_count();
    example_max_index();
    example_average();
    example_max_subarray();
    example_brackets();
    example_strings();
    example_matrices();
    example_affine();
    example_permutations();
}
