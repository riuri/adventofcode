#include <vector>
#include <string>
#include <iostream>

#define priority(x) ((x) >= 'a' ? (x) - 'a' + 1 : (x) - 'A' + 27)

using namespace std;

int main() {
  long total = 0;
  string rucksack;
  while (cin >> rucksack) {
    size_t compartment = rucksack.size() / 2;
    vector<bool> contains(52);
    for (size_t i = 0; i < compartment; ++i) {
      contains[priority(rucksack[i])] = true;
    }
    for (size_t i = compartment; i <= rucksack.size(); ++i) {
      int add = priority(rucksack[i]);
      if (contains[add]) {
        total += add;
        break;
      }
    }
  }
  cout << total << endl;
  return 0;
}
