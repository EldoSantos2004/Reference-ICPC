int b[MAXN][MAXN];
int a[MAXN][MAXN];

for (int i = 1; i <= N; i++) {
  for (int j = 1; j <= N; j++) {
    b[i][j] = a[i][j] + b[i - 1][j] +
                      b[i][j - 1] - b[i - 1][j - 1];
  }
}

for (int q = 0; q < Q; q++) {
  int from_row, to_row, from_col, to_col;
  cin >> from_row >> from_col >> to_row >> to_col;
  cout << b[to_row][to_col] - b[from_row - 1][to_col] -
              b[to_row][from_col - 1] +
              b[from_row - 1][from_col - 1]
        << '\n';
}
