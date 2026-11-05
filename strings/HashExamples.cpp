#include "HashRecipes.hpp"
#include "CollectionHash.hpp"
#include "ZobristHash.hpp"
#include "DynamicStringHash.hpp"
#include "RotationTraceHash.hpp"
using namespace std;
using namespace hashing_ref;

int main() {
    PrefixHash a("ab"), b("abab"), s("abcabc");
    cout << (repeated(a.whole(), 2) == b.whole()) << '\n'; // 1
    cout << (s.get(3, 6) == s.get(0, 3)) << '\n';        // 1
    cout << lcp(s, 0, s, 3) << '\n';                     // 3
    cout << is_block_power(s, 0, 6, 3) << '\n';          // 1
    // Compare two virtual strings of length 2*10^18.
    cout << compare_repeated_exact(a, 1000000000000000000ULL,
                            b, 500000000000000000ULL) << '\n'; // 0

    MultisetPrefix p({4, 1, 4, 4, 4, 1});
    cout << (p.get(0, 3) == p.get(3, 6)) << '\n'; // 1: same counts
    SetHash x, y;
    x.insert(4); x.insert(4); y.insert(4);
    cout << (x == y) << '\n'; // 1: duplicate insertion is ignored

    ZobristContext context(8, 3); // Eight slots, states 0,1,2.
    ZobristState board(context), copy(context);
    board.set(2, 1); copy.set(2, 1);
    cout << (board == copy) << '\n'; // 1
    board.set(2, -1); board.set(5, 1); // Move, clearing the old slot.
    cout << (board == copy) << '\n'; // 0 (probabilistic)

    DynamicStringHash d("abca");
    cout << d.palindrome(0, 4) << '\n'; // 0
    d.set(2, 'b');
    cout << d.palindrome(0, 4) << '\n'; // 1: "abba"

    RotationTraceHash r("abcab"), t("cabab"), u("abacb");
    cout << r.same_rotation(0, 5, t, 0, 5) << '\n'; // 1, exact
    cout << r.same_rotation(0, 5, u, 0, 5) << '\n'; // 0, exact
}
