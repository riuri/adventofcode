#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
  vector<bool> sequence;
  string s, node, left, right;
  map<string, string[2]> m;

  cin >> s;
  for (char c : s) {
    sequence.push_back(c == 'R');
  }

  while (cin >> node >> s >> left >> right) {
    left.erase(0, 1);
    left.erase(3);
    right.erase(3);
    m[node][0] = left;
    m[node][1] = right;
  }

  long count = 0;
  size_t i = 0;
  s = "AAA";
  while (s != "ZZZ") {
    s = m[s][sequence[i]];
    i = (i + 1) % sequence.size();
    count++;
  }

  cout << count << endl;
  return 0;
}
