#include <iostream>
#include <map>
#include <queue>
#include <set>

#define STEPS 100
#define SIZE 10

using namespace std;

int main() {
  // When do we expect i,j to flash?
  int step[SIZE][SIZE];
  // What octopi do we expect to flash at step i?
  map<int, set<pair<int, int>>> to_flash;
  char cur;

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      cin >> cur;
      step[i][j] = '9' - cur + 1; // Count from 1
      to_flash[step[i][j]].emplace(i, j);
    }
  }

  int flashes = 0;
  int sync_step = -1;
  while (true) {
    int next_step = to_flash.begin()->first;
    if (next_step > STEPS && sync_step >= 0) {
      break;
    }
    auto &flashed = to_flash[next_step];
    queue<pair<int, int>> q;
    for (auto it = flashed.cbegin(); it != flashed.cend(); ++it) {
      q.push(*it);
    }
    while (!q.empty()) {
      int i = q.front().first, j = q.front().second;
      to_flash[next_step + 10].emplace(i, j);
      step[i][j] = next_step + 10;

      for (int ii = i - 1; ii <= i + 1; ++ii) {
        if (ii < 0 || ii >= SIZE) {
          continue;
        }
        for (int jj = j - 1; jj <= j + 1; ++jj) {
          auto p = make_pair(ii, jj);
          if (jj < 0 || jj >= SIZE || flashed.contains(p)) {
            continue;
          }
          int old = step[ii][jj];
          to_flash[old - 1].insert(to_flash[old].extract(p));
          if (to_flash[old].empty()) {
            to_flash.erase(old);
          }
          step[ii][jj]--;
          if (step[ii][jj] == next_step) {
            q.push(p);
          }
        }
      }
      q.pop();
    }
    if (next_step <= STEPS) {
      flashes += flashed.size();
    }
    to_flash.erase(next_step);
    if (to_flash.size() <= 1 && sync_step < 0) {
      sync_step = next_step;
    }
  }

  cout << flashes << endl;
  cout << sync_step << endl;
  return 0;
}
