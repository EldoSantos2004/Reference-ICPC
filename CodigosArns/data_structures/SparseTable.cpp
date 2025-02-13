const int MAXN=100005, K=30;
int lg[MAXN+1];
int st[K + 1][MAXN];

int mini(int L, int R){
  int i = lg[R - L + 1];
  int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);
  return minimum;
}

int main(){
  lg[1]=0;
  for (int i = 2; i <= MAXN; i++)
    lg[i] = lg[i/2] + 1;
  std::copy(a.begin(), a.end(), st[0]);

  for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= n; j++)
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
