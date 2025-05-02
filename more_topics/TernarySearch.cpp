/*
  Ternary Search (for continuous unimodal functions)
  --------------------------------------------------
  Finds the maximum (or minimum) value of a unimodal function f(x) in [l, r]
  Indexing: continuous domain (double)
  Bounds:
    - Search range is [l, r]
    - Precision controlled by eps
  Time Complexity: O(log((r - l) / eps))
  - For minimum, reverse the condition (if f1 > f2 then l = m1)
*/
double ternary_search(double l, double r) {
  double eps = 1e-9; // precision error
  while (r - l > eps) {
    double m1 = l + (r - l) / 3;
    double m2 = r - (r - l) / 3;
    double f1 = f(m1); // evaluate function at m1
    double f2 = f(m2); // evaluate function at m2
    if (f1 < f2)
      l = m1;  // move left bound up if increasing
    else
      r = m2;  // move right bound down if decreasing
  }
  return f(l); // return value at the best point
}
