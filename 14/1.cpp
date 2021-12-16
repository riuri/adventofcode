#include <iostream>
#include <limits>
#include <map>
#include <string>

using namespace std;

class Node {
public:
  Node *prev = nullptr, *next = nullptr;
  char c;
  Node(char _c) : c(_c) {}
};

typedef array<char, 2> Pair;

class Consumer {
  map<char, int> counts;

public:
  void operator<<(char c) { counts[c]++; }
  int result() const {
    int high = -1, low = numeric_limits<int>::max();
    for (const auto &[c, count] : counts) {
      high = max(high, count);
      low = min(low, count);
    }
    return high - low;
  }
};

template <typename T>
void grow_polymer(T &consumer, const Node &node, int depth) {
  if (depth > 0 && node.prev) {
    grow_polymer(consumer, *node.prev, depth - 1);
  }
  consumer << node.c;
  if (depth > 0 && node.next) {
    grow_polymer(consumer, *node.next, depth - 1);
  }
}

template <typename T>
void grow_polymer(T &consumer, const map<Pair, Node> &filled_rules,
                  const string &s, int depth) {
  if (s.size() == 0) {
    return;
  }
  for (size_t i = 0; i < s.size() - 1; ++i) {
    consumer << s[i];
    if (depth > 0) {
      grow_polymer(consumer, filled_rules.at(Pair{s[i], s[i + 1]}), depth - 1);
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

  Consumer c;
  grow_polymer(c, rules, initial, 10);
  cout << c.result() << endl;
  return 0;
}
