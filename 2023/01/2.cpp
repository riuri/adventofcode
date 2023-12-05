#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

optional<int> digit(string_view s)
{
  const vector<string> names = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
  };
  if (s[0] >= '0' && s[0] <= '9')
    return s[0] - '0';
  for (size_t i = 0; i < names.size(); ++i) {
    if (s.starts_with(names[i]))
      return i;
  }
  return {};
}

int main()
{
  int N = 0;
  string line;
  while (cin >> line) {
    for (size_t i = 0; i < line.size(); ++i) {
      auto result = digit(string_view(&line[i], line.size() - i));
      if (result) {
        N += *result * 10;
        break;
      }
    }
    for (int i = line.size() - 1; i >= 0; --i) {
      auto result = digit(string_view(&line[i], line.size() - i));
      if (result) {
        N += *result;
        break;
      }
    }
  }
  cout << N << endl;
  return 0;
}
