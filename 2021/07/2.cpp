#include <cmath>
#include <iostream>
#include <set>

using namespace std;

int get_fuel(const multiset<int> &s, int loc) {
  int fuel = 0;
  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    fuel += (abs(*it - loc)) * (abs(*it - loc) + 1) / 2;
  }
  return fuel;
}

int main() {
  int cur, sum = 0;
  multiset<int> s;
  while (cin >> cur) {
    s.insert(cur);
    sum += cur;
    char sep;
    cin >> sep;
  }

  double mid = (double)sum / s.size();

  cout << min(get_fuel(s, ceil(mid)), get_fuel(s, floor(mid))) << endl;
  return 0;
}
