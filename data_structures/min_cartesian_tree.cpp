struct min_cartesian_tree{
  vector<int> par;
  vector<vector<int>> sons;
  min_cartesian_tree(int n,vector<int> &arr){
    par.assign(n,-1);
    stack<int> st;
    for(int i=0;i<n;i++){
      int last=-1;
      while(!st.empty()&&arr[st.top()]>arr[i]){
        last=st.top();
        st.pop();
      }
      if(!st.empty()){
        par[i]=st.top();
        sons[st.top()].pb(i);
      }
      if(last!=-1){
        par[last]=i;
        sons[i].pb(last);
      }
      st.push(i);
    }
  }
};