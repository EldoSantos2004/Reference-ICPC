/*
  GCD Convolution via Multiple Zeta and Mobius Transforms
  ------------------------------------------------------
  Given two sequences A[0..n] and B[0..n], computes C where
    C[d] = sum_{i, j: gcd(i, j) = d} A[i] * B[j]
  Indexing: 0-based, vectors of size n+1 (ignore index 0 if unused)
  Bounds:
    - i, j, d in [1..n]
  Time Complexity: O(n log log n + n log n) per convolution
  Space Complexity: O(n)
  Steps:
    1. Multiple Zeta Transform: for each prime p, v[i] += v[i*p]
    2. Pointwise multiply transformed A and B
    3. Multiple Mobius Transform: for each prime p, v[i] -= v[i*p]
*/
// Enumerate primes up to n in O(n)
vector<int> PrimeEnumerate(int n) {
  vector<bool> isPrime(n+1, true);
  vector<int> P;
  for (int i = 2; i <= n; i++) {
    if (isPrime[i]) P.push_back(i);
    for (int p : P) {
      if (i * p > n) break;
      isPrime[i*p] = false;
      if (i % p == 0) break;
    }
  }
  return P;
}
// Multiple Zeta Transform (over divisibility poset)
template<typename T>
void MultipleZetaTransform(vector<T>& v) {
  int n = (int)v.size() - 1;
  for (int p : PrimeEnumerate(n)) {
    for (int i = n/p; i >= 1; i--) {
      v[i] += v[i * p];
    }
  }
}
// Multiple Mobius Transform (inverse of zeta)
template<typename T>
void MultipleMobiusTransform(vector<T>& v) {
  int n = (int)v.size() - 1;
  for (int p : PrimeEnumerate(n)) {
    for (int i = 1; i * p <= n; i++) {
      v[i] -= v[i * p];
    }
  }
}
// GCD convolution of A and B, both size n+1
template<typename T>
vector<T> GCDConvolution(vector<T> A, vector<T> B) {
  int n = (int)A.size() - 1;
  MultipleZetaTransform(A);
  MultipleZetaTransform(B);
  for (int i = 1; i <= n; i++) {
    A[i] *= B[i];  // pointwise multiplication
  }
  MultipleMobiusTransform(A);
  return A;       // result C[0..n], where C[d] = sum_{gcd(i,j)=d} A[i]*B[j]
}
// Example usage
vector<long long> A(n+1), B(n+1);
for (int i = 1; i <= n; i++) cin >> A[i];
for (int i = 1; i <= n; i++) cin >> B[i];
auto C = GCDConvolution<long long>(A, B);
for (int d = 1; d <= n; d++){
  cout << C[d] << (d==n?'\n':' ');
}
