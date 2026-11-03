// C++17: useful library functions with runnable examples.
// Iterator ranges are [first, last): the last iterator is excluded.
// For a vector subrange [l, r], use begin()+l, begin()+r+1.
#include <bits/stdc++.h>
using namespace std;

// Only a helper for displaying vectors; the examples use standard functions.
template<class T>
void show(const char* name, const vector<T>& v) {
    cout << name << ':';
    for (const auto& x : v) cout << ' ' << x;
    cout << '\n';
}

void ordering_examples() {
    vector<int> v = {3, 1, 4, 2};
    reverse(v.begin(), v.end());
    show("reverse", v); // 2 4 1 3
    reverse(v.begin() + 1, v.begin() + 3);
    show("reverse subrange", v); // 2 1 4 3

    sort(v.begin(), v.end());
    show("sort", v); // 1 2 3 4
    sort(v.begin(), v.end(), greater<int>());
    show("sort descending", v); // 4 3 2 1

    // Comparator returns true when a must precede b; do not use <=.
    vector<pair<int, int>> p = {{3, 1}, {1, 2}, {2, 1}};
    stable_sort(p.begin(), p.end(), [](auto a, auto b) {
        return a.second < b.second;
    });
    // p = {{3, 1}, {2, 1}, {1, 2}}: ties keep their original order.
    cout << "stable_sort:";
    for (auto [a, b] : p) cout << ' ' << a << ',' << b;
    cout << '\n';

    v = {1, 2, 3, 4, 5};
    rotate(v.begin(), v.begin() + 2, v.end()); // left rotation by 2
    show("rotate left", v); // 3 4 5 1 2
    rotate(v.begin(), v.end() - 1, v.end()); // right rotation by 1
    show("rotate right", v); // 2 3 4 5 1

    v = {9, 2, 7, 1, 5};
    nth_element(v.begin(), v.begin() + 2, v.end());
    cout << "third smallest: " << v[2] << '\n'; // 5
    // Elements before/after v[2] are partitioned, not fully sorted.
    partial_sort(v.begin(), v.begin() + 3, v.end());
    show("three smallest", vector<int>(v.begin(), v.begin() + 3));
    // 1 2 5. partial_sort sorts only the chosen prefix.

    v = {1, 2, 3};
    next_permutation(v.begin(), v.end());
    show("next_permutation", v); // 1 3 2
    prev_permutation(v.begin(), v.end());
    show("prev_permutation", v); // 1 2 3
    // To enumerate all distinct permutations: sort first, then do/while.
    int permutations = 0;
    do { ++permutations; }
    while (next_permutation(v.begin(), v.end()));
    cout << "permutations: " << permutations << '\n'; // 6
    // Returning false also wraps to the first (sorted) permutation.
}

void searching_examples() {
    // These binary-search algorithms require the matching sorted order.
    vector<int> v = {1, 2, 2, 2, 5};
    auto lo = lower_bound(v.begin(), v.end(), 2); // first value >= 2
    auto hi = upper_bound(v.begin(), v.end(), 2); // first value > 2
    cout << "bounds: " << lo - v.begin() << ' ' << hi - v.begin();
    cout << ' ' << hi - lo << '\n'; // 1 4 3 (three copies of 2)
    cout << "binary_search: ";
    cout << binary_search(v.begin(), v.end(), 5) << '\n'; // 1
    auto [first, last] = equal_range(v.begin(), v.end(), 2);
    cout << "equal_range count: " << last - first << '\n'; // 3
    // A bound may return end(); check before dereferencing it.

    v = {7, 4, 9, 2}; // find/find_if do not require sorted input.
    auto it = find(v.begin(), v.end(), 9);
    if (it != v.end()) cout << "find index: " << it - v.begin() << '\n'; // 2
    it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    if (it != v.end()) cout << "first even: " << *it << '\n'; // 4

    cout << "count: " << count(v.begin(), v.end(), 4) << '\n'; // 1
    cout << "count_if: " << count_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    }) << '\n'; // 2
    auto positive = [](int x) { return x > 0; };
    auto negative = [](int x) { return x < 0; };
    cout << "all/any/none: " << all_of(v.begin(), v.end(), positive);
    cout << ' ' << any_of(v.begin(), v.end(), negative);
    cout << ' ' << none_of(v.begin(), v.end(), negative) << '\n'; // 1 0 1

    // Dereference min/max iterators only when the range is nonempty.
    auto [mn, mx] = minmax_element(v.begin(), v.end());
    cout << "min/max: " << *mn << ' ' << *mx << '\n'; // 2 9
    cout << "clamp: " << clamp(15, 0, 10) << '\n'; // 10
    cout << "is_sorted: " << is_sorted(v.begin(), v.end()) << '\n'; // 0
}

