#include <iostream>
#include <string>

using namespace std;

int main()
{
  string ignore, colour;
  int game, sum = 0;
  while (cin >> ignore >> game >> ignore) {
    int count;
    bool game_possible = true;
    do {
      do {
        cin >> count >> colour;
        if ((colour.starts_with("red") && count > 12)
          || (colour.starts_with("green") && count > 13)
          || (colour.starts_with("blue") && count > 14))
          game_possible = false;
      } while(colour[colour.size() - 1] == ',');
    } while (colour[colour.size() - 1] == ';');
    if (game_possible)
      sum += game;
  }
  cout << sum << endl;
  return 0;
}
