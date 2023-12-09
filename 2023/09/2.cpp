#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  long tmp;
  long sum = 0;
  vector<long> line;
  while (cin >> tmp) {
    line.push_back(tmp);
    if (cin.peek() == '\n') {
      // Lagrange polynomial interpolation but I only care about coefficient 0
      double coef0 = 0;
      for (size_t i = 0; i < line.size(); ++i) {
        double num = line[i];
        double den = 1;
        for (size_t j = 0; j < line.size(); ++j) {
          if (i == j) continue;
          num *= -(double)j - 1;
          den *= (double)i - (double)j;
        }
        coef0 += num / den;
      }
      line.clear();
      sum += (long)round(coef0);
    }
  }
  cout << sum << endl;
  return 0;
}
