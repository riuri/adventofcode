#include <iostream>
#include <vector>

using namespace std;

void count_bits(vector<int> &mode, const string &cur) {
  for (int i = 0; i < mode.size(); ++i) {
    mode[i] += cur[i] == '1';
  }
}

int main() {
  vector<int> mode;
  int count = 1;
  string cur;

  cin >> cur;
  mode.resize(cur.size(), 0);
  count_bits(mode, cur);

  while (cin >> cur) {
    count++;
    count_bits(mode, cur);
  }

  int gamma = 0;
  for (int m : mode) {
    gamma <<= 1;
    gamma += m > count / 2;
  }
  int epsilon = (1 << mode.size()) - 1 - gamma;

  cout << gamma * epsilon << endl;
  return 0;
}
