ll vals[1000001];
void fi(){
  vals[0]=1;
  vals[1]=1;
  for(int i=2;i<1000001;i++){
    vals[i]=i*vals[i-1];
    vals[i]%=MOD;
  }
}