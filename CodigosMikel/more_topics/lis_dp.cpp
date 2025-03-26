vector<int> v;
v.pb(a[0]);
for(int i=1;i<n;i++){
  if(a[i]>v[v.size()-1]){
    v.pb(a[i]);
  }
  else{
    int b=lower_bound(v.begin(),v.end(),a[i])-v.begin();
    v[b]=a[i];
  }
}
