#include <iostream>
#include <string>

using namespace std;

typedef enum segment { A = 1, B, C, D, E, F, G } Segment;

void find_mapping(Segment *mapping, string one, string four,
                  const int *counts) {
  for (int segment = A; segment <= G; ++segment) {
    switch (counts[segment]) {
    case 4:
      mapping[segment] = E;
      break;
    case 6:
      mapping[segment] = B;
      break;
    case 7:
      // D or G, check 4 (4 segments);
      mapping[segment] = four.find(segment + 0x60) == string::npos ? G : D;
      break;
    case 8:
      // A or C, check 1 (2 segments);
      mapping[segment] = one.find(segment + 0x60) == string::npos ? A : C;
      break;
    case 9:
      mapping[segment] = F;
      break;
    }
  }
}

int find_digit(const Segment *mapping, string digit) {
  bool c = false, d = false, e = false;
  switch (digit.size()) {
  case 2:
    return 1;
  case 3:
    return 7;
  case 4:
    return 4;
  case 5:
    for (size_t i = 0; i < 5; ++i) {
      Segment seg = mapping[digit[i] & 7];
      c |= seg == C;
      e |= seg == E;
    }
    if (c && e) {
      return 2;
    } else if (c) {
      return 3;
    } else {
      return 5;
    }
  case 6:
    for (size_t i = 0; i < 6; ++i) {
      Segment seg = mapping[digit[i] & 7];
      c |= seg == C;
      d |= seg == D;
      e |= seg == E;
    }
    if (!c) {
      return 6;
    } else if (!d) {
      return 0;
    } else if (!e) {
      return 9;
    }
  case 7:
    return 8;
  }
  throw 0;
}

int main() {
  string cur, one, four;
  int sum = 0;
  Segment mapping[8];

  while (true) {
    int counts[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    while (true) {
      if (!(cin >> cur)) {
        cout << sum << endl;
        return 0;
      }
      if (cur.size() == 1) {
        break;
      } else if (cur.size() == 2) {
        one = cur;
      } else if (cur.size() == 4) {
        four = cur;
      }
      for (size_t i = 0; i < cur.size(); ++i) {
        counts[cur[i] & 7]++;
      }
    }

    find_mapping(mapping, one, four, counts);

    int num = 0;
    while (cin.peek() != '\n') {
      cin >> cur;
      num *= 10;
      num += find_digit(mapping, cur);
    }
    sum += num;
  }
}
