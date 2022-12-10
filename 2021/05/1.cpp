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
  if (seg.a.x == seg.b.x) {
    for (int y = min(seg.a.y, seg.b.y); y <= max(seg.a.y, seg.b.y); ++y) {
      Point p(seg.a.x, y);
      if (once.contains(p)) {
        multiple.insert(p);
      } else {
        once.insert(p);
      }
    }
  } else if (seg.a.y == seg.b.y) {
    for (int x = min(seg.a.x, seg.b.x); x <= max(seg.a.x, seg.b.x); ++x) {
      Point p(x, seg.a.y);
      if (once.contains(p)) {
        multiple.insert(p);
      } else {
        once.insert(p);
      }
    }
  }
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
