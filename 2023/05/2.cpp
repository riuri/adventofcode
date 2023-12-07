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

class RangeSet : public map<unsigned, unsigned> {};

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

  RangeSet operator()(RangeSet instance) const {
    RangeSet ret;

    for (auto p : instance) {
      unsigned start = p.first;
      unsigned length = p.second;
      while (length > 0) {
        auto it = dst.lower_bound(start);
        unsigned reduction;
        if (it == dst.end()) {
          it = dst.begin();
        }
        if (it->first + it->second.range <= start) {
          if (it == dst.begin()) {
            it = dst.end();
          } else {
            --it;
          }
        }
        if (it == dst.end()) {
          reduction = length;
          ret[start] = reduction;
        } else if (it->first > start) {
          reduction = min(length, it->first - start);
          ret[start] = reduction;
        } else {
          reduction = min(length, it->first + it->second.range - start);
          ret[start + it->second.dst - it->first] = reduction;
        }
        start += reduction;
        length -= reduction;
      }
    }

    return ret;
  }
};

int main() {
  RangeSet seeds;
  vector<RangeMap> mappings;
  string s;
  cin >> s; // seeds:
  while (cin >> s && isdigit(s[0])) {
    unsigned range;
    cin >> range;
    seeds[stoul(s)] = range;
  }

  while (cin >> s) {
    mappings.emplace_back();
    while (cin >> s && isdigit(s[0])) {
      unsigned src, range;
      cin >> src >> range;
      mappings.back().add(stoul(s), src, range);
    }
  }

  for (const auto& mapping : mappings) {
    seeds = mapping(seeds);
  }

  cout << seeds.begin()->first << endl;
  return 0;
}
