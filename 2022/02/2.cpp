#include <iostream>
using namespace std;

int points(int other, int outcome) {
  int me = (other + outcome + 2) % 3;
  switch (outcome) {
    case 0:
      return 1 + me;
    case 1:
      return 4 + me;
    case 2:
      return 7 + me;
  }
  return 0;
}

int points_char(char other, char outcome) {
  return points(other - 'A', outcome - 'X');
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
