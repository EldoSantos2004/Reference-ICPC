int lo[maxn], hi[maxn];
vector<int> tocheck[maxn];

bool c=true;
while(c){
		c=false;
		//initialize changes of structure to 0 

		for(int i=0;i<k;i++){
				if(low[i]!=high[i]){
						check[(low[i]+high[i])/2].pb(i);
				}
		}

		for(int i=0;i<m;i++){
				// apply change for ith query

				while(check[i].size()){
						c=true;
						int x=check[i].back();
						check[i].pop_back();

						if(operationToCheck){
								high[x]=i;
						}
						else{
								low[x]=i+1;
						}
				}
		}
}

