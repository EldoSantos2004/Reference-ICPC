vector<int> SOS_DP(vector<int> A, int k) {
  vector<int> Ap = A;
  for (int i = k - 1; i >= 0; i--)
    for (int mk = 0; mk < (1 << k); mk++)
      if (mk & (1 << i))
        Ap[mk] += Ap[mk - (1 << i)];
  return Ap;
}

vector<int> SOS_DP_inv (vector<int> Ap, int k) {
  vector<int> A = Ap;
  for (int i = 0; i < k; i++)
      for (int mk = 0; mk < (1 << k); mk++)
          if (mk & (1 << i)) 
              A[mk] -= A[mk - (1 << i)];
  return A;
}

vector<int> SUPER_SOS_DP(vector<int> A, int k) {
  vector<int> Ap = A;
  for (int i = k - 1; i >= 0; i--)
    for (int mk = 0; mk < (1 << k); mk++)
      if (~mk & (1 << i))
        Ap[mk] += Ap[mk + (1 << i)];
  return Ap;
}

vector<int> SUPER_SOS_DP_inv (vector<int> Ap, int k) {
  vector<int> A = Ap;
  for (int i = 0; i < k; i++)
    for (int mk = (1 << k) - 1; mk >= 0; mk--)
          if (~mk & (1 << i)) 
              A[mk] -= A[mk + (1 << i)];
  return A;
}

// or convolution
Ap = SOS_DP(A, k);
Bp = SOS_DP(B, k);

for (int i = 0; i < (1 << k); i++)
    Cp[i] = Ap[i] * Bp[i];

C = SOS_DP_inv(Cp, k);

// and convolution
Ap = SUPER_SOS_DP(A, k);
Bp = SUPER_SOS_DP(B, k);

for (int i = 0; i < (1 << k); i++)
    Cp[i] = Ap[i] * Bp[i];

C = SUPER_SOS_DP_inv(Cp, k);
