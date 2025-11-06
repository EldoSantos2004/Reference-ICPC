#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
const int LOGN = 20;
const int MOD = 998244353;

vector<int> g[MAXN];         // Adjacency list of the given graph
vector<int> ver[MAXN];       // For each color c, ver[c] stores vertices with color c
vector<int> aux_g[MAXN];     // Adjacency list for the virtual tree
int col[MAXN];               // Color of each vertex
int tmr, n;                  // Global time counter and number of vertices
int up[LOGN][MAXN], dep[MAXN], tin[MAXN]; // For computing LCA and entry time

// DP arrays for dynamic programming on the virtual tree
int dp[MAXN][2], sum[MAXN];

// Preprocessing function: DFS to compute tin, up array, and dep
void dfs_precalc(int v, int p) {
    tin[v] = ++tmr;
    up[0][v] = p;
    dep[v] = dep[p] + 1;
    for (int i = 1; i < LOGN; ++i)
        up[i][v] = up[i - 1][up[i - 1][v]];
    for (auto to : g[v])
        if (to != p)
            dfs_precalc(to, v);
}

// Function to compute LCA using binary lifting
int getlca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = LOGN - 1; i >= 0; --i)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y) return x;
    for (int i = LOGN - 1; i >= 0; --i)
        if (up[i][x] != up[i][y]) {
            x = up[i][x];
            y = up[i][y];
        }
    return up[0][x];
}

// DFS on the virtual tree to perform DP.
// Parameter c — target color for which counting is performed.

void dfs_calc(int v, int p, int c, int &ans) {
    dp[v][0] = dp[v][1] = 0;
    sum[v] = 0;
    for(auto to : aux_g[v]) {
        if(to == p) continue;
        dfs_calc(to, v, c, ans);
        // DP transitions: combining current state with result from subtree.
        int nxt0 = (dp[v][0] + sum[to]) % MOD;
        int nxt1 = ((dp[v][0] + dp[v][1]) * 1ll * sum[to] % MOD + dp[v][1]) % MOD;
        dp[v][0] = nxt0;
        dp[v][1] = nxt1;
    }
    sum[v] = (dp[v][0] + dp[v][1]) % MOD;
    if(col[v] == c) {
        // If the vertex has the target color, it can participate in a valid subtree.
        sum[v] = (sum[v] + 1) % MOD;
        ans = (ans + sum[v]) % MOD;
    } else {
        ans = (ans + dp[v][1]) % MOD;
    }
}

// Function to build a virtual tree for color c and perform DP.
void calc_aux(int c, int &ans) {
    auto p = ver[c];
    if (p.empty()) return;
    // Sort vertices by entry time (tin) — DFS traversal order.
    sort(p.begin(), p.end(), [&](const int a, const int b) { return tin[a] < tin[b]; });
    vector<int> verstk = {1}; // Initialize stack with the root of tree T (vertex 1).
    aux_g[1].clear();
    auto add = [&](int u, int v) {
        aux_g[u].push_back(v);
        aux_g[v].push_back(u);
    };
    // Process each vertex from set p, maintaining a stack to build the virtual tree.
    for (auto u : p) {
        if (u == 1) continue;
        int lca = getlca(u, verstk.back());
        if (lca != verstk.back()) {
            while (verstk.size() >= 2 && tin[lca] < tin[verstk[verstk.size() - 2]]) {
                add(verstk.back(), verstk[verstk.size() - 2]);
                verstk.pop_back();
            }
            if (verstk.size() >= 2 && tin[lca] != tin[verstk[verstk.size() - 2]]) {
                aux_g[lca].clear();
                add(verstk.back(), lca);
                verstk.back() = lca;
            } else {
                add(verstk.back(), lca);
                verstk.pop_back();
            }
        }
        aux_g[u].clear();
        verstk.push_back(u);
    }
    while (verstk.size() > 1) {
        add(verstk.back(), verstk[verstk.size() - 2]);
        verstk.pop_back();
    }
    // Perform DP on the virtual tree, starting from root 1.
    return dfs_calc(1, 0, c, ans);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    // Read colors and group vertices by color.
    for (int i = 1; i <= n; ++i) {
        cin >> col[i];
        ver[col[i]].push_back(i);
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_precalc(1, 0);
    int ans = 0;
    // Process the corresponding virtual tree for each possible color.
    for (int i = 1; i <= n; ++i)
        calc_aux(i, ans);
    cout << ans;
    return 0;
}
