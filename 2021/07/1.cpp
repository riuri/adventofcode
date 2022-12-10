#include <iostream>
#include <set>

using namespace std;

int main() {
  int cur;
  multiset<int> s;
  while (cin >> cur) {
    s.insert(cur);
    char sep;
    cin >> sep;
  }

  auto it = s.cbegin();
  int fuel = 0;
  for (size_t i = 0; i < s.size() / 2; ++i, ++it) {
    fuel -= *it;
  }
  for (; it != s.cend(); ++it) {
    fuel += *it;
  }

  cout << fuel << endl;
  return 0;
}
