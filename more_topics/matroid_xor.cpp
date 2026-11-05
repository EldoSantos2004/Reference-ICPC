struct LinearGF2Matroid {
    vector<long long> vals;
    vector<long long> basis;
    
    LinearGF2Matroid(const vector<long long>& vals) : vals(vals) {}
    
    void clear() { 
        basis.clear(); 
    }
    
    bool check(int x) {
        long long v = vals[x];
        for (long long b : basis) v = min(v, v ^ b);
        return v > 0;
    }
    
    void add(int x) {
        long long v = vals[x];
        for (long long b : basis) v = min(v, v ^ b);
        if (v > 0) {
            basis.push_back(v);
            // Sorting ensures MSBs remain strictly descending for correct basis reduction
            sort(basis.rbegin(), basis.rend()); 
        }
    }
    
    void precomp() {}
};