// Maximum length of substring that ends at position i and is prefix of string
vector<int> KMP(string s){
  int n=s.length();
  vector<int> pf(n, 0);
  for(int i=1;i<n;i++){
    int j=pf[i-1];
    while(j>0 && s[i]!=s[j]){
      j=pf[j-1];
    }
    if(s[i]==s[j]){
      pf[i]=j+1;
    }
  }
  return pf;
}
