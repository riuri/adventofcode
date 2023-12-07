#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main()
{
  string last;
  set<int> card;
  int sum = 0;
  size_t points;
  vector<int> extras;
  cin >> last; // Card
  while (cin >> last) { // n:
    int count;
    if (extras.empty()) {
      count = 1;
    } else {
      count = extras[0] + 1;
      extras.erase(extras.begin());
    }
    points = 0;
    card.clear();
    while (cin >> last && last != "|") {
      card.insert(stoi(last));
    }
    while (cin >> last && last != "Card") {
      if (card.contains(stoi(last)))
        points++;
    }
    if (extras.size() < points) {
      extras.resize(points, 0);
    }
    for (size_t i = 0; i < points; ++i)
      extras[i] += count;
    sum += count;
  }
  cout << sum << endl;
  return 0;
}
