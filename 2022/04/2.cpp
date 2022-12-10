#include <iostream>

using namespace std;

int main() {
  int s1, s2, e1, e2, total = 0;
  char d;
  while (cin >> s1 >> d >> e1 >> d >> s2 >> d >> e2) {
    if ((s1 <= e2 && s2 <= e1)
      || (s2 <= e1 && s1 <= e2)) {
      total++;
    }
  }
  cout << total << endl;
  return 0;
}
