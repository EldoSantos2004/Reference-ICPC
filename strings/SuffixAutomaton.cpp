/*
                                Suffix Automaton
  ----------------------------------------------------------------
  Constructs suffix automaton for a given string.
  Be careful with overlapping substrings.

  Firstposition if first position string ends in. If you want
   starting index you need to
   substract length of the string being searched.

  len is length of longest string of state

  Time Complexity(Construction): O(n)
  Space Complexity: O(n)
*/


struct state {
  int len, link, firstposition;
  vector<int> inv_link; // can skip for almost everything
  map<char, int> next;
};

const int MAXN = 100000;
state st[MAXN * 2];
ll cnt[MAXN*2], cntPaths[MAXN*2], cntSum[MAXN*2], cnt1[2 * MAXN];
int sz, last;

// call this first
void initSuffixAutomaton() {
  st[0].len = 0;
  st[0].link = -1;
  sz++;
  last = 0;
}

// construction is O(n)
void insertChar(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  st[cur].firstposition=st[last].len;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
      st[p].next[c] = cur;
      p = st[p].link;
  }
  if (p == -1) {
      st[cur].link = 0;
  } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
          st[cur].link = q;
      } else {
          int clone = sz++;
          st[clone].len = st[p].len + 1;
          st[clone].next = st[q].next;
          st[clone].link = st[q].link;
          st[clone].firstposition=st[q].firstposition;
          while (p != -1 && st[p].next[c] == q) {
              st[p].next[c] = clone;
              p = st[p].link;
          }
          st[q].link = st[cur].link = clone;
      }
  }
  last = cur;
  cnt[last]=1;
}

// searches for the starting position in O(len(s)). Returns starting index of first ocurrence or -1 if it does not appear.
int search(string s){
  int cur=0, i=0, n=(int)s.length();
  while(i<n){
    if(!st[cur].next.count(s[i])) return -1;
    cur=st[cur].next[s[i]];
    i++;
  }
  //sumar 2 si se quiere 1 indexado
  return st[cur].firstposition-n+1;
}

void dfs(int cur){
  cntPaths[cur]=1;
  for(auto [x, y]:st[cur].next){
    if(cntPaths[y]==0) dfs(y);
    cntPaths[cur]+=cntPaths[y];
  }
}

// Counts how many paths exist from state. How many substrings exist from a specific state.
// Stored in cntPaths
void countPaths(){
  dfs(0);
}

// Computes the number of times each state appears
void countOcurrences(){
  vector<pair<int, int>> a;
  for(int i=sz-1;i>0;i--){
    a.push_back({st[i].len, i});
  }
  sort(a.begin(), a.end());
  for(int i=sz-2;i>=0;i--){
    cnt[st[a[i].second].link]+=cnt[a[i].second];
  }
}

void dfs1(int cur){
  for(auto [x, y]:st[cur].next){
    if(cntSum[y]==cnt[y]) dfs1(y);
    cntSum[cur]+=cntSum[y];
  }
}

// Computes the number of times each state or any of its children appear in the string.
void countSumOcurrences(){
  for(int i=0;i<sz;i++){
    cntSum[i]=cnt[i];
  }
  dfs1(0);
}


// Counts number of paths that can reach specific state.
void countPathsReverse(){
  cnt1[0]=1;
  queue<int> q;
  q.push(0);
  vector<int> in(2*MAXN, 0);
  for(int i=0;i<sz;i++){
    for(auto [x, y]:st[i].next){
      in[y]++;
    }
  }
  while((int)q.size()){
    int cur=q.front();
    q.pop();
    for(auto [x, y]:st[cur].next){
      cnt1[y]+=cnt1[cur];
      in[y]--;
      if(in[y]==0){
	      q.push(y);
      }
    }
  }
}

// Computes the kth smallest string that appears on the string (counting repetitions)
string kthSmallest(ll k){
  string s="";
  int cur=0;
  while(k>0){
    for(auto [c, y]:st[cur].next){
      if(k>cntSum[y]) k-=cntSum[y];
      else{
        k-=cnt[y];
        s+=c;
        cur=y;
        break;
      }
    }
  }
  return s;
}


// Computes the kth smallest string that appears on the string (without counting repetitions)
string kthSmallestDistinct(ll k){
  string s="";
  int cur=0;
  while(k>0){
    for(auto [c, y]:st[cur].next){
      if(k>cntPaths[y]) k-=cntPaths[y];
      else{
        k--;
        s+=c;
        cur=y;
        break;
      }
    }
  }
  return s;
}


// Precomputation to find all occurrences of a substring
void precoumpte_for_all_ocurrences(){
  for (int v = 1; v < sz; v++) {
    st[st[v].link].inv_link.push_back(v);
  }
}

// Finding all occurences of substring in string
// P_length is length of substring
// v is state where first ocurrence happens
// be careful as indices can appear multiple times due to clone states
// if you want to avoid duplicate positions utilize set or have a flag for each state to know if it is clone or not
void output_all_occurrences(int v, int P_length) {
  cout << st[v].firstposition - P_length + 1 << endl;
  for (int u : st[v].inv_link)
    output_all_occurrences(u, P_length);
}


//longest common substring
//build automaton for s first
string lcs (string S, string T) {
    int v = 0, l = 0, best = 0, bestpos = 0;
    for (int i = 0; i < T.size(); i++) {
        while (v && !st[v].next.count(T[i])) {
            v = st[v].link ;
            l = st[v].len;
        }
        if (st[v].next.count(T[i])) {
            v = st [v].next[T[i]];
            l++;
        }
        if (l > best) {
            best = l;
            bestpos = i;
        }
    }
    return T.substr(bestpos - best + 1, best);
} 


int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  initSuffixAutomaton();
  for(char c:s){
    insertChar(c);
  }
}