void editing_examples() {
    vector<int> v = {3, 1, 3, 2, 1};
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    show("sort + unique", v); // 1 2 3
    // unique removes adjacent duplicates only; erase changes vector size.

    v = {1, 2, 3, 2, 4};
    v.erase(remove(v.begin(), v.end(), 2), v.end());
    show("erase-remove", v); // 1 3 4
    v.erase(remove_if(v.begin(), v.end(), [](int x) {
        return x % 2 != 0;
    }), v.end());
    show("erase-remove_if", v); // 4
    // remove/remove_if alone do not shrink the container.

    v = {1, 2, 1, 3};
    replace(v.begin(), v.end(), 1, 9);
    show("replace", v); // 9 2 9 3
    fill(v.begin(), v.begin() + 2, 4);
    show("fill prefix", v); // 4 4 9 3

    vector<int> doubled(v.size());
    transform(v.begin(), v.end(), doubled.begin(), [](int x) {
        return 2 * x;
    });
    show("transform", doubled); // 8 8 18 6
    vector<int> evens;
    copy_if(v.begin(), v.end(), back_inserter(evens), [](int x) {
        return x % 2 == 0;
    });
    show("copy_if even", evens); // 4 4
    // For copy/transform into begin(), allocate output elements first.
    // back_inserter grows a vector with push_back instead.
}

void numeric_examples() {
    vector<int> v = {2, 5, 3};
    cout << "sum: " << accumulate(v.begin(), v.end(), 0LL) << '\n'; // 10
    // 0LL makes the accumulator long long; 0 would make it int.
    vector<int> ids(5);
    iota(ids.begin(), ids.end(), 10);
    show("iota", ids); // 10 11 12 13 14

    vector<long long> prefix(v.size()), difference(v.size());
    partial_sum(v.begin(), v.end(), prefix.begin());
    show("partial_sum", prefix); // 2 7 10
    // partial_sum accumulates in the input value type, here int.
    // For large sums, use vector<long long> as the input too.
    adjacent_difference(prefix.begin(), prefix.end(), difference.begin());
    show("adjacent_difference", difference); // 2 5 3

    vector<int> weights = {4, 1, 2};
    cout << "dot product: ";
    cout << inner_product(v.begin(), v.end(), weights.begin(), 0LL);
    cout << '\n'; // 19 = 2*4 + 5*1 + 3*2
    // Multiplication still uses the element types; use long long inputs
    // if an individual product might overflow int.
    cout << "gcd/lcm: " << gcd(18, 24) << ' ' << lcm(6, 8) << '\n'; // 6 24
    // For lcm, the resulting value must fit the argument type.
    int a = 3, b = 8;
    swap(a, b);
    cout << "swap: " << a << ' ' << b << '\n'; // 8 3
}

void string_examples() {
    string s = "abcdef";
    reverse(s.begin(), s.end());
    cout << "reverse string: " << s << '\n'; // fedcba
    s = "banana";
    cout << "substr: " << s.substr(1, 3) << '\n'; // ana (start, count)
    size_t pos = s.find("ana");
    if (pos != string::npos) cout << "string find: " << pos << '\n'; // 1
    s.replace(1, 3, "XYZ"); // replace 3 characters starting at index 1.
    cout << "string replace: " << s << '\n'; // bXYZna
    s.erase(1, 3);
    cout << "string erase: " << s << '\n'; // bna

    cout << "stoll: " << stoll("1234567890123") << '\n';
    cout << "to_string: " << to_string(-42) << '\n'; // -42
    // stoi/stoll throw on invalid or out-of-range input.
    // They accept a numeric prefix; use the position argument to check all input.
    vector<int> numbers;
    istringstream in("10 20 -3");
    for (int x; in >> x;) numbers.push_back(x);
    show("istringstream", numbers); // 10 20 -3
}

void set_and_heap_examples() {
    // Set algorithms require both ranges sorted with the same comparator.
    vector<int> a = {1, 2, 4}, b = {2, 3, 4}, out;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out));
    show("set_intersection", out); // 2 4
    out.clear();
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out));
    show("set_union", out); // 1 2 3 4
    out.clear();
    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out));
    show("set_difference", out); // 1 (a minus b)
    // Duplicates are treated as multisets; deduplicate first for set semantics.

    vector<int> heap = {3, 1, 4};
    make_heap(heap.begin(), heap.end());
    cout << "heap maximum: " << heap.front() << '\n'; // 4
    heap.push_back(5);
    push_heap(heap.begin(), heap.end());
    cout << "after push_heap: " << heap.front() << '\n'; // 5
    pop_heap(heap.begin(), heap.end()); // moves maximum to back, size unchanged.
    cout << "popped maximum: " << heap.back() << '\n'; // 5
    heap.pop_back(); // actually remove it.
    cout << "remaining maximum: " << heap.front() << '\n'; // 4
    // priority_queue is usually simpler when only top/push/pop are needed.
}

int main() {
    ordering_examples();
    searching_examples();
    editing_examples();
    numeric_examples();
    string_examples();
    set_and_heap_examples();
}
