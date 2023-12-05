#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Union {
  vector<int> regions;
public:
  int size() const {
    int total = 0;
    for (size_t i = 0; 2 * i < regions.size(); ++i) {
      total += regions[2 * i + 1] - regions[2 * i];
    }
    return total;
  }

  void add(int start, int end) {
    if (regions.size() == 0) {
      regions.push_back(start);
      regions.push_back(end);
      return;
    }
    size_t i, j;
    for (i = 0; i < regions.size() && regions[i] < start; ++i);
    for (j = 0; j < regions.size() && regions[j] < end; ++j);
    if (i % 2) {
      i--;
      if (j % 2 == 0) {
        regions[--j] = end;
      }
    } else {
      regions.insert(next(regions.begin(), i), start);
      j++;
      if (j % 2) {
        regions.insert(next(regions.begin(), j), end);
      }
    }
    regions.erase(next(regions.begin(), i + 1), next(regions.begin(), j));
  }
};

class Point: public pair<int, int> {};
istream& operator>>(istream& in, Point &p) {
  char c;
  string s;
  return in >> c >> c >> p.first >> s >> c >> c >> p.second;
}

int main() {
  Union u;
  int y = 2000000;
  set<int> existing;
  if (cin.peek() == 'x') {
    // For sample y=10
    Point p;
    cin >> p;
    y = p.second;
  }
  string ign;
  Point sensor, beacon;
  while (cin >> ign >> ign >> sensor >> ign >> ign >> ign >> ign >> ign >> beacon) {
    int distance = abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
    if (beacon.second == y) {
      existing.insert(beacon.first);
    }
    int remaining = distance - abs(y - sensor.second);
    if (remaining >= 0) {
      u.add(sensor.first - remaining, sensor.first + remaining + 1);
    }
  }
  cout << u.size() - existing.size() << endl;
}
