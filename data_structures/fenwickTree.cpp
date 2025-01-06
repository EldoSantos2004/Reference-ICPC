ll fwsum(ll k){
    ll s = 0;
    while(k >= 1){
        s += tr[k];
        k -= k & (-k);
    }
    return s;
}

void fwadd(ll k, ll x, int n){
    while(k <= n){
        tr[k] += x;
        k += k & (-k);
    }
}
