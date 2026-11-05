template<typename M>
struct TruncatedMatroid {
    M m;
    int k, cnt;
    
    TruncatedMatroid(M m, int k) : m(m), k(k), cnt(0) {}
    
    void clear() { 
        m.clear(); 
        cnt = 0; 
    }
    
    bool check(int x) { 
        return cnt < k && m.check(x); 
    }
    
    void add(int x) { 
        m.add(x); 
        cnt++; 
    }
    
    void precomp() { 
        m.precomp(); 
    }
};