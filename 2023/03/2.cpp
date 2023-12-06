#include <iostream>
#include <vector>
#include <string>
#include <optional>

using namespace std;

struct number_t {
  size_t value, start, length;
};

struct line_t {
  vector<struct number_t*> numbers;
  vector<size_t> gears;
};

struct line_t parse_line(const string &s) {
  struct line_t ret;
  ret.numbers.push_back(nullptr);
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      if (ret.numbers.back()) {
        ret.numbers.push_back(ret.numbers.back());
        ret.numbers.back()->value *= 10;
        ret.numbers.back()->value += s[i] - '0';
        ret.numbers.back()->length++;
      } else {
        ret.numbers.push_back(new number_t());
        ret.numbers.back()->value = s[i] - '0';
        ret.numbers.back()->start = i + 1;
        ret.numbers.back()->length = 1;
      }
    } else {
      ret.numbers.push_back(nullptr);
      if (s[i] == '*')
        ret.gears.push_back(i + 1);
    }
  }
  ret.numbers.push_back(nullptr);
  return ret;
}

size_t is_gear(const vector<line_t> &lines, size_t line_position, size_t asterisk_position) {
  const struct number_t *first = nullptr;
  const struct number_t *second = nullptr;
  for (size_t i = line_position == 0 ? 0 : line_position - 1;
    i <= (line_position == lines.size() - 1 ? lines.size() - 1 : line_position + 1);
    ++i) {
    for (size_t j = asterisk_position - 1; j <= asterisk_position + 1; ++j) {
      if (lines[i].numbers[j] == nullptr)
        continue;
      if (first == nullptr) {
        first = lines[i].numbers[j];
        continue;
      }
      if (first == lines[i].numbers[j])
        continue;
      if (second == nullptr) {
        second = lines[i].numbers[j];
        continue;
      }
      if (second != lines[i].numbers[j])
        return 0;
    }
  }
  if (first && second) {
    return first->value * second->value;
  }
  return 0;
}

size_t sum_gear_numbers(const vector<struct line_t> &lines) {
  size_t sum = 0;
  for (size_t i = 0; i < lines.size(); ++i) {
    for (size_t j : lines[i].gears) {
      sum += is_gear(lines, i, j);
    }
  }
  return sum;
}

int main()
{
  vector<struct line_t> lines;
  string s;
  while (cin >> s) {
    lines.push_back(parse_line(s));
  }
  cout << sum_gear_numbers(lines) << endl;
  return 0;
}
