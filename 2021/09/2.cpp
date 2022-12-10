#include <iostream>
#include <queue>
#include <vector>

#define NO_BASIN 0
#define NOT_DETERMINED -1

using namespace std;

size_t assign(vector<vector<int>> &basin, int row, int col, int colour) {
  basin[row][col] = colour;
  size_t sum = 1;
  int deltas[4] = {1, 0, -1, 0};
  for (int i = 0; i < 4; ++i) {
    int nrow = row + deltas[i];
    int ncol = col + deltas[(i + 3) % 4];

    if (nrow < 0 || (size_t)nrow >= basin.size() || ncol < 0 ||
        (size_t)ncol >= basin[nrow].size() || !basin[nrow][ncol]) {
      continue;
    }
    if (basin[nrow][ncol] == NOT_DETERMINED) {
      sum += assign(basin, nrow, ncol, colour);
    }
  }
  return sum;
}

priority_queue<size_t> basin_sizes(vector<vector<int>> &basin) {
  priority_queue<size_t> pq;
  int assignment = 1;
  for (size_t i = 0; i < basin.size(); ++i) {
    for (size_t j = 0; j < basin[i].size(); ++j) {
      if (basin[i][j] == NOT_DETERMINED) {
        pq.push(assign(basin, i, j, assignment++));
      }
    }
  }
  return pq;
}

int main() {
  string cur;
  vector<vector<int>> basin;
  unsigned long long int prod = 1;
  while (cin >> cur) {
    vector<int> row(cur.size());
    for (size_t i = 0; i < cur.size(); ++i) {
      row[i] = cur[i] == '9' ? NO_BASIN : NOT_DETERMINED;
    }
    basin.push_back(row);
  }

  auto pq = basin_sizes(basin);
  for (int i = 0; i < 3; ++i) {
    prod *= pq.top();
    pq.pop();
  }

  cout << prod << endl;
  return 0;
}
