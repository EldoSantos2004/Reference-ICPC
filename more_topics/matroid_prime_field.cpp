struct LinearPrimeMatroid {
    int D; // Vector dimension
    long long MOD;
    vector<vector<long long>> vecs;
    vector<vector<long long>> basis;

    LinearPrimeMatroid(int D, long long MOD, const vector<vector<long long>>& vecs)
        : D(D), MOD(MOD), vecs(vecs) {}

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

    void clear() {
        basis.clear();
    }

    bool check(int x) {
        vector<long long> v = vecs[x];
        for (const auto& b : basis) {
            int pivot = -1;
            for (int i = 0; i < D; i++) {
                if (b[i] != 0) { pivot = i; break; }
            }
            if (pivot != -1 && v[pivot] != 0) {
                long long f = (v[pivot] * modInverse(b[pivot])) % MOD;
                for (int i = pivot; i < D; i++) {
                    v[i] = (v[i] - f * b[i]) % MOD;
                    if (v[i] < 0) v[i] += MOD;
                }
            }
        }
        for (int i = 0; i < D; i++) {
            if (v[i] != 0) return true;
        }
        return false;
    }

    void add(int x) {
        vector<long long> v = vecs[x];
        for (const auto& b : basis) {
            int pivot = -1;
            for (int i = 0; i < D; i++) {
                if (b[i] != 0) { pivot = i; break; }
            }
            if (pivot != -1 && v[pivot] != 0) {
                long long f = (v[pivot] * modInverse(b[pivot])) % MOD;
                for (int i = pivot; i < D; i++) {
                    v[i] = (v[i] - f * b[i]) % MOD;
                    if (v[i] < 0) v[i] += MOD;
                }
            }
        }
        for (int i = 0; i < D; i++) {
            if (v[i] != 0) {
                basis.push_back(v);
                return;
            }
        }
    }

    void precomp() {}
};