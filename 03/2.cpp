#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// returns the first that’s 1
int bisect(const vector<int> &vec, int start, int finish, int bitwise) {
  if (vec[start] & bitwise) {
    return start;
  }
  while (finish - start > 1) {
    int mid = (start + finish) / 2;
    if (vec[mid] & bitwise) {
      finish = mid;
    } else {
      start = mid;
    }
  }
  return finish;
}

int find(const vector<int> &filter, int bitwise, bool least_common) {
  int start = 0, finish = filter.size();
  while (filter[start] != filter[finish - 1]) {
    bitwise >>= 1;
    bool most_common = filter[(start + finish) / 2] & bitwise;
    if (most_common ^ least_common) {
      start = bisect(filter, start, finish, bitwise);
    } else {
      finish = bisect(filter, start, finish, bitwise);
    }
  }
  return filter[start];
}

int main() {
  multiset<int> report;
  string cur;
  vector<int> filter;

  while (cin >> cur) {
    int curint = 0;
    for (int i = 0; i < cur.size(); ++i) {
      curint <<= 1;
      curint += cur[i] & 1;
    }
    report.insert(curint);
  }
  
  filter.reserve(report.size());
  for (int element : report) {
    for (int i = 0; i < report.count(element); ++i) {
      filter.push_back(element);
    }
  }

  int O2 = find(filter, 1 << cur.size(), false);
  int CO2 = find(filter, 1 << cur.size(), true);

  cout << O2 * CO2 << endl;
  return 0;
}
