/*
  LCM Convolution via Divisor Zeta and Mobius Transforms
  ------------------------------------------------------
  Given two sequences A[1..n] and B[1..n], computes C where
    C[d] = sum_{i, j: lcm(i, j) = d} A[i] * B[j]
  Indexing: 1-based (vectors of size n+1, ignore index 0)
  Bounds:
    - i, j, d in [1..n]
  Time Complexity: O(n log log n + n log n)
  Space Complexity: O(n)
  Steps:
    1. Divisor Zeta Transform: for each prime p, v[i*p] += v[i]
    2. Pointwise multiply transformed A and B
    3. Divisor Mobius Transform: for each prime p, v[i*p] -= v[i]
*/
// Sieve primes up to n in O(n)
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
// Divisor Zeta Transform: v[d] = sum_{d|k} original_v[k]
template<typename T>
void DivisorZetaTransform(vector<T>& v) {
  int n = (int)v.size() - 1;
  auto primes = PrimeEnumerate(n);
  for (int p : primes) {
    for (int i = 1; i * p <= n; i++) {
      v[i * p] += v[i];
    }
  }
}
// Divisor Mobius Transform (inverse of zeta)
template<typename T>
void DivisorMobiusTransform(vector<T>& v) {
  int n = (int)v.size() - 1;
  auto primes = PrimeEnumerate(n);
  for (int p : primes) {
    for (int i = n / p; i >= 1; i--) {
      v[i * p] -= v[i];
    }
  }
}
// LCM convolution of A and B (each size n+1)
template<typename T>
vector<T> LCMConvolution(vector<T> A, vector<T> B) {
  int n = (int)A.size() - 1;
  DivisorZetaTransform(A);
  DivisorZetaTransform(B);
  for (int d = 1; d <= n; d++) {
    A[d] *= B[d];  // pointwise multiplication
  }
  DivisorMobiusTransform(A);
  return A;  // result C[1..n], C[d] = sum_{lcm(i,j)=d} A[i]*B[j]
}
// Example usage
vector<long long> A(n+1), B(n+1);
for (int i = 1; i <= n; i++) cin >> A[i];
for (int i = 1; i <= n; i++) cin >> B[i];
auto C = LCMConvolution<long long>(A, B);
for (int d = 1; d <= n; d++){
  cout << C[d] << (d==n?'\n':' ');
}
