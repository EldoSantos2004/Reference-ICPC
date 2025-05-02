/*
  Digit Dynamic Programming (Digit DP)
  ------------------------------------
  Goal: Count numbers in range [0, x] that do not have two adjacent equal digits.
  State:
    - pos: current digit position
    - last: digit placed at previous position (0 to 9)
    - f: tight flag (0 = must match prefix of x, 1 = already below x)
    - z: leading zero flag (1 = still in leading zero zone)
  Notes:
    - Solve up to x using `solve(x)`
    - Can be modified to count palindromes, digits divisible by 3, etc.
*/

vector<int> num;
ll DP[20][20][2][2]; // pos, last digit, f (tight), z (leading zero)

ll g(int pos, int last, int f, int z) {
  if (pos == num.size()) return 1; // reached end, valid number
  if (DP[pos][last][f][z] != -1) return DP[pos][last][f][z];
  ll res = 0;
  int limit = f ? 9 : num[pos]; // upper digit bound based on tight flag
  for (int dgt = 0; dgt <= limit; dgt++) {
    // Skip if digit equals last (unless it's a leading zero)
    if (dgt == last && !(dgt == 0 && z == 1)) continue;
    int nf = f;
    if (!f && dgt < limit) nf = 1;
    if (z && dgt == 0) res += g(pos + 1, dgt, nf, 1); // still leading zeros
    else res += g(pos + 1, dgt, nf, 0); // now in significant digits
  }
  return DP[pos][last][f][z] = res;
}

ll solve(ll x) {
  if (x == -1) return 0;
  num.clear();
  while (x > 0) {
    num.push_back(x % 10);
    x /= 10;
  }
  reverse(num.begin(), num.end());
  memset(DP, -1, sizeof(DP));
  return g(0, 0, 0, 1);
}
