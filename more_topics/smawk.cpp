#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;

// Let a matrix be monotone if Opt(i) <= Opt(i + 1) for all rows i.
// Given a totally monotone matrix (where every 2x2 submatrix is monotone), find the list of row optima positions.
// Need to implement select(r, u, v): checks if v is "better" solution than u.
// Ex) if we are finding a maximum, select(r, u, v) = (f(r, u) <= f(r, v)) since it makes v better.

map<pi, int> mp;

int f(int u, int v) {
	if (mp.count({u, v}))
		return mp[{u, v}];
	cout << "? " << u + 1 << " " << v + 1 << endl;
	int x;
	cin >> x;
	return mp[{u, v}] = x;
}

bool select(int r, int u, int v) {
	assert(u < v);
	return f(r, u) > f(r, v);
}

vector<int> recurse(vector<int> &rw, vector<int> &cl) {
	if (sz(rw) == 1) {
		vector<int> opt = {0};
		for (int i = 1; i < sz(cl); i++) {
			if (select(rw[0], cl[opt[0]], cl[i]))
				opt[0] = i;
		}
		return opt;
	}
	vector<int> stk, rev;
	for (int i = 0; i < sz(cl); i++) {
		while (sz(stk) && select(rw[sz(stk) - 1], stk.back(), cl[i])) {
			stk.pop_back();
			rev.pop_back();
		}
		if (sz(stk) < sz(rw)) {
			stk.push_back(cl[i]);
			rev.push_back(i);
		}
	}
	vector<int> half;
	for (int i = 0; i < sz(rw); i += 2) {
		half.push_back(rw[i]);
	}
	vector<int> ans(sz(rw));
	auto interp = recurse(half, stk);
	for (int i = 0; i < sz(interp); i++)
		ans[2 * i] = interp[i];
	for (int i = 1; i < sz(ans); i += 2) {
		int s = ans[i - 1];
		int e = (i + 1 < sz(ans) ? ans[i + 1] : sz(stk) - 1);
		ans[i] = s;
		for (int j = s + 1; j <= e; j++) {
			if (select(rw[i], stk[ans[i]], stk[j]))
				ans[i] = j;
		}
	}
	for (int i = 0; i < sz(ans); i++)
		ans[i] = rev[ans[i]];
	return ans;
}

vector<int> smawk(int n, int m) {
	assert(n >= 1 && m >= 1);
	vector<int> rw(n), cl(m);
	iota(all(rw), 0);
	iota(all(cl), 0);
	return recurse(rw, cl);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	auto ans = smawk(n, m);
	int dap = 1e9;
	for (int i = 0; i < n; i++) {
		dap = min(dap, f(i, ans[i]));
	}
	cout << "! " << dap << endl;
}
