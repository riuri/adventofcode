#include <iostream>
#include <queue>
#include <compare>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Cycle {
public:
  vector<bool> initial;
  size_t cycle_size;
  set<size_t> moduli;
  Cycle() {}
  Cycle(const map<string, string[2]> &m, string state, const vector<bool> &sequence) {
    vector<string> states = { state };
    bool cycle_found = false;
    size_t sequence_it = 0;
    while (!cycle_found) {
      states.push_back(m.at(states.back())[sequence[sequence_it]]);
      sequence_it = (sequence_it + 1) % sequence.size();
      for (size_t i = (states.size() - 1) % sequence.size(); i < states.size() - 1; i += sequence.size()) {
        if (states[i] == states.back()) {
          cycle_size = states.size() - i - 1;
          for (size_t j = 0; j < i; ++j) {
            initial.push_back(states[i][2] == 'Z');
          }
          for (size_t j = i; j < states.size() - 1; ++j) {
            if (states[j][2] == 'Z')
              moduli.insert(j % cycle_size);
          }
          cycle_found = true;
          break;
        }
      }
    }
  }
  size_t first() const {
    for (size_t i = 0; i < initial.size(); ++i) {
      if (initial[i]) return i;
    }
    auto it = moduli.lower_bound(initial.size());
    if (it == moduli.end()) {
      return cycle_size + *moduli.begin();
    }
    return *it;
  }
  weak_ordering operator<=>(const Cycle &other) const {
    if (cycle_size < other.cycle_size) {
      return weak_ordering::greater;
    } else if (cycle_size > other.cycle_size) {
      return weak_ordering::less;
    }
    return weak_ordering::equivalent;
  }
};

Cycle operator+(const Cycle &a, const Cycle &b) {
  Cycle ret;
  const Cycle &less = (a.initial.size() > b.initial.size())
    ? b
    : a;
  const Cycle &more = (a.initial.size() > b.initial.size())
    ? a
    : b;
  for (size_t i = 0; i < less.initial.size(); ++i) {
    ret.initial.push_back(less.initial[i] && more.initial[i]);
  }
  for (size_t i = less.initial.size(); i < more.initial.size(); ++i) {
    ret.initial.push_back(less.moduli.contains(i % less.cycle_size) && more.initial[i]);
  }
  size_t a_mult = 0, b_mult = 0;
  auto a_it = a.moduli.begin(), b_it = b.moduli.begin();
  while (true) {
    if (a_mult + *a_it < b_mult + *b_it) {
      ++a_it;
      if (a_it == a.moduli.end()) {
        a_mult += a.cycle_size;
        if (a_mult == b_mult)
          break;
        a_it = a.moduli.begin();
      }
    } else if (a_mult + *a_it > b_mult + *b_it) {
      ++b_it;
      if (b_it == b.moduli.end()) {
        b_mult += b.cycle_size;
        if (b_mult == a_mult)
          break;
        b_it = b.moduli.begin();
      }
    } else {
      ret.moduli.insert(a_mult + *a_it);

      ++a_it;
      if (a_it == a.moduli.end()) {
        a_mult += a.cycle_size;
        if (a_mult == b_mult)
          break;
        a_it = a.moduli.begin();
      }
      ++b_it;
      if (b_it == b.moduli.end()) {
        b_mult += b.cycle_size;
        if (b_mult == a_mult)
          break;
        b_it = b.moduli.begin();
      }
    }
  }
  ret.cycle_size = a_mult;
  return ret;
}

bool not_end_condition(const vector<string> &v) {
  for (const auto &s : v) {
    if (s[2] != 'Z')
      return true;
  }
  return false;
}

int main() {
  vector<bool> sequence;
  string s, node, left, right;
  map<string, string[2]> m;
  vector<string> initials;
  priority_queue<Cycle> cycles;

  cin >> s;
  for (char c : s) {
    sequence.push_back(c == 'R');
  }

  while (cin >> node >> s >> left >> right) {
    left.erase(0, 1);
    left.erase(3);
    right.erase(3);
    m[node][0] = left;
    m[node][1] = right;
    if (node[2] == 'A') {
      initials.push_back(node);
    }
  }

  for (const auto& initial : initials) {
    cycles.emplace(m, initial, sequence);
  }

  while (cycles.size() > 1) {
    Cycle a = cycles.top();
    cycles.pop();
    Cycle b = cycles.top();
    cycles.pop();
    cycles.push(a + b);
  }

  cout << cycles.top().first() << endl;
  return 0;
}
