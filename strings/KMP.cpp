/*
                                            KMP
  --------------------------------------------------------------------------------------------
  Computes the prefix function for a string.
  Maximum length of substring that ends at position i and is proper prefix (not equal to string itself) of string
  pf[i]  is the length of the longest proper prefix of the substring  
  s[0......i]$  which is also a suffix of this substring.
  For matching, one can append the string with a delimites like $ between them

  Time Complexity: O(n)
  Space Complexity: O(n)
*/

vector<int> KMP(string s){
  int n=(int)s.length();
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

// Counts how many times each prefix occurs
// Same thing can be done for two strings but only considering indices of second string
vector<int> count_occurrences_of_prefixes(vector<int> pf){
  int n=(int)pf.size();
  vector<int> ans(n + 1);
  for (int i = 0; i < n; i++)
    ans[pi[i]]++;
  for (int i = n-1; i > 0; i--)
    ans[pi[i-1]] += ans[i];
  for (int i = 0; i <= n; i++)
    ans[i]++;
}

// Computes automaton for string 
// useful for not having to recalculate KMP of string s
// can be utilized when the second string (the one in which we are trying to count occurences)
// is very large
void compute_automaton(string s, vector<vector<int>>& aut) {
  s += '#';
  int n = s.size();
  vector<int> pi = KMP(s);
  aut.assign(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
      for (int c = 0; c < 26; c++) {
          if (i > 0 && 'a' + c != s[i])
              aut[i][c] = aut[pi[i-1]][c];
          else
              aut[i][c] = i + ('a' + c == s[i]);
      }
  }
}