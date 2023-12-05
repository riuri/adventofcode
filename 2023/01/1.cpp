#include <iostream>
#include <string>

using namespace std;

int main()
{
  int N = 0;
  string line;
  while (cin >> line) {
    for (size_t i = 0; i < line.size(); ++i) {
      if (line[i] >= '0' && line[i] <= '9') {
        N += (line[i] - '0') * 10;
        break;
      }
    }
    for (int i = line.size() - 1; i >= 0; --i) {
      if (line[i] >= '0' && line[i] <= '9') {
        N += line[i] - '0';
        break;
      }
    }
  }
  cout << N << endl;
  return 0;
}
