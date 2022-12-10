#include <iostream>

using namespace std;

int main() {
  int cur, last, count = 0;
  cin >> last;
  while (cin >> cur) {
    if (cur > last) {
      count++;
    }
    swap(cur, last);
  }
  cout << count << endl;
  return 0;
}
