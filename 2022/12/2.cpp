#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <set>
#include <queue>

using namespace std;

bool not_check_height(const vector<string> &height_map, long ci, long cj, long ni, long nj) {
  return ni < 0
    || nj < 0
    || ni >= (long)height_map.size()
    || nj >= (long)height_map[0].size()
    || height_map[ni][nj] - height_map[ci][cj] > 1;
}

int main() {
  long Ei, Ej;
  vector<string> height_map;
  string line;
  while (cin >> line) {
    height_map.push_back(line);
  }

  queue<tuple<int, size_t, size_t>> q;
  set<tuple<long, long>> counted;
  for (size_t i = 0; i < height_map.size(); ++i) {
    for (size_t j = 0; j < height_map[i].size(); ++j) {
      if (height_map[i][j] == 'a') {
        q.emplace(0, i, j);
        counted.emplace(i, j);
      } else if (height_map[i][j] == 'E') {
        height_map[i][j] = 'z';
        Ei = i;
        Ej = j;
      }
    }
  }

  while (!q.empty()) {
    tuple<int, size_t, size_t> front = q.front();
    q.pop();
    int steps = get<0>(front);
    size_t i = get<1>(front);
    size_t j = get<2>(front);
    int step[] = { 0, 1, 0, -1};
    for (size_t k = 0; k < 4; ++k) {
      long ni = i + step[k];
      long nj = j + step[(k + 1) % 4];
      if (counted.contains(make_tuple(ni, nj))) {
        continue;
      }
      if (not_check_height(height_map, i, j, ni, nj)) {
        continue;
      }
      q.emplace(steps + 1, ni, nj);
      counted.emplace(ni, nj);
      if (ni == Ei && nj == Ej) {
        cout << steps + 1 << endl;
        return 0;
      }
    }
  }

  return 1;
}
