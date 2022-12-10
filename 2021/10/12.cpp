#include <iostream>
#include <set>
#include <stack>

using namespace std;

int points(char c) {
  switch (c) {
  case '(':
    return 1;
  case '[':
    return 2;
  case '{':
    return 3;
  case '<':
    return 4;
  case ')':
    return 3;
  case ']':
    return 57;
  case '}':
    return 1197;
  case '>':
    return 25137;
  default:
    return 0;
  }
}
char opening(char c) {
  switch (c) {
  case ')':
    return '(';
  case ']':
    return '[';
  case '}':
    return '{';
  case '>':
    return '<';
  default:
    return '\0';
  }
}

int main() {
  string cur;
  int sum = 0;
  multiset<unsigned long long int> valid_set;
  while (cin >> cur) {
    stack<char> s;
    bool invalid = false;
    for (size_t i = 0; i < cur.size(); ++i) {
      char c = cur[i];
      if (c == '(' || c == '[' || c == '{' || c == '<') {
        s.push(c);
        continue;
      }
      if (s.empty()) {
        sum += points(c);
        invalid = true;
        break;
      }
      char sc = s.top();
      s.pop();
      if (sc != opening(c)) {
        sum += points(c);
        invalid = true;
        break;
      }
    }
    unsigned long long int valid_points = 0;
    if (!invalid) {
      while (!s.empty()) {
        valid_points = valid_points * 5 + points(s.top());
        s.pop();
      }
      valid_set.insert(valid_points);
    }
  }

  auto it = valid_set.cbegin();
  advance(it, valid_set.size() / 2);

  cout << sum << endl;
  cout << *it << endl;
  return 0;
}
