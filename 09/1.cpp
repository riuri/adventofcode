#include<iostream>
#include<vector>

using namespace std;

int main() {
  string cur, prev;
  vector<bool> cur_low, prev_low;
  cin >> prev;
  int sum = 0;
  prev_low.resize(prev.size(), true);
  cur_low.resize(prev.size(), true);
  for (size_t i = 1; i < prev.size(); ++i) {
    prev_low[i] = prev_low[i] && (prev[i] < prev[i-1]);
    prev_low[i-1] = prev_low[i-1] && (prev[i-1] < prev[i]);
  }
  while (cin >> cur) {
    for (size_t i = 0; i < cur_low.size(); ++i) {
      cur_low[i] = true;
    }
    prev_low[0] = prev_low[0] && (prev[0] < cur[0]);
    cur_low[0] = cur[0] < prev[0];
    if (prev_low[0]) {
      sum += prev[0] - '0' + 1;
    }
    for (size_t i = 1; i < cur.size(); ++i) {
      cur_low[i] = cur_low[i] && (cur[i] < cur[i-1]) && (cur[i] < prev[i]);
      cur_low[i-1] = cur_low[i-1] && (cur[i-1] < cur[i]);
      prev_low[i] = prev_low[i] && (prev[i] < cur[i]);
      if (prev_low[i]) {
        sum += prev[i] - '0' + 1;
      }
    }
    prev = cur;
    prev_low = cur_low;
  }
  for (size_t i = 0; i < cur_low.size(); ++i) {
    if (cur_low[i]) {
      sum += cur[i] - '0' + 1;
    }
  }

  cout << sum << endl;
  return 0;
}
