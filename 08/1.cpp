#include <iostream>
#include <string>

using namespace std;

int check(size_t size) {
  return 1 & ((size >> 1) ^ ((size >> 2) & ~size));
}

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
      count += check(cur.size());
    }
  }
  
  cout << count << endl;;
  return 0;
}
