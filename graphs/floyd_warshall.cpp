ll distances[n + 1][n + 1];
for(int i = 1; i <= n; i++){
  for(int j = 1; j <= n; j++){
    if(i == j) distances[i][j] = 0;
    else if(adj[i][j]) distances[i][j] = adj[i][j];
    else distances[i][j] = INF;
  }
}

for(int k = 1; k <= n; k++){
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
    }
  }
}