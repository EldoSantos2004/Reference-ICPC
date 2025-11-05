// Compute factorial (up to reasonable limits)
long long fact(int n) {
    static vector<long long> f(21, -1); // cache up to 20!
    if (n <= 1) return 1;
    if (f[n] != -1) return f[n];
    return f[n] = n * fact(n - 1);
}

// Compute 0-indexed lexicographic rank of a permutation
long long permutationRank0(const vector<int>& perm) {
    int n = perm.size();
    long long rank = 0;
    vector<int> used(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        int smaller_unused = 0;
        for (int j = 1; j < perm[i]; ++j) {
            if (!used[j]) smaller_unused++;
        }
        rank += smaller_unused * fact(n - i - 1);
        used[perm[i]] = 1;
    }
    return rank;
}

// Given n and rank (0-indexed), reconstruct the permutation
vector<int> permutationUnrank0(int n, long long rank) {
    vector<int> elems(n);
    iota(elems.begin(), elems.end(), 1); // {1, 2, 3, ..., n}
    vector<int> perm;

    for (int i = n; i >= 1; --i) {
        long long f = fact(i - 1);
        int idx = rank / f;
        rank %= f;
        perm.push_back(elems[idx]);
        elems.erase(elems.begin() + idx);
    }

    return perm;
}
