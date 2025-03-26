ll inverse(ll a,ll b=MOD,ll n=1,ll m=0){
  if(a==1){
    return n;
  }
  if(a<b){
    long long x=b/a;
    m+=(x*n);
    m=m%MOD;
    b=b%a;
    return inverse(a,b,n,m);
  }
  else if(b==1){
    return(MOD-m);
  }
  else{
    long long x=a/b;
    n+=(x*m);
    n=n%MOD;
    a=a%b;
    return inverse(a,b,n,m);
  }
}

// other inverse
ll inverse(ll a){
  return binexp(a,MOD-2);
}