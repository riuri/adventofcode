#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

int main() {
  string s;
  string time;
  string distance;

  cin >> s;
  while (cin >> s && isdigit(s[0])) {
    time += s;
  }
  while (cin >> s && isdigit(s[0])) {
    distance += s;
  }

  long T = stol(time);
  long delta = T * T - 4 * stol(distance);
  if (delta <= 0) {
    cout << "0" << endl;
    return 0;
  }
  long int result = 2 * ceil((sqrt(delta) - T % 2) / 2) + T % 2 - 1;
  cout << result << endl;

  return 0;
}
