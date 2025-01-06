#define MAXN 10000
int bit[MAXN];
void update(int x, int val){
	for(; x < MAXN; x+=x&-x)
		bit[x] += val;
}
int get(int x){
	int ans = 0;
	for(; x; x-=x&-x)
		ans += bit[x];
	return ans;
}