/*
  Dynamic Segment Tree (Point Add, Range Sum)
  -------------------------------------------
  Indexing: [0, INF) or any large bounded range
  Time Complexity:
    - add(k, x): O(log U)
    - get_sum(l, r): O(log U)
      where U = range size (e.g., 1e9 if implicit bounds)

  Space Complexity: O(nodes visited or created) -> worst O(log U) per operation
*/

struct Vertex {
  int left, right;        // interval [left, right)
  int sum = 0;            // sum of elements in this interval
  Vertex *left_child = nullptr, *right_child = nullptr;

  Vertex(int lb, int rb) {
    left = lb;
    right = rb;
  }

  // Create children lazily only when needed
  void extend() {
    if (!left_child && left + 1 < right) {
      int mid = (left + right) / 2;
      left_child = new Vertex(left, mid);
      right_child = new Vertex(mid, right);
    }
  }

  // Add `x` to position `k`
  void add(int k, int x) {
    extend();
    sum += x;
    if (left_child) {
      if (k < left_child->right)
        left_child->add(k, x);
      else
        right_child->add(k, x);
    }
  }

  // Get sum over interval [lq, rq)
  int get_sum(int lq, int rq) {
    if (lq <= left && right <= rq)
      return sum;
    if (rq <= left || right <= lq)
      return 0;
    extend();
    return left_child->get_sum(lq, rq) + right_child->get_sum(lq, rq);
  }
};

Vertex *root = new Vertex(0, 1e9); // Range [0, 1e9)
root->add(5, 10);       // a[5] += 10
root->add(1000, 20);    // a[1000] += 20
cout << root->get_sum(0, 10) << '\n';     // sum of [0, 10) = 10
cout << root->get_sum(0, 2000) << '\n';   // sum of [0, 2000) = 30

