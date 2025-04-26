const int K = 2;
struct Vertex {
    int next[K];
 
    Vertex() {
        fill(begin(next), end(next), -1);
    }
};


//insert
for(int j=30;j>=0;j--) {
    int c = 1&(a[i]>>j);
    if (trie[v].next[c] == -1) {
        trie[v].next[c] = trie.size();
        trie.emplace_back();
        d.pb(-1);
    }
    v = trie[v].next[c];
}
