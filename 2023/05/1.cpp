#include <iostream>
#include <functional>
#include <string>
#include <limits>
#include <map>

using namespace std;

class DstRange {
public:
  unsigned dst, range;
  DstRange(unsigned _dst, unsigned _range): dst(_dst), range(_range) {}
  DstRange() : dst(0), range(0) {}
};

class RangeMap {
  map<unsigned, DstRange, greater<unsigned>> dst;
public:
  void add(unsigned destination, unsigned source, unsigned range) {
    dst[source] = DstRange(destination, range);
  }
  unsigned operator()(unsigned instance) const {
    auto it = dst.lower_bound(instance);
    if (it == dst.end() || it->first + it->second.range <= instance) {
      return instance;
    }
    return instance + it->second.dst - it->first;
  }
};

int main() {
  vector<unsigned> seeds;
  vector<RangeMap> mappings;
  string s;
  cin >> s; // seeds:
  while (cin >> s && isdigit(s[0])) {
    seeds.push_back(stoul(s));
  }

  while (cin >> s) {
    mappings.emplace_back();
    while (cin >> s && isdigit(s[0])) {
      unsigned src, range;
      cin >> src >> range;
      mappings.back().add(stoul(s), src, range);
    }
  }

  unsigned lowest = numeric_limits<unsigned>::max();
  for (unsigned seed : seeds) {
    for (const auto& mapping : mappings) {
      seed = mapping(seed);
    }
    lowest = min(lowest, seed);
  }

  cout << lowest << endl;
  return 0;
}
