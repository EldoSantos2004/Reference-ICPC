struct min_cartesian_tree
{
  vector<int> par;
  vector<vector<int>> sons;
  int root;
  void init(int n, vector<int> &arr)
  {
    par.assign(n, -1);
    sons.assign(n, vector<int>(2, -1));
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
      int last = -1;
      while (!st.empty() && arr[st.top()] < arr[i])
      {
        last = st.top();
        st.pop();
      }
      if (!st.empty())
      {
        par[i] = st.top();
        sons[st.top()][1] = i;
      }
      if (last != -1)
      {
        par[last] = i;
        sons[i][0] = last;
      }
      st.push(i);
    }
    for (int i = 0; i < n; i++)
    {
      if (par[i] == -1)
      {
        root = i;
      }
    }
  }
};