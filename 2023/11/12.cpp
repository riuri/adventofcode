#include <iostream>
#include <set>
#include <string>

using namespace std;

class SpaceDimension {
  multiset<size_t> galaxies;
public:
  void insert_galaxy(size_t coordinate) {
    galaxies.insert(coordinate);
  }

  long long sum_pairwise(size_t expansion) const {
    size_t coordinate = 0, i = 0;
    long long sum = 0;
    auto it = galaxies.begin();
    while (true) {
      auto prev_it = it++;
      if (it == galaxies.end())
        break;
      i++;
      coordinate += *it - *prev_it;
      if (*it - *prev_it > 1) {
        // Increase the space in between
        coordinate += (*it - *prev_it - 1) * (expansion - 1);
      }
      sum += coordinate * (
        // Paths that end here
        i
        // Paths that start here
        - (galaxies.size() - i - 1));
    }
    return sum;
  }
};

int main() {
  string s;
  size_t line = 0;
  SpaceDimension dims[2];
  while (cin >> s) {
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '#') {
        dims[0].insert_galaxy(line);
        dims[1].insert_galaxy(i);
      }
    }
    line++;
  }

  cout << dims[0].sum_pairwise(2) + dims[1].sum_pairwise(2) << endl;
  cout << dims[0].sum_pairwise(10) + dims[1].sum_pairwise(10) << endl;
  cout << dims[0].sum_pairwise(100) + dims[1].sum_pairwise(100) << endl;
  cout << dims[0].sum_pairwise(1000000) + dims[1].sum_pairwise(1000000) << endl;
  return 0;
}
