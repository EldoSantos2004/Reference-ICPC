// From repository root: g++ -std=c++17 -O2 tests/hashing_tools.cpp -o /tmp/hash-tests
#include "../strings/HashRecipes.hpp"
#include "../strings/CollectionHash.hpp"
#include "../strings/ZobristHash.hpp"
#include "../strings/DynamicStringHash.hpp"
#include "../strings/RotationTraceHash.hpp"
using namespace std;
using namespace hashing_ref;
mt19937 gen(836451);
int rnd(int n) { return gen() % n; }
string word(int n, int alphabet = 7) {
    string s(n, '\0');
    for (char& c : s) c = (char)rnd(alphabet);
    return s;
}
int cmp(const string& a, const string& b) {
    return (a > b) - (a < b);
}
bool naive_rotation(const string& a, const string& b) {
    return a.size() == b.size() && (a.empty() || (a + a).find(b) != string::npos);
}
bool same_matrix(const Matrix3& a, const Matrix3& b) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (a.a[i][j] != b.a[i][j]) return false;
    return true;
}
int main() {
    rng().seed(714159265);
    for (int z = 0; z < 6000; ++z) {
        string a = word(rnd(65), z % 2 ? 256 : 7);
        string b = word(rnd(65), z % 2 ? 256 : 7);
        PrefixHash A(a), B(b), C(a + b);
        Hash identity;
        assert(A.whole() * B.whole() == C.whole());
        assert(A.whole() * identity == A.whole());
        assert(identity * A.whole() == A.whole());
        assert(C.whole() / A.whole() == B.whole());
        assert(A.whole() / A.whole() == identity);
        int p = rnd(10), q = rnd(10);
        string aa, bb;
        for (int i = 0; i < p; ++i) aa += a;
        for (int i = 0; i < q; ++i) bb += b;
        assert(repeated(A.whole(), p) == PrefixHash(aa).whole());
        assert(compare_repeated(A, p, B, q) == cmp(aa, bb));
        assert(compare_repeated_exact(A, p, B, q) == cmp(aa, bb));
        for (int k = 0; k < 12; ++k) {
            int l = rnd(a.size() + 1), r = rnd(a.size() + 1);
            int i = rnd(b.size() + 1), j = rnd(b.size() + 1);
            if (l > r) swap(l, r);
            if (i > j) swap(i, j);
            assert(A.get(l, r) == PrefixHash(a.substr(l, r - l)).whole());
            assert(compare(A, l, r, B, i, j) == cmp(a.substr(l, r - l), b.substr(i, j - i)));
            int n = 0;
            while (l + n < (int)a.size() && i + n < (int)b.size() && a[l + n] == b[i + n]) ++n;
            assert(lcp(A, l, B, i) == n);
            int period = rnd(a.size() + 3);
            bool ok = period > 0 && period <= r - l;
            if (ok) for (int x = l; x + period < r; ++x) ok &= a[x] == a[x + period];
            assert(has_period(A, l, r, period) == ok);
            assert(is_block_power(A, l, r, period) == (ok && (r - l) % period == 0));
        }
    }
    for (int z = 0; z < 500; ++z) {
        string s = word(rnd(80), 256);
        DynamicStringHash d(s);
        for (int k = 0; k < 200; ++k) {
            if (!s.empty() && rnd(3) == 0) {
                int i = rnd(s.size());
                s[i] = (char)rnd(256);
                d.set(i, (unsigned char)s[i]);
            }
            int l = rnd(s.size() + 1), r = rnd(s.size() + 1);
            if (l > r) swap(l, r);
            string sub = s.substr(l, r - l), rev = sub;
            reverse(rev.begin(), rev.end());
            assert(d.get(l, r) == PrefixHash(sub).whole());
            assert(d.reversed(l, r) == PrefixHash(rev).whole());
            assert(d.palindrome(l, r) == (sub == rev));
        }
    }
    for (int z = 0; z < 2000; ++z) {
        vector<long long> a(rnd(70));
        for (auto& x : a) x = rnd(30) - 15;
        if (!a.empty() && z % 3 == 0) a[0] = LLONG_MIN;
        if (a.size() > 1 && z % 5 == 0) a[1] = LLONG_MAX;
        MultisetPrefix pref(a);
        for (int k = 0; k < 25; ++k) {
            int l = rnd(a.size() + 1), r = rnd(a.size() + 1);
            if (l > r) swap(l, r);
            MultisetHash h;
            vector<long long> sub(a.begin() + l, a.begin() + r);
            shuffle(sub.begin(), sub.end(), gen);
            for (long long x : sub) h.insert((u64)x);
            assert(h == pref.get(l, r));
            assert(pref.get(0, l) + pref.get(l, r) == pref.get(0, r));
            for (long long x : sub) h.erase((u64)x);
            assert(h == MultisetHash{});
        }
    }
    MultisetPrefix letters("abccba");
    assert(letters.get(0, 3) == letters.get(3, 6));
    MultisetPrefix aa("aa"), bb("bb");
    assert(!(aa.get(0, 2) == bb.get(0, 2)));
    MultisetHash unit, largest;
    unit.insert(7);
    u64 bits = numeric_limits<u64>::max();
    while (bits) {
        if (bits & 1) largest = largest + unit;
        bits >>= 1;
        if (bits) unit = unit + unit;
    }
    auto saved = largest;
    try { largest.insert(7); assert(false); }
    catch (const overflow_error&) {}
    assert(largest == saved);
    SetHash sethash;
    set<u64> exactset;
    for (int k = 0; k < 10000; ++k) {
        u64 x = rnd(100);
        if (rnd(2)) assert(sethash.insert(x) == exactset.insert(x).second);
        else assert(sethash.erase(x) == (exactset.erase(x) != 0));
        SetHash rebuild;
        for (u64 v : exactset) rebuild.insert(v);
        assert(sethash == rebuild);
    }
    ZobristContext context(50, 8);
    ZobristState board(context);
    for (int k = 0; k < 10000; ++k) {
        board.set(rnd(50), rnd(9) - 1);
        ZobristState rebuilt(context);
        for (int i = 0; i < 50; ++i) rebuilt.set(i, board.value[i]);
        assert(board == rebuilt);
        auto copy = board;
        int i = rnd(50), old = board.value[i], state = rnd(9) - 1;
        board.set(i, state);
        board.set(i, old);
        assert(board == copy);
    }
    assert(!Matrix3{}.inverse());
    Matrix3 permutation;
    permutation.a[0][1] = permutation.a[1][2] = permutation.a[2][0] = 1;
    assert(same_matrix(permutation * *permutation.inverse(), Matrix3::identity()));
    for (int z = 0; z < 1000; ++z) {
        Matrix3 m;
        for (auto& row : m.a) for (u64& x : row) x = rng()() % MOD;
        auto inv = m.inverse();
        if (inv) {
            assert(same_matrix(m * *inv, Matrix3::identity()));
            assert(same_matrix(*inv * m, Matrix3::identity()));
        }
    }
    for (int z = 0; z < 1500; ++z) {
        string a = word(rnd(45), z % 2 ? 256 : 3);
        RotationTraceHash A(a);
        for (int k = 0; k < 12; ++k) {
            int l = rnd(a.size() + 1), r = rnd(a.size() + 1);
            if (l > r) swap(l, r);
            string b = a.substr(l, r - l);
            if (!b.empty()) rotate(b.begin(), b.begin() + rnd(b.size()), b.end());
            if (!b.empty() && rnd(2)) b[rnd(b.size())] = (char)rnd(256);
            RotationTraceHash B(b);
            bool want = naive_rotation(a.substr(l, r - l), b);
            assert(A.same_rotation(l, r, B, 0, b.size()) == want);
            assert(exact_rotation(a.substr(l, r - l), b) == want);
            if (want) assert(A.fingerprint(l, r) == B.fingerprint(0, b.size()));
        }
    }
    // Exhaust all binary words of lengths <= 8 and all their rotations.
    for (int n = 0; n <= 8; ++n) for (int mask = 0; mask < (1 << n); ++mask) {
        string a(n, 'a');
        for (int i = 0; i < n; ++i) a[i] += (mask >> i) & 1;
        RotationTraceHash A(a);
        for (int shift = 0; shift < max(1, n); ++shift) {
            string b = a.substr(shift) + a.substr(0, shift);
            assert(A.same_rotation(0, n, RotationTraceHash(b), 0, n));
        }
    }
    PrefixHash one("x"), two("xx");
    u64 max_length = numeric_limits<u64>::max();
    assert(repeated(one.whole(), max_length).len == max_length);
    assert(compare_repeated(one, max_length, two, max_length / 2) == 1);
    assert(compare_repeated(one, max_length, one, max_length) == 0);
    assert(compare_repeated_exact(one, max_length, two, max_length / 2) == 1);
    assert(compare_repeated_exact(one, max_length, one, max_length) == 0);
    try { repeated(two.whole(), max_length); assert(false); }
    catch (const overflow_error&) {}
    try { repeated(one.whole(), max_length) * one.whole(); assert(false); }
    catch (const overflow_error&) {}
    cout << "PASS: hashing algebra, static/dynamic strings, virtual powers, collections, Zobrist, matrices and rotations.\n";
}
