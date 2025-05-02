/*
                                            Z_function
  --------------------------------------------------------------------------------------------
  Computes the z_function for any string.
  ith element is equal to the greatest number of characters starting 
  from the position  i  that coincide with the first characters of  s

  z[i] length of the longest string that is, at the same time, 
  a prefix of  s  and a prefix of the suffix of  $s$  starting at  i.
  
  to compress string, one can run z_function and then find the smallest i that divides n such that i + z[i] = n

  Time Complexity: O(n)
  Space Complexity: O(n)
*/


vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for(int i = 1; i < n; i++) {
    if(i < r) {
      z[i] = min(r - i, z[i - l]);
    }
    while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if(i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

// usage
// vector<int> z = z_function("abacaba");
// this will return {0, 0, 1, 0, 3, 0, 1}
// vector<int> z = z_function("aaaaa");
// this will return {0, 4, 3, 2, 1}
// vector<int> z = z_function("aaabaab");
// this will return {0, 2, 1, 0, 2, 1, 0}
