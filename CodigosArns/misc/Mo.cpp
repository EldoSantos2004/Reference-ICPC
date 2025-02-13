ll n, q;
ll cur=0;
ll cnt[1000005];
ll answers[200500];
ll BLOCK_SIZE;
ll arr[200500];

pair< pair<ll, ll>, ll> queries[200500];

inline bool cmp(const pair< pair<ll, ll>, ll> &x, const pair< pair<ll, ll>, ll> &y) {
    ll block_x = x.first.first / BLOCK_SIZE;
    ll block_y = y.first.first / BLOCK_SIZE;
    if(block_x != block_y)
        return block_x < block_y;
    return x.first.second < y.first.second;
}

int main(){
    cin >> n >> q;
    BLOCK_SIZE =(ll)(sqrt(n));
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    for(int i = 0; i < q; i++) {
        cin >> queries[i].first.first >> queries[i].first.second;
        queries[i].second = i;
    }

    sort(queries, queries + q, cmp);

    ll l = 0, r = -1;

    for(int i = 0; i < q; i++) {
        ll left = queries[i].first.first;
        left--;
        ll right = queries[i].first.second;
        right--;

        while(r < right) {
            //operations
            r++;
        }
        while(r > right) {
            //operations
            r--;
        }

        while(l < left) {
            //operations
            l++;
        }
        while(l > left) {
            //operations
            l--;
        }
        answers[queries[i].second] = cur;
    }
}
