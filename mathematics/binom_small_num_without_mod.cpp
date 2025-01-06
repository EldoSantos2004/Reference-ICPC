double bin[501][501];
void build(){
  bin[0][0] = 1;
  for(int k = 0; k < 501; k++){
    for(int n = k; n < 501; n++){
      if(k == 0){
        bin[n][k] = 1;
        continue;
      }
      if(n == k){
        bin[n][k] = 1;
        continue;
      }
      bin[n][k] = bin[n - 1][k - 1] + bin[n - 1][k];
    }
  }
}
