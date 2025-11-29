vector<vector<int>> rot(const vector<vector<int>>& a) {
    int n = a.size();
    int m = a[0].size();

    vector<vector<int>> res(m, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[j][n - 1 - i] = a[i][j];
        }
    }
    return res;
}
