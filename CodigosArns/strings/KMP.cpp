// Maximum length of substring that ends at position i and is prefix of string
vector<int> KMP(string s){
  int n=s.length();
  vector<int> prefixFunction(n, 0);
  for(int i=1;i<n;i++){
    int j=prefixFunction[i-1];
    while(j>0 && s[i]!=s[j]){
      j=prefixFunction[j-1];
    }
    if(s[i]==s[j]){
      prefixFunction[i]=j+1;
    }
  }
  return prefixFunction;
}
