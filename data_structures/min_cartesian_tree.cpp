/*
  Min Cartesian Tree
  -------------------
  Indexing: 0-based
  Time Complexity: O(n)
  Space Complexity: O(n)
  Tree Properties:
    - Binary tree where in-order traversal = original array
    - Tree satisfies min-heap property: parent <= children
    - `par[i]`: parent of node i
    - `sons[i][0]`: left child, `sons[i][1]`: right child
    - `root`: index of root node

  Use cases:
    - RMQ construction
    - LCA over RMQ via Cartesian Tree
*/

struct min_cartesian_tree {
  vector<int> par;           // parent for each node
  vector<vector<int>> sons;  // left and right children
  int root;

  void init(int n, const vector<int> &arr) {
    par.assign(n, -1);
    sons.assign(n, vector<int>(2, -1)); // 0 = left, 1 = right
    stack<int> st;

    for (int i = 0; i < n; i++) {
      int last = -1;

      // Maintain increasing stack -> build min Cartesian Tree
      // Change > to < for max Cartesian Tree
      while (!st.empty() && arr[st.top()] > arr[i]) {
        last = st.top();
        st.pop();
      }

      if (!st.empty()) {
        par[i] = st.top();
        sons[st.top()][1] = i;
      }
      if (last != -1) {
        par[last] = i;
        sons[i][0] = last;
      }

      st.push(i);
    }

    for (int i = 0; i < n; i++) {
      if (par[i] == -1) {
        root = i;
      }
    }
  }
};
// Example usage:
vector<int> a = {4, 2, 6, 1, 3};
min_cartesian_tree ct;
ct.init(a.size(), a);
cout << "Root index: " << ct.root << '\n';
