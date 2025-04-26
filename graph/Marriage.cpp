// MALE OPTIMAL STABLE MARRIAGE PROBLEM O(N^2)
// gv[i][j] jth most prefered female for ith male
// om[i][j] jth most prefered male for ith female
#define MAXN 1000
int gv[MAXN][MAXN],om[MAXN][MAXN]; 
int pv[MAXN],pm[MAXN];             // ans
int pun[MAXN];                     // Auxiliary

void stableMarriage(int n) {
	fill_n(pv,n,-1); fill_n(pm,n,-1); fill_n(pun,n,0);
	int s = n, i = n-1;
	#define engage pm[j] = i; pv[i] = j;
	while (s) {
		while (pv[i] == -1) {
			int j = gv[i][pun[i]++];
			if (pm[j] == -1) {
				s--;
				engage;
			}
			else if (om[j][i] < om[j][pm[j]]) {
				int loser = pm[j];
				pv[loser] = -1;
				engage;
				i = loser;
			}
		}
		i--;
		if (i < 0) i = n-1;
	}
}
