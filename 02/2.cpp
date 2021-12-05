#include <iostream>
#include <string>

using namespace std;

int main() {
  int x = 0, y = 0, aim = 0, cur;
  string dir;

  while (cin >> dir >> cur) {
    if (dir == "up") {
      aim -= cur;
    } else if (dir == "down") {
      aim += cur;
    } else { // forward
      x += cur;
      y += aim * cur;
    }
  }
  cout << x * y << endl;
  return 0;
}
