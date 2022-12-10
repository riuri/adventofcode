#include <iostream>
#define SLIDING_WINDOW 3

using namespace std;

int main() {
  int window[SLIDING_WINDOW], count = 0, n = 0, cur;
  for (int i = 0; i < SLIDING_WINDOW; ++i) {
    cin >> window[i];
  }
  while (cin >> cur) {
    int i = n++ % SLIDING_WINDOW;
    if (cur > window[i]) {
      count++;
    }
    swap(cur, window[i]);
  }
  cout << count << endl;
  return 0;
}
