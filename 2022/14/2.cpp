#include <iostream>
#include <utility>
#include <set>
#include <string>

using namespace std;

typedef pair<int, int> Point;

void set_segment(set<Point> &s, Point a, Point b) {
  int direction_first = (b.first > a.first) - (a.first > b.first);
  int direction_second = (b.second > a.second) - (a.second > b.second);
  
  for (Point i = a; i != b; i.first += direction_first, i.second += direction_second) {
    s.insert(i);
  }
  s.insert(b);
}

bool read_and_set_line(set<Point> &s, int &lowest) {
  char comma;
  string discard;
  int first, second;
  cin >> first >> comma >> second;
  if (lowest < second) {
    lowest = second;
  }
  Point p(first, second);
  do {
    cin >> discard >> first >> comma >> second;
    if (lowest < second) {
      lowest = second;
    }
    Point n(first, second);
    set_segment(s, p, n);
    if (cin.peek() == '\n') {
      return true;
    }
    p = n;
  } while (!cin.eof());
  return false;
}

bool settle_sand(set<Point> &s, Point start, int lowest) {
  Point sand = start;
  while (sand.second <= lowest) {
    Point
      below(sand.first, sand.second + 1),
      left(sand.first - 1, sand.second + 1),
      right(sand.first + 1, sand.second + 1);
    if (!s.contains(below)) {
      sand = below;
    } else if (!s.contains(left)) {
      sand = left;
    } else if (!s.contains(right)) {
      sand = right;
    } else {
      s.insert(sand);
      return sand != start;
    }
  }
  s.insert(sand);
  return true;
}

int main() {
  set<Point> s;
  int lowest = -1;
  while (read_and_set_line(s, lowest));
  int count;
  Point start(500, 0);
  for (count = 1; settle_sand(s, start, lowest); ++count);

  cout << count << endl;
  return 0;
}
