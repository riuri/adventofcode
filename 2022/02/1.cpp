#include <iostream>
using namespace std;

enum Shape { Rock = 0, Paper, Scissors };

int points(Shape other, Shape me) {
  switch ((me + 3 - other) % 3) {
    case 0:
      return 4 + me;
    case 1:
      return 7 + me;
    case 2:
      return 1 + me;
  }
  return 0;
}

int points_char(char other, char me) {
  return points((Shape)(other - 'A'), (Shape)(me - 'X'));
}

int main() {
  char other, me;
  long total = 0;
  while (cin >> other >> me) {
    total += points_char(other, me);
  }
  cout << total << endl;
  return 0;
}
