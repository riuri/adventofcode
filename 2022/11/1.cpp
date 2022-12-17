#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <array>
#include <queue>
#include <vector>
using namespace std;

class Polynomial {
  array<int, 3> a;
public:
  int apply(int x) const {
    return (x * x * a[2] + x * a[1] + a[0]) / 3;
  }
  istream& input(istream &in) {
    string discard, op, operand;
    // new = old op operand
    in >> discard >> discard >> discard >> op >> operand;
    if (op == "+") {
      a[0] = stoi(operand);
      a[1] = 1;
      a[2] = 0;
    } else if (op == "*") {
      if (operand == "old") {
        a[2] = 1;
        a[1] = a[0] = 0;
      } else {
        a[2] = 0;
        a[1] = stoi(operand);
        a[0] = 0;
      }
    }
    return in;
  }
};

istream& operator>>(istream& in, Polynomial &p) {
  return p.input(in);
}

struct Throw {
  int to_monkey;
  vector<int> items;
};

class Monkey {
  vector<int> items;
  Polynomial polynomial;
  int divisor;
  array<int, 2> destination;
  int count_inspected;
public:
  array<Throw, 2> inspect_all() {
    array<Throw, 2> output;
    output[0].to_monkey = destination[0];
    output[1].to_monkey = destination[1];
    count_inspected += items.size();
    for (int item : items) {
      int new_item = polynomial.apply(item);
      output[!!(new_item % divisor)].items.push_back(new_item);
    }
    items.clear();
    return output;
  }
  void receive(vector<int> inputs) {
    copy(inputs.begin(), inputs.end(), back_inserter(items));
  }
  int inspected() const {
    return count_inspected;
  }
  istream& input(istream& in) {
    string discard;
    int item;
    // Monkey n:
    in >> discard >> discard
    // Starting items:
       >> discard >> discard;
    items.clear();
    do {
      in >> item;
      items.push_back(item);
    } while (in.get() == ',');
    // Operation:
    return
    in >> discard >> polynomial
    // Test: divisible by
       >> discard >> discard >> discard >> divisor
    // If bool: throw to monkey
       >> discard >> discard >> discard >> discard >> discard >> destination[0]
       >> discard >> discard >> discard >> discard >> discard >> destination[1];
  }
};

istream& operator>>(istream& in, Monkey &m) {
  return m.input(in);
}

int main() {
  vector<Monkey> monkeys;
  Monkey tmp;
  while (cin >> tmp) {
    monkeys.push_back(tmp);
  }

  for (int round = 0; round < 20; ++round) {
    for (size_t i = 0; i < monkeys.size(); ++i) {
      for (const Throw& t : monkeys[i].inspect_all()) {
        monkeys[t.to_monkey].receive(t.items);
      }
    }
  }

  priority_queue<int> pq;
  for (const Monkey &m : monkeys) {
    pq.push(m.inspected());
  }
  long business = pq.top();
  pq.pop();
  business *= pq.top();
  cout << business << endl;
  return 0;
}
