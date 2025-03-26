ll binom(ll a,ll b){
  if(b>a)return 0;
  ll ans=vals[a];
  ans*=inverse(vals[b]);
  ans%=MOD;
  ans*=inverse(vals[a-b]);
  ans%=MOD;
  return ans;
}