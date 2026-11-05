struct TransversalMatroid {
    int n, m, timer; // n = |U| (ground set), m = |V|
    vector<vector<int>> adj; 
    vector<int> matchL, matchR, vis;

    TransversalMatroid(int n, int m, const vector<vector<int>> &adj)
        : n(n), m(m), timer(0), adj(adj), matchL(n, -1), matchR(m, -1), vis(m, 0) {}

    void clear() {
        fill(begin(matchL), end(matchL), -1);
        fill(begin(matchR), end(matchR), -1);
        timer = 0;
        fill(begin(vis), end(vis), 0);
    }

    bool dfs_check(int u) {
        for (int v : adj[u]) {
            if (vis[v] == timer) continue;
            vis[v] = timer;
            if (matchR[v] == -1 || dfs_check(matchR[v])) return true;
        }
        return false;
    }

    bool check(int x) {
        if (matchL[x] != -1) return true;
        ++timer;
        return dfs_check(x);
    }

    bool dfs_add(int u) {
        for (int v : adj[u]) {
            if (vis[v] == timer) continue;
            vis[v] = timer;
            if (matchR[v] == -1 || dfs_add(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    void add(int x) {
        if (matchL[x] != -1) return;
        ++timer;
        dfs_add(x);
    }
    
    void precomp() {}
};