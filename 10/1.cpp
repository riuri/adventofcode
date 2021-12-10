#include <iostream>
#include <stack>

using namespace std;

int points(char c) {
  switch (c) {
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
  while (cin >> cur) {
    stack<char> s;
    for (size_t i = 0; i < cur.size(); ++i) {
      char c = cur[i];
      if (c == '(' || c == '[' || c == '{' || c == '<') {
        s.push(c);
        continue;
      }
      if (s.empty()) {
        sum += points(c);
        break;
      }
      char sc = s.top();
      s.pop();
      if (sc != opening(c)) {
        sum += points(c);
        break;
      }
    }
  }

  cout << sum << endl;
  return 0;
}
