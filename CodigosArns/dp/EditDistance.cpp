string s, t; cin >> s>> t;
    int n=s.length(), m=t.length();
    for (int i=0;i<=n;i++){
        fill(dp[i], dp[i]+m+1, 1e9);
    }
    dp[0][0]=0;
    for (int i=0;i<=n;i++){
        for (int j=0;j<=m;j++){
            if(j){
                dp[i][j]=min(dp[i][j], dp[i][j-1]+1);
            }
            if(i){
                dp[i][j]=min(dp[i][j], dp[i-1][j]+1);
            }
            if(i && j){
                int a=(s[i-1]!=t[j-1] ? 1:0);
                dp[i][j]=min(dp[i][j], dp[i-1][j-1]+a);
            }
        }
    }
