// C++17. Each example prints its exact sorted order or queue pop order.
#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

// Print helpers only; comparator definitions are below.
ostream& operator<<(ostream& out, const P& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<class T>
void show(const char* label, const vector<T>& values) {
    cout << label << ':';
    for (const auto& x : values) cout << ' ' << x;
    cout << '\n';
}

template<class Queue>
void show_queue(const char* label, Queue q) {
    // Copy the queue so printing does not consume the original.
    cout << label << ':';
    while (!q.empty()) {
        cout << ' ' << q.top();
        q.pop();
    }
    cout << '\n';
}

void integer_examples() {
    vector<int> a = {4, 1, 3, 1, 2};
    auto v = a;
    sort(v.begin(), v.end()); // default comparator: less<int>
    show("sort less", v); // 1 1 2 3 4
    sort(v.begin(), v.end(), greater<int>());
    show("sort greater", v); // 4 3 2 1 1

    priority_queue<int> max_heap; // default comparator: less<int>
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int x : a) { max_heap.push(x); min_heap.push(x); }
    show_queue("queue less", max_heap); // 4 3 2 1 1
    show_queue("queue greater", min_heap); // 1 1 2 3 4
    // The queue pops in the REVERSE of the sort order for the same comp.

    // Binary search must use the same comparator used for sorting.
    auto it = lower_bound(v.begin(), v.end(), 2, greater<int>());
    cout << "descending lower_bound index: " << it - v.begin() << '\n'; // 2
}

void pair_examples() {
    vector<P> a = {{2, 4}, {1, 9}, {2, 1}, {1, 3}};
    auto v = a;
    sort(v.begin(), v.end());
    show("pairs default sort", v); // (1,3) (1,9) (2,1) (2,4)
    // Pairs compare first, then second; tuples compare fields in sequence.
    priority_queue<P> default_heap;
    for (auto p : a) default_heap.push(p);
    show_queue("pairs default queue", default_heap);
    // (2,4) (2,1) (1,9) (1,3)

    // Desired order: first ASCENDING, then second DESCENDING.
    auto before = [](const P& x, const P& y) {
        if (x.first != y.first) return x.first < y.first;
        return x.second > y.second;
    };
    sort(v.begin(), v.end(), before);
    show("pairs custom sort", v); // (1,9) (1,3) (2,4) (2,1)

    // C++17: decltype gives the lambda type; pass the lambda to the ctor.
    priority_queue<P, vector<P>, decltype(before)> reversed(before);
    for (auto p : a) reversed.push(p);
    show_queue("queue with same comparator", reversed);
    // (2,1) (2,4) (1,3) (1,9): opposite of custom sort.

    // To pop in the desired sort order, reverse the comparison.
    auto lower_priority = [before](const P& x, const P& y) {
        return before(y, x); // swap arguments; do NOT use !before(x,y).
    };
    priority_queue<P, vector<P>, decltype(lower_priority)> q(lower_priority);
    for (auto p : a) q.push(p);
    show_queue("queue in desired order", q);
    // (1,9) (1,3) (2,4) (2,1)
}

struct Task {
    int priority, deadline, id;
};

ostream& operator<<(ostream& out, const Task& t) {
    return out << '(' << t.priority << ',' << t.deadline << ',' << t.id << ')';
}

// Desired order: larger priority, earlier deadline, smaller id.
struct TaskBefore {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority != b.priority) return a.priority > b.priority;
        if (a.deadline != b.deadline) return a.deadline < b.deadline;
        return a.id < b.id;
    }
};

struct TaskLowerPriority {
    bool operator()(const Task& a, const Task& b) const {
        return TaskBefore{}(b, a);
        // Equivalent explicit comparisons:
        // if (a.priority != b.priority) return a.priority < b.priority;
        // if (a.deadline != b.deadline) return a.deadline > b.deadline;
        // return a.id > b.id;
    }
};

void struct_examples() {
    vector<Task> tasks = {{2,5,3}, {5,9,4}, {5,3,2}, {5,3,1}, {2,2,5}};
    auto sorted = tasks;
    sort(sorted.begin(), sorted.end(), TaskBefore{});
    cout << "tasks sorted:";
    for (auto t : sorted) cout << ' ' << t;
    cout << '\n'; // (5,3,1) (5,3,2) (5,9,4) (2,2,5) (2,5,3)

    priority_queue<Task, vector<Task>, TaskLowerPriority> q;
    for (auto t : tasks) q.push(t);
    cout << "tasks pop order:";
    while (!q.empty()) {
        cout << ' ' << q.top();
        q.pop();
    }
    cout << '\n'; // (5,3,1) (5,3,2) (5,9,4) (2,2,5) (2,5,3)
    // The explicit id tie-break makes the pop order deterministic.
    // A queue does not preserve insertion order among equivalent keys.
}

// A named function can be passed directly to sort.
bool shorter_then_lex(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

void string_and_set_examples() {
    vector<string> words = {"pear", "fig", "kiwi", "apple", "plum"};
    auto v = words;
    sort(v.begin(), v.end(), shorter_then_lex);
    show("length then lex", v); // fig kiwi pear plum apple

    auto length_only = [](const string& a, const string& b) {
        return a.size() < b.size();
    };
    v = words;
    stable_sort(v.begin(), v.end(), length_only);
    show("stable_sort length only", v); // fig pear kiwi plum apple
    // stable_sort preserves the input order for equal lengths.
    // sort does not guarantee any particular order within such ties.

    set<string, decltype(length_only)> one_per_length(length_only);
    for (const auto& word : words) one_per_length.insert(word);
    cout << "set length only:";
    for (const auto& word : one_per_length) cout << ' ' << word;
    cout << '\n'; // fig pear apple (kiwi/plum equivalent to pear)
    // set treats a,b as the same key when !comp(a,b) && !comp(b,a).
    // operator== is not used to decide key equivalence.

    auto full_order = [](const string& a, const string& b) {
        return shorter_then_lex(a, b);
    };
    set<string, decltype(full_order)> all_words(full_order);
    for (const auto& word : words) all_words.insert(word);
    cout << "set length then lex:";
    for (const auto& word : all_words) cout << ' ' << word;
    cout << '\n'; // fig kiwi pear plum apple
    // multiset can store equivalent keys too; set keeps one representative.
}

int main() {
    integer_examples();
    pair_examples();
    struct_examples();
    string_and_set_examples();
}
