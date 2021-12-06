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
  array<long long int, 9> operator*(const array<long long int, 9> &o) const {
    array<long long int, 9> v = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        v[i] += mat[i][j] * o[j];
      }
    }
    return v;
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

  array<long long int, 9> end80 = (m ^ 80) * begin;
  array<long long int, 9> end256 = (m ^ 256) * begin;
  long long int sum80 = 0;
  long long int sum256 = 0;
  for (int i = 0; i < 9; ++i) {
    sum80 += end80[i];
    sum256 += end256[i];
  }
  cout << "After 80 days: " << sum80 << endl;
  cout << "After 256 days: " << sum256 << endl;

  return 0;
}
