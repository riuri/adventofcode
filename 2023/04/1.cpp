#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
  string last;
  set<int> card;
  int sum = 0, points;
  cin >> last; // Card
  while (cin >> last) { // n:
    points = 1;
    card.clear();
    while (cin >> last && last != "|") {
      card.insert(stoi(last));
    }
    while (cin >> last && last != "Card") {
      if (card.contains(stoi(last)))
        points <<= 1;
    }
    sum += points / 2;
  }
  cout << sum << endl;
  return 0;
}
