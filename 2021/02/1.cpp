#include <iostream>
#include <string>

using namespace std;

int main() {
  int x = 0, y = 0, cur;
  string dir;

  while (cin >> dir >> cur) {
    if (dir == "up") {
      y -= cur;
    } else if (dir == "down") {
      y += cur;
    } else { // forward
      x += cur;
    }
  }
  cout << x * y << endl;
  return 0;
}
