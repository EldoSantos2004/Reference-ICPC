/*
  Male-Optimal Stable Marriage Problem (Gale-Shapley Algorithm)
  --------------------------------------------------------------
  Indexing: 0-based
  Bounds: 0 <= i, j < n
  Time Complexity: O(n^2)
  Space Complexity: O(n^2)

  Input:
    - n: Number of men/women (equal)
    - gv[i][j]: j-th most preferred woman for man i
    - om[i][j]: j-th most preferred man for woman i
        * Both are permutations of {0, ..., n-1}
        * om must be inverted to get om[w][m] = woman w's ranking of man m

  Output:
    - pm[i]: Woman matched to man i (i.e. pairings)
    - pv[i]: Man matched to woman i
*/

#define MAXN 1000
int gv[MAXN][MAXN], om[MAXN][MAXN]; // Male and female preference lists
int pv[MAXN], pm[MAXN];             // pv[woman] = man, pm[man] = woman
int pun[MAXN];                      // pun[man] = next woman to propose to

void stableMarriage(int n) {
  fill_n(pv, n, -1);   // All women initially unmatched
  fill_n(pm, n, -1);   // All men initially unmatched
  fill_n(pun, n, 0);   // Each man starts at his top preference

  int unmatched = n;   // Number of free men
  int i = n - 1;       // Current man index (rotates over all men)

  #define engage pm[j] = i; pv[i] = j;

  while (unmatched) {
    while (pm[i] == -1) {
      int j = gv[i][pun[i]++]; // Next woman on man i's list

      if (pv[j] == -1) {
        // Woman j is free -> engage with man i
        unmatched--;
        engage;
      } else if (om[j][i] < om[j][pv[j]]) {
        // Woman j prefers i over her current partner
        int loser = pv[j];
        pm[loser] = -1;
        engage;
        i = loser; // Reconsider the rejected man
      }
    }

    // Move to next unmatched man
    i--;
    if (i < 0) i = n - 1;
  }

  #undef engage
}
