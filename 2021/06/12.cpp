#include <array>
#include <iostream>

using namespace std;

class Mat {
public:
  long long int mat[9][9] = {
    {0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  // Matrix multiplication
  Mat operator*(const Mat &o) const {
    Mat m;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        m.mat[i][j] = 0;
        for (int k = 0; k < 9; ++k) {
          m.mat[i][j] += mat[i][k] * o.mat[k][j];
        }
      }
    }
    return m;
  }
  // Matrix power
  Mat operator^(unsigned int n) const {
    if (n == 1) {
      return *this;
    }
    Mat sq = *this ^ (n / 2);
    if (n % 2) {
      return *this * sq * sq;
    } else {
      return sq * sq;
    }
  }
  // Multiplication by vector. We only need the sum of the vector
  long long int operator*(const array<long long int, 9> &o) const {
    long long int sum = 0;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        sum += mat[i][j] * o[j];
      }
    }
    return sum;
  }
};

int main() {
  Mat m;
  array<long long int, 9> begin = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int cur;
  while (cin >> cur) {
    char separator;
    begin[cur]++;
    cin >> separator;
  }

  cout << "After 80 days: " << (m ^ 80) * begin << endl;
  cout << "After 256 days: " << (m ^ 256) * begin << endl;

  return 0;
}
