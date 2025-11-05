// Compute nCr (binomial coefficient)
long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// Compute 0-indexed lexicographic rank of a combination
long long combinationRank0(const vector<int>& comb) {
    long long rank = 0;
    for (int i = 0; i < (int)comb.size(); ++i) {
        rank += nCr(comb[i] - 1, i + 1);
    }
    return rank; // 0-indexed
}

// Given n, r, and rank (0-indexed), reconstruct the combination
vector<int> combinationUnrank0(int n, int r, long long rank) {
    vector<int> comb;
    int x = 1;

    for (int i = r; i >= 1; --i) {
        while (nCr(n - x, i) > rank) {
            x++;
        }
        comb.push_back(x);
        rank -= nCr(n - x, i);
        x++;
    }

    return comb;
}
