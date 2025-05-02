/*
  Sqrt Decomposition (String Block Cut and Move)
  ----------------------------------------------
  Operation:
    - Supports moving substrings using block cut logic
    - Rebuilds when too many blocks (for performance)

  Indexing: 0-based
  String Bounds: [0, n)
  Time Complexity:
    - cut(a, b): O(sqrt(n))
    - rebuildDecomp(): O(n)
  When to rebuild: after too many block splits

  Use case: performing multiple cut/paste operations efficiently on large strings
*/

const int MAXI = 350; // = sqrt(n), for n up to 1e5

int n, numBlocks;
string s;

struct Block {
  int l, r; // indices into string s
  int sz() const { return r - l; }
};

Block blocks[2 * MAXI];     // current block array
Block newBlocks[2 * MAXI];  // used temporarily during cutting

// Rebuilds the entire decomposition into 1 block (or balanced ones)
void rebuildDecomp() {
  string newS = s;
  int k = 0;
  // Flatten string using current block structure
  for (int i = 0; i < numBlocks; i++) {
    for (int j = blocks[i].l; j < blocks[i].r; j++) {
      newS[k++] = s[j];
    }
  }
  // Reset to one big block
  numBlocks = 1;
  blocks[0] = {0, n};
  s = newS;
}

// Cut [a, b) into a separate region and reorder it to the end
void cut(int a, int b) {
  int pos = 0, curBlock = 0;
  // Pass 1: Split blocks to isolate [a, b)
  for (int i = 0; i < numBlocks; i++) {
    Block B = blocks[i];
    bool containsA = (pos < a && pos + B.sz() > a);
    bool containsB = (pos < b && pos + B.sz() > b);
    int cutA = B.l + a - pos;
    int cutB = B.l + b - pos;

    if (containsA && containsB) {
      newBlocks[curBlock++] = {B.l, cutA};
      newBlocks[curBlock++] = {cutA, cutB};
      newBlocks[curBlock++] = {cutB, B.r};
    } else if (containsA) {
      newBlocks[curBlock++] = {B.l, cutA};
      newBlocks[curBlock++] = {cutA, B.r};
    } else if (containsB) {
      newBlocks[curBlock++] = {B.l, cutB};
      newBlocks[curBlock++] = {cutB, B.r};
    } else {
      newBlocks[curBlock++] = B;
    }

    pos += B.sz();
  }

  // Pass 2: Reorder — move [a, b) to the end
  pos = 0;
  numBlocks = 0;

  // First add all blocks not in [a, b)
  for (int i = 0; i < curBlock; i++) {
    if (pos < a || pos >= b)
      blocks[numBlocks++] = newBlocks[i];
    pos += newBlocks[i].sz();
  }

  // Then add blocks in [a, b)
  pos = 0;
  for (int i = 0; i < curBlock; i++) {
    if (pos >= a && pos < b)
      blocks[numBlocks++] = newBlocks[i];
    pos += newBlocks[i].sz();
  }
}
// Example usage
int main() {
  cin >> s;
  n = s.size();
  numBlocks = 1;
  blocks[0] = {0, n};

  int q; cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    cut(a, b); // move [a, b) to the end

    if (numBlocks > MAXI) rebuildDecomp();
  }

  rebuildDecomp(); // flatten before output
  cout << s << '\n';
}
