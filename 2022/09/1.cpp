#include <set>
#include <iostream>
#include <utility>
#include <cstdlib>

using namespace std;

class State {
  pair<int, int> head, tail;
  set<pair<int, int>> visited = {{0, 0}};
  void move_head(char direction) {
    switch (direction) {
      case 'U':
        head.second += 1;
        break;
      case 'D':
        head.second -= 1;
        break;
      case 'L':
        head.first -= 1;
        break;
      case 'R':
        head.first += 1;
        break;
      default:
        break;
    }
  }
  bool touching() {
    return abs(head.first - tail.first) <= 1
      && abs(head.second - tail.second) <= 1;
  }
  void move_tail() {
    tail.first += (tail.first < head.first) - (tail.first > head.first);
    tail.second += (tail.second < head.second) - (tail.second > head.second);
    visited.insert(tail);
  }
public:
  void move(char direction) {
    move_head(direction);
    if (!touching()) {
      move_tail();
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
