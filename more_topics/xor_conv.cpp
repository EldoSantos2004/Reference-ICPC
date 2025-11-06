/*
  Fast Walsh-Hadamard Transform (FWHT) for XOR Convolution
  -------------------------------------------------------
  Given two arrays A[0..N-1], B[0..N-1], with N = 1<<k (power of two).
  Computes C[d] = sum_{i xor j = d} A[i] * B[j].
  Indexing: 0-based
  Bounds:
    - N must be a power of two
  Time Complexity: O(N * log(N))
  Steps:
    1. fwht(A, false); fwht(B, false); // forward transform
    2. for i in [0..N): C[i] = A[i] * B[i]
    3. fwht(C, true);                  // inverse transform
*/
void FWHT (int A[], int k, int inv) {
  for (int j = 0; j < k; j++)
    for (int i = 0; i < (1 << k); i++)
      if (~i & (1 << j)) {
        int p0 = A[i];
        int p1 = A[i | (1 << j)];
        A[i] = p0 + p1;
        A[i | (1 << j)] = p0 - p1;
        if (inv) {
          A[i] /= 2;
          A[i | (1 << j)] /= 2;
        }
      }
}
void XOR_conv (int A[], int B[], int C[], int k) {
  FWHT(A, k, false);
  FWHT(B, k, false);
  for (int i = 0; i < (1 << k); i++)
    C[i] = A[i] * B[i];
  FWHT(A, k, true);
  FWHT(B, k, true);
  FWHT(C, k, true);
}
// Example usage:
int A[1 << 20], B[1 << 20], C[1 << 20];
XOR_conv(A, B, C, 20);
for (int d = 0; d < (1<<20); d++){
  cout << C[d] << (d==(1<<20)?'\n':' ');
}





#include <bits/stdc++.h>

using namespace std;
#define int long long

const int mod = 998244353;

int inverse(int x, int mod) {
	return x == 1 ? 1 : mod - mod / x * inverse(mod % x, mod) % mod;
}

void xormul(vector<int> a, vector<int> b, vector<int> &c) {
	int m = (int) a.size();
	c.resize(m);
	for (int n = m / 2; n > 0; n /= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = a[i + j], y = a[i + j + n];
				a[i + j] = (x + y) % mod;
				a[i + j + n] = (x - y + mod) % mod;
			}
	for (int n = m / 2; n > 0; n /= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = b[i + j], y = b[i + j + n];
				b[i + j] = (x + y) % mod;
				b[i + j + n] = (x - y + mod) % mod;
			}
	for (int i = 0; i < m; i++)
		c[i] = a[i] * b[i] % mod;
	for (int n = 1; n < m; n *= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = c[i + j], y = c[i + j + n];
				c[i + j] = (x + y) % mod;
				c[i + j + n] = (x - y + mod) % mod;
			}
	int mrev = inverse(m, mod);
	for (int i = 0; i < m; i++)
		c[i] = c[i] * mrev % mod;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<int> a(1 << n), b(1 << n), c;
	for (int i = 0; i < (1 << n); i++)
		cin >> a[i];
	for (int i = 0; i < (1 << n); i++)
		cin >> b[i];
	xormul(a, b, c);
	for (int i = 0; i < (1 << n); i++)
		cout << c[i] << ' ';
}
