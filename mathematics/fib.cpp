void fib(ll n, ll&x, ll&y){
  if(n==0){
    x = 0;
    y = 1;
    return ;
  }
    
  if(n&1){
    fib(n-1, y, x);
    y=(y+x)%MOD;
  }else{
    ll a, b;
    fib(n>>1, a, b);
    y = (a*a+b*b)%MOD;
    x = (a*b + a*(b-a+MOD))%MOD;
  }
}

// Usage
// ll x, y;
// fib(10, x, y);
// cout << x << " " << y << endl;
// This will output 55 89