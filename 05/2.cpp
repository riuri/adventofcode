#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

class Point {
public:
  int x, y;
  Point(int _x, int _y) : x(_x), y(_y) {}
  Point() : Point(0, 0) {}
  strong_ordering operator<=>(const Point &o) const {
    if (o.x == x) {
      return y <=> o.y;
    }
    return o.x <=> x;
  }
  bool operator!=(const Point &o) const {
    return *this <=> o != strong_ordering::equal;
  }
  Point operator+(const Point &o) const { return Point(x + o.x, y + o.y); }
  Point operator-(const Point &o) const { return Point(x - o.x, y - o.y); }
};

istream &operator>>(istream &in, Point &p) {
  char c;
  int x, y;
  if (in >> x >> c >> y) {
    p = Point(x, y);
  }
  return in;
}

class Segment {
public:
  Point a, b;
  Segment(Point _a, Point _b) : a(_a), b(_b) {}
  Segment() : Segment(Point(), Point()) {}
};

istream &operator>>(istream &in, Segment &s) {
  char c;
  Point a, b;
  if (in >> a >> c >> c >> b) {
    s = Segment(a, b);
  }
  return in;
}

void add_points(set<Point> &once, set<Point> &multiple, Segment seg) {
  int dirx = seg.b.x - seg.a.x;
  int diry = seg.b.y - seg.a.y;
  if (dirx != diry && dirx != -diry && dirx != 0 && diry != 0) {
    return;
  }
  Point dir(dirx ? dirx / abs(dirx) : 0, diry ? diry / abs(diry) : 0);
  Point p = seg.a - dir;
  do {
    p = p + dir;
    if (once.contains(p)) {
      multiple.insert(p);
    } else {
      once.insert(p);
    }
  } while (p != seg.b);
}

int main() {
  Segment s;
  set<Point> once, multiple;
  while (cin >> s) {
    add_points(once, multiple, s);
  }

  cout << multiple.size() << endl;
  return 0;
}
