#include <iostream>
#include <string>

using namespace std;

int main()
{
  string ignore, colour;
  int game, sum = 0;
  while (cin >> ignore >> game >> ignore) {
    int r = 0, g = 0, b = 0, count;
    do {
      cin >> count >> colour;
      if (colour.starts_with("red"))
        r = max(r, count);
      else if (colour.starts_with("green"))
        g = max(g, count);
      else if (colour.starts_with("blue"))
        b = max(b, count);
    } while (colour[colour.size() - 1] == ';' || colour[colour.size() - 1] == ',');
    sum += r * g * b;
  }
  cout << sum << endl;
  return 0;
}
