#include <set>
#include <iostream>
#include <utility>
#include <cstdlib>

using namespace std;

class State {
  pair<int, int> knot[10];
  set<pair<int, int>> visited = {{0, 0}};
  void move_head(char direction) {
    switch (direction) {
      case 'U':
        knot[0].second += 1;
        break;
      case 'D':
        knot[0].second -= 1;
        break;
      case 'L':
        knot[0].first -= 1;
        break;
      case 'R':
        knot[0].first += 1;
        break;
      default:
        break;
    }
  }
  bool touching(int i) {
    return abs(knot[i].first - knot[i + 1].first) <= 1
      && abs(knot[i].second - knot[i + 1].second) <= 1;
  }
  void move_tail(int i) {
    knot[i + 1].first += (knot[i + 1].first < knot[i].first) - (knot[i + 1].first > knot[i].first);
    knot[i + 1].second += (knot[i + 1].second < knot[i].second) - (knot[i + 1].second > knot[i].second);
    if (i == 8) {
      visited.insert(knot[9]);
    }
  }
public:
  void move(char direction) {
    move_head(direction);
    for (int i = 0; i < 9 && !touching(i); ++i) {
      move_tail(i);
    }
  }
  size_t result() {
    return visited.size();
  }
};

int main() {
  char direction;
  int steps;
  State state;
  while (cin >> direction >> steps) {
    for (int i = 0; i < steps; ++i) {
      state.move(direction);
    }
  }
  cout << state.result() << endl;
  return 0;
}
