/*
  2D Segment Tree (Sum over Rectangles)
  -------------------------------------
  Indexing: 0-based
  Grid Size: n * m
  Time Complexity:
    - build: O(nm log n log m)
    - point update: O(log n log m)
    - range query [x1..x2][y1..y2]: O(log n log m)
  Space Complexity: O(4n × 4m)
*/

const int MAXN = 505;
int n, m;             // grid dimensions
int a[MAXN][MAXN];    // input grid
int t[4 * MAXN][4 * MAXN]; // segment tree

// Build the tree along y-axis (internal to each x-interval)
void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
  if (ly == ry) {
    if (lx == rx)
      t[vx][vy] = a[lx][ly];
    else
      t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
  } else {
    int my = (ly + ry) / 2;
    build_y(vx, lx, rx, vy * 2, ly, my);
    build_y(vx, lx, rx, vy * 2 + 1, my + 1, ry);
    t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
  }
}

// Build the tree along x-axis and call build_y for each
void build_x(int vx, int lx, int rx) {
  if (lx != rx) {
    int mx = (lx + rx) / 2;
    build_x(vx * 2, lx, mx);
    build_x(vx * 2 + 1, mx + 1, rx);
  }
  build_y(vx, lx, rx, 1, 0, m - 1);
}

// Query along y-axis in a fixed x-node
int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
  if (ly > ry) return 0;
  if (ly == tly && ry == try_) return t[vx][vy];
  int tmy = (tly + try_) / 2;
  return sum_y(vx, vy * 2, tly, tmy, ly, min(ry, tmy))
       + sum_y(vx, vy * 2 + 1, tmy + 1, try_, max(ly, tmy + 1), ry);
}

// Query sum in rectangle [lx..rx][ly..ry]
int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
  if (lx > rx) return 0;
  if (lx == tlx && trx == rx)
    return sum_y(vx, 1, 0, m - 1, ly, ry);
  int tmx = (tlx + trx) / 2;
  return sum_x(vx * 2, tlx, tmx, lx, min(rx, tmx), ly, ry)
       + sum_x(vx * 2 + 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
}

// Update along y-axis for fixed x-node
void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
  if (ly == ry) {
    if (lx == rx)
      t[vx][vy] = new_val;
    else
      t[vx][vy] = t[vx * 2][vy] + t[vx * 2 + 1][vy];
  } else {
    int my = (ly + ry) / 2;
    if (y <= my)
      update_y(vx, lx, rx, vy * 2, ly, my, x, y, new_val);
    else
      update_y(vx, lx, rx, vy * 2 + 1, my + 1, ry, x, y, new_val);
    t[vx][vy] = t[vx][vy * 2] + t[vx][vy * 2 + 1];
  }
}

// Update point (x, y) to new_val
void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
  if (lx != rx) {
    int mx = (lx + rx) / 2;
    if (x <= mx)
      update_x(vx * 2, lx, mx, x, y, new_val);
    else
      update_x(vx * 2 + 1, mx + 1, rx, x, y, new_val);
  }
  update_y(vx, lx, rx, 1, 0, m - 1, x, y, new_val);
}
