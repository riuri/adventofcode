#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

int main() {
  string s;
  vector<int> time;
  vector<int> distance;

  cin >> s;
  while (cin >> s && isdigit(s[0])) {
    time.push_back(stoi(s));
  }
  while (cin >> s && isdigit(s[0])) {
    distance.push_back(stoi(s));
  }

  int mult = 1;
  for (size_t i = 0; i < time.size(); ++i) {
    int delta = time[i] * time[i] - 4 * distance[i];
    if (delta <= 0) {
      mult = 0;
      break;
    }
    mult *= 2 * ceil((sqrt(delta) - time[i] % 2) / 2) + time[i] % 2 - 1;
  }

  cout << mult << endl;

  return 0;
}
