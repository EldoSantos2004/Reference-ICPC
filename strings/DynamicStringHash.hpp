#pragma once
#include "ComposableHash.hpp"

namespace hashing_ref {
// Point replacement; forward/reverse hashes; zero-based [l,r).
// Hashes use the same parameters as PrefixHash and Hash.
class DynamicStringHash {
    struct Node { Hash forward, reverse; };
    int n, base = 1;
    std::vector<Node> tree;
    static Node merge(const Node& a, const Node& b) {
        return {a.forward * b.forward, b.reverse * a.reverse};
    }
public:
    explicit DynamicStringHash(std::string_view s) : n((int)s.size()) {
        while (base < n) base *= 2;
        tree.resize(2 * base);
        for (int i = 0; i < n; ++i) {
            Hash c = Hash::character((unsigned char)s[i]);
            tree[base + i] = {c, c};
        }
        for (int v = base - 1; v > 0; --v)
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }
    void set(int position, unsigned char c) {
        assert(0 <= position && position < n);
        int v = base + position;
        Hash h = Hash::character(c);
        tree[v] = {h, h};
        for (v /= 2; v; v /= 2)
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }
    Node query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        Node left, right;
        for (l += base, r += base; l < r; l /= 2, r /= 2) {
            if (l & 1) left = merge(left, tree[l++]);
            if (r & 1) right = merge(tree[--r], right);
        }
        return merge(left, right);
    }
    Hash get(int l, int r) const { return query(l, r).forward; }
    Hash reversed(int l, int r) const { return query(l, r).reverse; }
    bool palindrome(int l, int r) const {
        Node x = query(l, r);
        return x.forward == x.reverse;
    }
};
} // namespace hashing_ref
