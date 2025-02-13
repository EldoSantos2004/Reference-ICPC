vector<int> num;
ll DP[20][20][2][2]; 
 
ll g(int pos, int last, int f, int z){
    
    if(pos == num.size()){
        return 1;
    }
 
    if(DP[pos][last][f][z] != -1) return DP[pos][last][f][z];
    ll res = 0;
    
    int l=(f ? 9 :num[pos]);
 
    for(int dgt = 0; dgt<=l; dgt++){
        if(dgt==last && !(dgt==0 && z==1)) continue;
        int nf = f;
        if(f == 0 && dgt < l) nf = 1; 
        if(z && !dgt) res+=g(pos+1, dgt, nf, 1);
        else res += g(pos+1, dgt, nf, 0);
    }
    DP[pos][last][f][z]=res;
    return res;
}
 
ll solve(ll x){
    num.clear();
    if(x==-1) return 0;
    memset(DP, -1, sizeof(DP));    
    while(x>0){
        num.pb(x%10);
        x/=10;
    }
    reverse(all(num));
    return g(0, 0, 0, 1);
}
