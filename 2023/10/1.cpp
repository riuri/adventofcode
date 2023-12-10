#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct position {
  size_t l, c;
};

struct position find_start(const vector<string> &grid) {
  for (size_t i = 0; i < grid.size(); ++i) {
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == 'S')
        return { i, j };
    }
  }
  return {};
}

inline char at(const vector<string> &grid, const struct position &pos) {
  return grid[pos.l][pos.c];
}

int main() {
  vector<string> grid;
  string s;
  while (cin >> s) {
    grid.push_back(s);
  }
  size_t loop = 0;
  struct position cur = find_start(grid), prev;
  do {
    switch (at(grid, cur)) {
      case '|':
        if (prev.l + 1 == cur.l) {
          prev = cur;
          cur.l++;
        } else {
          prev = cur;
          cur.l--;
        }
        break;
      case '-':
        if (prev.c + 1 == cur.c) {
          prev = cur;
          cur.c++;
        } else {
          prev = cur;
          cur.c--;
        }
        break;
      case 'L':
        if (prev.l == cur.l) {
          prev = cur;
          cur.l--;
        } else {
          prev = cur;
          cur.c++;
        }
        break;
      case 'J':
        if (prev.l == cur.l) {
          prev = cur;
          cur.l--;
        } else {
          prev = cur;
          cur.c--;
        }
        break;
      case '7':
        if (prev.l == cur.l) {
          prev = cur;
          cur.l++;
        } else {
          prev = cur;
          cur.c--;
        }
        break;
      case 'F':
        if (prev.l == cur.l) {
          prev = cur;
          cur.l++;
        } else {
          prev = cur;
          cur.c++;
        }
        break;
      case 'S':
        prev = cur;
        cur = { prev.l - 1, prev.c };
        const string up = "|7F";
        if (prev.l > 0 && up.contains(at(grid, cur))) {
          break;
        }
        const string left = "-LF";
        cur = { prev.l, prev.c - 1 };
        if (prev.c > 0 && left.contains(at(grid, cur))) {
          break;
        }
        const string down = "|LJ";
        cur = { prev.l + 1, prev.c };
        if (cur.l < grid.size() && down.contains(at(grid, cur))) {
          break;
        }
        cur = { prev.l, prev.c + 1 };
    }
    loop++;
  } while (at(grid, cur) != 'S');

  cout << loop/2 << endl;
  return 0;
}
