struct Point {
  int x;
  int y;
  Point(int i, int j) : x(i), y(j) {}

  bool operator==(const Point &p) { return x == p.x && y == p.y; }

  bool operator!=(const Point &p) { return !(*this == p); }
};