#include <iostream>
#include <optional>
#include <set>
#include <utility>
#include <vector>

using namespace std;

inline int fold1d(int pos, int fold) {
  return pos > fold ? (2 * fold - pos) : pos;
}

set<pair<int, int>> foldall(const set<pair<int, int>> &input,
                            const vector<int> &xx, const vector<int> &yy,
                            int &maxx, int &maxy) {
  set<pair<int, int>> output;
  for (const auto &point : input) {
    int x = point.first;
    int y = point.second;
    for (int xfold : xx) {
      x = fold1d(x, xfold);
    }
    for (int yfold : yy) {
      y = fold1d(y, yfold);
    }
    maxx = max(x, maxx);
    maxy = max(y, maxy);
    output.emplace(x, y);
  }
  return output;
}

int main() {
  int x, y;
  char sep;
  set<pair<int, int>> input;
  while (true) {
    cin >> x;
    if (cin.fail()) {
      break;
    }
    cin >> sep >> y;
    input.emplace(x, y);
  }
  cin.clear();

  string fold, along, direction;
  vector<int> xx, yy;
  vector<int> *first = nullptr;
  while (cin >> fold >> along >> direction) {
    int pos = stoi(string(direction, 2));
    if (direction[0] == 'x') {
      xx.push_back(pos);
      if (!first) {
        first = &xx;
      }
    } else {
      yy.push_back(pos);
      if (!first) {
        first = &yy;
      }
    }
  }

  int maxx = -1, maxy = -1;
  if (first) {
    vector<int> empty, one(1, (*first)[0]);
    if (first == &xx) {
      cout << foldall(input, one, empty, maxx, maxy).size() << endl;
    } else if (first == &yy) {
      cout << foldall(input, empty, one, maxx, maxy).size() << endl;
    }
  }
  maxx = -1;
  maxy = -1;
  auto output = foldall(input, xx, yy, maxx, maxy);
  for (y = 0; y <= maxy; ++y) {
    for (x = 0; x <= maxx; ++x) {
      cout << (output.contains(make_pair(x, y)) ? '#' : '.');
    }
    cout << endl;
  }
  return 0;
}
