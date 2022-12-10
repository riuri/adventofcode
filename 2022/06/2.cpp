#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool no_repeat(const vector<int> &counts) {
  for (int count : counts) {
    if (count > 1) {
      return false;
    }
  }
  return true;
}

int main() {
  string input;
  while (cin >> input) {
    vector<int> counts(26);
    for (size_t i = 0; i < input.size(); ++i) {
      counts[input[i] - 'a']++;
      if (i >= 14) {
        counts[input[i - 14] - 'a']--;
      }
      if (i >= 13 && no_repeat(counts)) {
        cout << i + 1 << endl;
        break;
      }
    }
  }
  return 0;
}
