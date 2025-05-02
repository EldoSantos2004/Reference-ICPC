/*
  Bit Trie (Binary Trie for Integers)
  -----------------------------------
  Indexing: 0-based
  Bit Width: [0, MAX_BIT] inclusive (e.g., 31 for 32-bit integers)
  Time Complexity:
    - Insert: O(MAX_BIT)
    - Query: O(MAX_BIT)
  Space Complexity: O(N * MAX_BIT) nodes (in worst case, 1 per bit per number)
*/

const int K = 2; // Each node has 2 branches (bit 0 or 1)
const int MAX_BIT = 30; // Max bit position (for 32-bit integers)

struct Vertex {
  int next[K]; // next[0] = child for bit 0, next[1] = child for bit 1

  Vertex() {
    fill(begin(next), end(next), -1); // -1 means no child
  }
};

vector<Vertex> trie; // Trie nodes

// Inserts a number into the binary trie
void insert(int num) {
  int v = 0; // Start from root
  for (int j = MAX_BIT; j >= 0; --j) {
    int c = (num >> j) & 1; // Extract j-th bit (0 or 1)
    if (trie[v].next[c] == -1) {
      trie[v].next[c] = trie.size();
      trie.emplace_back(); // Add new node
    }
    v = trie[v].next[c]; // Move to next node
  }
}
