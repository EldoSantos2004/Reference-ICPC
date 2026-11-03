#pragma once
#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len = 0, link = -1, firstposition = -1;
        bool isClone = false;
        map<char, int> next;
        vector<int> inv_link;
    };

    string text;
    vector<State> st;
    vector<long long> occurrenceCount;       // Occurrences of a state's substrings.
    vector<long long> pathCountFromState;    // Paths starting here, including the empty path.
    vector<long long> extensionOccurrenceSum; // Occurrences of the current substring and extensions.
    vector<long long> pathCountFromRoot;     // Paths from the root to each state.
    int sz = 0, last = 0;
    bool ready = false;

    SuffixAutomaton(const string& s = "") {
        build(s);
    }

    void build(string s) {
        text.clear();
        text.reserve(s.size());
        st.clear();
        st.reserve(2 * s.size() + 1);
        st.emplace_back();
        sz = 1;
        last = 0;
        ready = false;
        occurrenceCount.clear();
        pathCountFromState.clear();
        extensionOccurrenceSum.clear();
        pathCountFromRoot.clear();
        for (char c : s) insertChar(c);
    }

    void insertChar(char c) {
        ready = false;
        int cur = sz++;
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].firstposition = st[cur].len - 1;

        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                State copy;
                copy.len = st[p].len + 1;
                copy.link = st[q].link;
                copy.firstposition = st[q].firstposition;
                copy.next = st[q].next;
                copy.isClone = true;
                st.push_back(move(copy));

                while (p != -1) {
                    auto it = st[p].next.find(c);
                    if (it == st[p].next.end() || it->second != q) break;
                    it->second = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
        text += c;
    }

    int findState(const string& s) const {
        int v = 0;
        for (char c : s) {
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) return -1;
            v = it->second;
        }
        return v;
    }

    // First occurrence, zero-based. Returns -1 if absent.
    int search(const string& s) const {
        if (s.empty()) return 0;
        int v = findState(s);
        return v == -1 ? -1 : st[v].firstposition - (int)s.size() + 1;
    }

    // State indices sorted by increasing len, in O(n).
    vector<int> statesByLength() const {
        vector<int> bucket(st[last].len + 1, 0), order(sz);
        for (const auto& state : st) ++bucket[state.len];
        for (int i = 1; i < (int)bucket.size(); ++i)
            bucket[i] += bucket[i - 1];
        for (int v = sz - 1; v >= 0; --v)
            order[--bucket[st[v].len]] = v;
        return order;
    }

    // Computes all counters and inverse suffix links in O(n).
    // Calling it repeatedly without an insertion does no extra work.
    void precompute() {
        if (ready) return;

        occurrenceCount.assign(sz, 0);
        pathCountFromState.assign(sz, 1);
        extensionOccurrenceSum.assign(sz, 0);
        pathCountFromRoot.assign(sz, 0);
        for (auto& state : st) state.inv_link.clear();

        for (int v = 1; v < sz; ++v) {
            occurrenceCount[v] = !st[v].isClone;
            st[st[v].link].inv_link.push_back(v);
        }

        vector<int> order = statesByLength();

        // Propagate occurrence counts through suffix links.
        for (int i = sz - 1; i > 0; --i) {
            int v = order[i];
            occurrenceCount[st[v].link] += occurrenceCount[v];
        }

        // Transitions always lead to states with greater len.
        for (int i = sz - 1; i >= 0; --i) {
            int v = order[i];
            extensionOccurrenceSum[v] = v == 0 ? 0 : occurrenceCount[v];
            for (auto [c, u] : st[v].next) {
                pathCountFromState[v] += pathCountFromState[u];
                extensionOccurrenceSum[v] += extensionOccurrenceSum[u];
            }
        }

        pathCountFromRoot[0] = 1;
        for (int v : order)
            for (auto [c, u] : st[v].next)
                pathCountFromRoot[u] += pathCountFromRoot[v];

        ready = true;
    }

    // Counts overlapping occurrences too.
    long long occurrences(const string& s) {
        if (s.empty()) return (long long)st[last].len + 1;
        int v = findState(s);
        if (v == -1) return 0;
        precompute();
        return occurrenceCount[v];
    }

    // k is one-based. Returns "" for an invalid k.
    // By default, equal substrings appear once per occurrence.
    string kthSmallest(long long k, bool countRepetitions = true) {
        precompute();
        const auto& ways = countRepetitions ? extensionOccurrenceSum : pathCountFromState;
        long long total = countRepetitions ? extensionOccurrenceSum[0] : pathCountFromState[0] - 1;
        if (k < 1 || k > total) return "";

        string answer;
        int v = 0;
        while (true) {
            for (auto [c, u] : st[v].next) {
                if (k > ways[u]) {
                    k -= ways[u];
                } else {
                    answer += c;
                    long long copies = countRepetitions ? occurrenceCount[u] : 1;
                    if (k <= copies) return answer;
                    k -= copies;
                    v = u;
                    break;
                }
            }
        }
    }

    string kthSmallestDistinct(long long k) {
        return kthSmallest(k, false);
    }

    // Returns sorted, zero-based starting positions without duplicates.
    vector<int> allOccurrences(const string& s) {
        if (s.empty()) {
            vector<int> result(st[last].len + 1);
            iota(result.begin(), result.end(), 0);
            return result;
        }
        int v = findState(s);
        if (v == -1) return {};
        precompute();

        vector<int> result, pending = {v};
        while (!pending.empty()) {
            int u = pending.back();
            pending.pop_back();
            if (!st[u].isClone)
                result.push_back(st[u].firstposition - (int)s.size() + 1);
            for (int child : st[u].inv_link) pending.push_back(child);
        }
        sort(result.begin(), result.end());
        return result;
    }

    // answer[i] = longest substring ending at t[i] that occurs in the built string.
    vector<int> longestEndingAtEachIndex(const string& t) const {
        vector<int> answer(t.size());
        int v = 0, length = 0;

        for (int i = 0; i < (int)t.size(); ++i) {
            char c = t[i];

            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                length = st[v].len;
            }

            auto it = st[v].next.find(c);
            if (it != st[v].next.end()) {
                v = it->second;
                ++length;
            } else {
                v = 0;
                length = 0;
            }

            answer[i] = length;
        }

        return answer;
    }

    // Longest substring with at least k occurrences; overlaps are allowed.
    // O(n) after precompute(). Ties may return any longest substring.
    string longestRepeatedSubstring(int k = 2) {
        precompute();
        int best = 0;
        for (int v = 1; v < sz; ++v) {
            if (occurrenceCount[v] >= k && st[v].len > st[best].len)
                best = v;
        }
        if (best == 0) return "";
        return text.substr(st[best].firstposition - st[best].len + 1, st[best].len);
    }

    // answer[k] = number of distinct nonempty substrings occurring exactly k times.
    // answer[0] = 0. O(n) after precompute().
    vector<long long> substringFrequencyHistogram() {
        precompute();
        vector<long long> answer(text.size() + 1, 0);
        for (int v = 1; v < sz; ++v)
            answer[occurrenceCount[v]] += st[v].len - st[st[v].link].len;
        return answer;
    }

    // answer[length] = number of distinct substrings of that length.
    // answer[0] = 0. O(n); does not need precompute().
    vector<long long> distinctSubstringCountsByLength() const {
        vector<long long> answer(text.size() + 2, 0);
        for (int v = 1; v < sz; ++v) {
            ++answer[st[st[v].link].len + 1];
            --answer[st[v].len + 1];
        }
        for (int length = 1; length <= (int)text.size(); ++length)
            answer[length] += answer[length - 1];
        answer.pop_back();
        return answer;
    }

    // answer[i] = longest substring starting at t[i] that occurs in the built string.
    // Builds a reversed automaton each call: O(n + |t|) for a fixed alphabet.
    vector<int> longestStartingAtEachIndex(const string& t) const {
        SuffixAutomaton reversed(string(text.rbegin(), text.rend()));
        vector<int> answer = reversed.longestEndingAtEachIndex(string(t.rbegin(), t.rend()));
        reverse(answer.begin(), answer.end());
        return answer;
    }

    // Shortest absent nonempty string over alphabet. Ties use lexicographic order.
    // Returns "" for an empty alphabet. O(n * |alphabet|) for a fixed alphabet.
    string shortestAbsentSubstring(string alphabet = "abcdefghijklmnopqrstuvwxyz") const {
        sort(alphabet.begin(), alphabet.end());
        alphabet.erase(unique(alphabet.begin(), alphabet.end()), alphabet.end());
        if (alphabet.empty()) return "";

        vector<int> order = statesByLength(), distance(sz, INT_MAX);
        vector<char> choice(sz);
        for (int i = sz - 1; i >= 0; --i) {
            int v = order[i];
            for (char c : alphabet) {
                auto it = st[v].next.find(c);
                int candidate = it == st[v].next.end() ? 1 : 1 + distance[it->second];
                if (candidate < distance[v]) {
                    distance[v] = candidate;
                    choice[v] = c;
                }
            }
        }

        string answer;
        int v = 0;
        while (true) {
            char c = choice[v];
            answer += c;
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) return answer;
            v = it->second;
        }
    }

    // Shortest substring occurring exactly once. Returns "" for an empty text.
    // O(n) after precompute(); ties may return any shortest substring.
    string shortestUniqueSubstring() {
        precompute();
        int bestState = 0, bestLength = (int)text.size() + 1;
        for (int v = 1; v < sz; ++v) {
            int length = st[st[v].link].len + 1;
            if (occurrenceCount[v] == 1 && length < bestLength) {
                bestState = v;
                bestLength = length;
            }
        }
        if (bestState == 0) return "";
        return text.substr(st[bestState].firstposition - bestLength + 1, bestLength);
    }

    // Helper: longest matching substring length in each state, including suffixes.
    vector<int> matchLengthsByState(const string& t, const vector<int>& order) const {
        vector<int> matches(sz, 0);
        int v = 0, length = 0;
        for (char c : t) {
            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                length = st[v].len;
            }
            auto it = st[v].next.find(c);
            if (it != st[v].next.end()) {
                v = it->second;
                ++length;
                matches[v] = max(matches[v], length);
            } else {
                v = 0;
                length = 0;
            }
        }
        for (int i = sz - 1; i > 0; --i) {
            int u = order[i], p = st[u].link;
            matches[p] = max(matches[p], min(matches[u], st[p].len));
        }
        return matches;
    }

    // Number of distinct nonempty substrings shared by text and t.
    // O(n + |t|) for a fixed alphabet.
    long long countCommonDistinctSubstrings(const string& t) const {
        vector<int> order = statesByLength();
        vector<int> matches = matchLengthsByState(t, order);
        long long answer = 0;
        for (int v = 1; v < sz; ++v)
            answer += max(0, matches[v] - st[st[v].link].len);
        return answer;
    }

    // answer[length] = number of distinct shared substrings of that length.
    // answer has text.size() + 1 entries; answer[0] = 0.
    // O(n + |t|) for a fixed alphabet.
    vector<long long> countCommonDistinctSubstringsByLength(const string& t) const {
        vector<int> order = statesByLength();
        vector<int> matches = matchLengthsByState(t, order);
        vector<long long> answer(text.size() + 2, 0);
        for (int v = 1; v < sz; ++v) {
            int minimumLength = st[st[v].link].len + 1;
            if (matches[v] < minimumLength) continue;
            ++answer[minimumLength];
            --answer[matches[v] + 1];
        }
        for (int length = 1; length <= (int)text.size(); ++length)
            answer[length] += answer[length - 1];
        answer.pop_back();
        return answer;
    }

    // Shortest nonempty substring of text absent from t; "" if none exists.
    // O(n + |t|) for a fixed alphabet. Ties may return any shortest substring.
    string shortestDistinguishingSubstring(const string& t) const {
        vector<int> order = statesByLength();
        vector<int> matches = matchLengthsByState(t, order);
        int bestState = 0, bestLength = 0;
        for (int v = 1; v < sz; ++v) {
            if (matches[v] == st[v].len) continue;
            // This state's lengths above matches[v] are absent from t.
            int length = max(st[st[v].link].len + 1, matches[v] + 1);
            if (bestState == 0 || length < bestLength) {
                bestState = v;
                bestLength = length;
            }
        }
        if (bestState == 0) return "";
        return text.substr(st[bestState].firstposition - bestLength + 1, bestLength);
    }

    // Minimum pieces whose concatenation is t, each a substring of text.
    // Returns 0 for empty t, -1 if impossible. O(|t|) for a fixed alphabet.
    int minimumSubstringPieces(const string& t) const {
        if (t.empty()) return 0;
        // Greedy longest pieces are optimal because valid pieces are suffix-closed.
        int pieces = 1, v = 0;
        for (char c : t) {
            auto it = st[v].next.find(c);
            if (it == st[v].next.end()) {
                it = st[0].next.find(c);
                if (it == st[0].next.end()) return -1;
                ++pieces;
            }
            v = it->second;
        }
        return pieces;
    }

    // Sum of occurrences_in_text(p) * occurrences_in_t(p) over all nonempty p.
    // Overlaps count. The result can exceed 64 bits, so it returns __int128.
    // O(n + |t|) for a fixed alphabet, including precompute().
    __int128 countCommonSubstringOccurrencePairs(const string& t) {
        precompute();
        vector<int> order = statesByLength();
        vector<long long> suffixOccurrenceSum(sz, 0);
        for (int v : order) {
            if (v == 0) continue;
            int p = st[v].link;
            suffixOccurrenceSum[v] = suffixOccurrenceSum[p]
                + occurrenceCount[v] * (st[v].len - st[p].len);
        }

        __int128 answer = 0;
        int v = 0, length = 0;
        for (char c : t) {
            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                length = st[v].len;
            }
            auto it = st[v].next.find(c);
            if (it != st[v].next.end()) {
                v = it->second;
                ++length;
                int p = st[v].link;
                // Include all shorter states and only the matched part of v.
                answer += suffixOccurrenceSum[p]
                    + occurrenceCount[v] * (length - st[p].len);
            } else {
                v = 0;
                length = 0;
            }
        }
        return answer;
    }

    // Total occurrences in text of all DISTINCT cyclic rotations of pattern.
    // Returns 0 for an empty pattern. Overlapping occurrences count.
    // O(n + |pattern|) for a fixed alphabet, including precompute().
    long long countCyclicRotationMatches(const string& pattern) {
        if (pattern.empty() || pattern.size() > text.size()) return 0;
        precompute();
        vector<char> seen(sz, false);
        int m = (int)pattern.size(), v = 0, length = 0;
        long long answer = 0;

        // The first 2*m-1 characters of pattern + pattern cover all rotations.
        for (int pass = 0; pass < 2; ++pass) {
            int limit = m - (pass == 1);
            for (int i = 0; i < limit; ++i) {
                char c = pattern[i];
                while (v && !st[v].next.count(c)) {
                    v = st[v].link;
                    length = st[v].len;
                }
                auto it = st[v].next.find(c);
                if (it == st[v].next.end()) {
                    v = 0;
                    length = 0;
                    continue;
                }
                v = it->second;
                ++length;
                if (length < m) continue;

                length = m;
                // Use the state representing this length, not a longer match.
                while (st[st[v].link].len >= m) v = st[v].link;
                if (!seen[v]) {
                    seen[v] = true;
                    answer += occurrenceCount[v];
                }
            }
        }
        return answer;
    }

    // Longest substring shared by text and EVERY string in strings.
    // An empty vector returns text. An empty string in it returns "".
    // O((strings.size() + 1) * n + total input length) for a fixed alphabet.
    string longestCommonSubstringMultiple(const vector<string>& strings) const {
        vector<int> order = statesByLength(), common(sz);
        for (int v = 0; v < sz; ++v) common[v] = st[v].len;
        for (const string& t : strings) {
            if (t.empty()) return "";
            vector<int> matches = matchLengthsByState(t, order);
            for (int v = 0; v < sz; ++v) common[v] = min(common[v], matches[v]);
        }

        int bestState = 0, bestLength = 0;
        for (int v = 1; v < sz; ++v) {
            if (common[v] > bestLength) {
                bestState = v;
                bestLength = common[v];
            }
        }
        if (bestLength == 0) return "";
        return text.substr(st[bestState].firstposition - bestLength + 1, bestLength);
    }

    // Longest substring with two occurrences that do not overlap. O(n).
    // Returns "" if none exists; ties may return any longest substring.
    string longestNonOverlappingRepeat() const {
        vector<int> order = statesByLength();
        vector<int> minEnd(sz, text.size()), maxEnd(sz, -1);
        for (int v = 1; v < sz; ++v) {
            if (!st[v].isClone)
                minEnd[v] = maxEnd[v] = st[v].firstposition;
        }
        for (int i = sz - 1; i > 0; --i) {
            int v = order[i], p = st[v].link;
            minEnd[p] = min(minEnd[p], minEnd[v]);
            maxEnd[p] = max(maxEnd[p], maxEnd[v]);
        }

        int bestState = 0, bestLength = 0;
        for (int v = 1; v < sz; ++v) {
            int length = min(st[v].len, maxEnd[v] - minEnd[v]);
            if (length > st[st[v].link].len && length > bestLength) {
                bestState = v;
                bestLength = length;
            }
        }
        if (bestLength == 0) return "";
        return text.substr(st[bestState].firstposition - bestLength + 1, bestLength);
    }

    // Longest common substring of the built string and t.
    string lcs(const string& t) const {
        int v = 0, length = 0, best = 0;
        size_t bestpos = 0;
        for (size_t i = 0; i < t.size(); ++i) {
            while (v && !st[v].next.count(t[i])) {
                v = st[v].link;
                length = st[v].len;
            }
            auto it = st[v].next.find(t[i]);
            if (it != st[v].next.end()) {
                v = it->second;
                ++length;
            } else {
                v = 0;
                length = 0;
            }
            if (length > best) {
                best = length;
                bestpos = i;
            }
        }
        return best == 0 ? string{} : t.substr(bestpos - (best - 1), best);
    }
};
