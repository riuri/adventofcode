#include <iostream>
#include <string>

using namespace std;

class State {
  int cycle;
  int X = 1;
  string accumulate;

public:
  void noop() {
    accumulate += (abs(cycle % 40 - X) <= 1) ? '#' : '.';
    cycle++;
    if (cycle % 40 == 0) {
      accumulate += '\n';
    }
  }
  string result() {
    return accumulate;
  }
  void addx(int x) {
    noop();
    noop();
    X += x;
  }
};

int main() {
  State state;
  string op;
  int value;
  while(cin >> op) {
    if (op == "noop") {
      state.noop();
    } else if (op == "addx") {
      cin >> value;
      state.addx(value);
    }
  }
  cout << state.result();
  return 0;
}
