#include <vector>
#include <string>
#include <iostream>

#define priority(x) (long)((x) >= 'a' ? (x) - 'a' : (x) - 'A' + 26)

using namespace std;

int main() {
  long total = 0;
  string elf[3];
  while (cin >> elf[0] >> elf[1] >> elf[2]) {
    long contains = 0;
    for (size_t i = 0; i < elf[0].size(); ++i) {
      contains |= 1L << priority(elf[0][i]);
    }
    long accumulator = contains;
    contains = 0;
    for (size_t i = 0; i < elf[1].size(); ++i) {
      contains |= 1L << priority(elf[1][i]);
    }
    accumulator &= contains;
    for (size_t i = 0; i < elf[2].size(); ++i) {
      long add_1 = priority(elf[2][i]);
      if (accumulator & (1L << add_1)) {
        total += 1 + add_1;
        break;
      }
    }
  }
  cout << total << endl;
  return 0;
}
