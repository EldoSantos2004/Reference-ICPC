vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b, int n) {
	vector<vector<ll>> res(n, vector<ll>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
			}
		}
	}

	return res;
}

//for fibonacci
vector<vll> a(2, vll(2));
vector<vll> iden(2, vll(2));
a[0][0]=1;
a[0][1]=1;
a[1][0]=1;
a[1][1]=0;
iden[0][0]=1;
iden[1][1]=1;
iden[0][1]=0;
iden[1][0]=0;
for (;k>0;k/=2){
		if(k&1) iden=mul(iden, a);
		a=mul(a, a);
}


