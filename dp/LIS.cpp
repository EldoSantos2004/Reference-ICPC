vector <int> dp;
for (int i=0;i<n;i++){
    auto it=lower_bound(dp.begin(), dp.end(), v[i]);
    if(it==dp.end()){
        dp.push_back(v[i]);
    }
    else{
        int pos=it-dp.begin();
        dp[pos]=v[i];
    }
}
cout << dp.size() << endl;
