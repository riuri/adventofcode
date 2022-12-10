#include <iostream>
#include <string>

using namespace std;

int main() {
  string cur, ignore;
  int count = 0;
  char separator;
  while (cin >> ignore) {
    for (int i = 0; i < 10; ++i) {
      cin >> ignore;
    }
    while (true) {
      separator = cin.peek();
      if (separator == '\n') {
        break;
      }
      cin >> cur;
      size_t size = cur.size();
      count += 1 & ((size >> 1) ^ ((size >> 2) & ~size));
    }
  }

  cout << count << endl;
  return 0;
}
