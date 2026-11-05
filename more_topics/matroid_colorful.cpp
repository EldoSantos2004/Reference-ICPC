struct ColorfulMatroid {
    vector<int> color;
    vector<bool> used;
    
    ColorfulMatroid(int num_colors, const vector<int>& color)
        : color(color), used(num_colors, false) {}
        
    void clear() { 
        fill(begin(used), end(used), false); 
    }
    
    bool check(int x) { 
        return !used[color[x]]; 
    }
    
    void add(int x) { 
        used[color[x]] = true; 
    }
    
    void precomp() {}
};