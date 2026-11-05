#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// NDPC N: 1 <= n <= 4000, 0 <= v[i] <= 10^9,
// 1 <= query weight <= 10^9. Fill the weight EXACTLY.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) {
        __int128 lhs = (__int128)v[a] * b;
        __int128 rhs = (__int128)v[b] * a;
        if (lhs != rhs) return lhs > rhs;
        return a < b;
    });
    int p = order[0], limit = n * n;
    const ll NEG = -(1LL << 60);
    vector<ll> dp(limit + 1, NEG);
    dp[0] = 0;
    for (int w = 1; w <= limit; ++w) {
        int k = (int)min((ll)n, (2LL * limit + w - 1) / w);
        for (int j = 0; j < k; ++j) {
            int i = order[j];
            if (i <= w && dp[w - i] != NEG)
                dp[w] = max(dp[w], dp[w - i] + v[i]);
        }
    }
    while (q--) {
        ll W;
        cin >> W;
        ll take = 0;
        if (W > limit) {
            take = (W - limit + p - 1) / p;
            W -= take * p;
        }
        cout << dp[(int)W] + take * v[p] << '\n';
    }
}
