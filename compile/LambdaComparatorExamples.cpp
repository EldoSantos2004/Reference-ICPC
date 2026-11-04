// C++17. Three representative comparator recipes.
#include <bits/stdc++.h>
using namespace std;

template<class A, class B>
ostream& operator<<(ostream& out, const pair<A, B>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}
template<class Range>
void show(const char* label, const Range& values) {
    cout << label << ':';
    for (const auto& x : values) cout << ' ' << x;
    cout << '\n';
}

int main() {
    // SORT_BEGIN
    vector<int> v = {3, 1, 2};
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    // v: 3 2 1

    using P = pair<int, int>; // (score, id)
    vector<P> a = {{20,3}, {30,4}, {20,2}, {30,1}};
    auto before = [](const P& x, const P& y) {
        if (x.first != y.first) return x.first > y.first;
        return x.second < y.second; // Tied score: smaller id first.
    };
    sort(a.begin(), a.end(), before);
    // a: (30,1) (30,4) (20,2) (20,3)
    // SORT_END
    show("integers", v);
    show("sorted pairs", a);

    // QUEUE_BEGIN
    // Reuse P, a, and before from the sorting example.
    auto lower_priority = [before](const P& x, const P& y) {
        return before(y, x); // Reverse arguments for the heap.
    };
    using Queue = priority_queue<P, vector<P>,
                                 decltype(lower_priority)>;
    Queue q(lower_priority);
    for (auto p : a) q.push(p);
    // Repeated top()/pop(): (30,1) (30,4) (20,2) (20,3)
    // QUEUE_END
    cout << "queue:";
    while (!q.empty()) { cout << ' ' << q.top(); q.pop(); }
    cout << '\n';

    // CONTAINERS_BEGIN
    auto longer = [](const string& x, const string& y) {
        if (x.size() != y.size()) return x.size() > y.size();
        return x < y; // Equal length: alphabetical order.
    };
    set<string, decltype(longer)> s(longer);
    map<string, int, decltype(longer)> freq(longer);
    for (string w : {"fig", "pear", "kiwi", "pear"}) {
        s.insert(w);
        ++freq[w];
    }
    // Set iteration: kiwi pear fig
    // Map iteration: (kiwi,1) (pear,2) (fig,1)
    // CONTAINERS_END
    show("set", s);
    show("map", freq);
}
