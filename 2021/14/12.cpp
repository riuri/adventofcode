#include <iostream>
#include <limits>
#include <map>
#include <string>

using namespace std;

class Count {
  map<char, long long int> counts;
  Count(map<char, long long int> _counts) : counts(_counts) {}

public:
  Count(char _c) { counts[_c] = 1; }
  Count() {}
  Count &operator<<(const Count &o) {
    for (const auto &[k, v] : o.counts) {
      counts[k] += v;
    }
    return *this;
  }
  Count &operator<<(char c) {
    counts[c]++;
    return *this;
  }
  long long int result() const {
    long long int high = -1, low = numeric_limits<long long int>::max();
    for (const auto &[c, count] : counts) {
      high = max(high, count);
      low = min(low, count);
    }
    return high - low;
  }
};

class Node {
  map<int, Count> rounds;

public:
  char c;
  Node *prev = nullptr, *next = nullptr;
  Node(char _c) : c(_c) { rounds[1] = Count(_c); }
  Count get_at_round(int round) {
    auto it = rounds.find(round);
    if (it == rounds.end()) {
      Count inc = Count(c);
      if (prev) {
        inc << prev->get_at_round(round - 1);
      }
      if (next) {
        inc << next->get_at_round(round - 1);
      }
      rounds[round] = inc;
      return inc;
    }
    return it->second;
  }
};

typedef array<char, 2> Pair;

template <typename T> void grow_polymer(T &consumer, Node &node, int depth) {
  consumer << node.get_at_round(depth);
}

template <typename T>
void grow_polymer(T &consumer, map<Pair, Node> &filled_rules, const string &s,
                  int depth) {
  if (s.size() == 0) {
    return;
  }
  for (size_t i = 0; i < s.size() - 1; ++i) {
    consumer << s[i];
    if (depth > 0) {
      grow_polymer(consumer, filled_rules.at(Pair{s[i], s[i + 1]}), depth);
    }
  }
  consumer << s[s.size() - 1];
}

void fill_rules(map<Pair, Node> &rules) {
  for (auto &[k, v] : rules) {
    auto prev = rules.find({k[0], v.c});
    if (prev != rules.end()) {
      v.prev = &prev->second;
    }
    auto next = rules.find({v.c, k[1]});
    if (next != rules.end()) {
      v.next = &next->second;
    }
  }
}

int main() {
  string initial;
  cin >> initial;
  map<Pair, Node> rules;

  string pair, arrow, create;
  while (cin >> pair >> arrow >> create) {
    rules.emplace(Pair{pair[0], pair[1]}, create[0]);
  }

  fill_rules(rules);

  Count c;
  grow_polymer(c, rules, initial, 10);
  cout << c.result() << endl;
  Count c2;
  grow_polymer(c2, rules, initial, 40);
  cout << c2.result() << endl;
  return 0;
}
