#include <iostream>
#include <vector>
#include <string>
#include <optional>

using namespace std;

struct number_t {
  size_t value, start, length;
};

struct line_t {
  vector<struct number_t> numbers;
  vector<bool> symbols;
};

struct line_t parse_line(const string &s) {
  struct line_t ret;
  optional<struct number_t> current_number;
  ret.symbols.push_back(false);
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      if (current_number) {
        current_number->value *= 10;
        current_number->value += s[i] - '0';
        current_number->length++;
      } else {
        current_number.emplace();
        current_number->value = s[i] - '0';
        current_number->start = i + 1;
        current_number->length = 1;
      }
      ret.symbols.push_back(false);
    } else {
      if (current_number) {
        ret.numbers.push_back(*current_number);
        current_number = {};
      }
      ret.symbols.push_back(s[i] != '.');
    }
  }
  ret.symbols.push_back(false);
  if (current_number)
    ret.numbers.push_back(*current_number);
  return ret;
}

bool is_part_number(const struct line_t &line, const struct number_t &number, const vector<const struct line_t*> &other_lines) {
  if (line.symbols[number.start - 1] || line.symbols[number.start + number.length])
    return true;
  for (const struct line_t* other_line : other_lines) {
    for (size_t i = number.start - 1; i <= number.start + number.length; ++i) {
      if (other_line->symbols[i])
        return true;
    }
  }
  return false;
}

size_t sum_part_numbers_per_line(const struct line_t &line, const vector<const struct line_t*> other_lines) {
  size_t sum = 0;
  for (const struct number_t &number : line.numbers) {
    if (is_part_number(line, number, other_lines))
      sum += number.value;
  }
  return sum;
}

size_t sum_part_numbers(const vector<struct line_t> &lines) {
  size_t sum = 0;
  for (size_t i = 0; i < lines.size(); ++i) {
    vector<const struct line_t*> others;
    if (i > 0) others.push_back(&lines[i - 1]);
    if (i < lines.size() - 1) others.push_back(&lines[i + 1]);
    sum += sum_part_numbers_per_line(lines[i], others);
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
  cout << sum_part_numbers(lines) << endl;
  return 0;
}
