#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  while (cin >> input) {
    for (size_t i = 4; i <= input.size(); ++i) {
      if (input[i - 1] != input[i - 2]
        && input[i - 2] != input[i - 3]
        && input[i - 3] != input[i - 4]
        && input[i - 4] != input[i - 1]
        && input[i - 1] != input[i - 3]
        && input[i - 2] != input[i - 4]) {
        cout << i << endl;
        break;
      }
    }
  }
  return 0;
}
