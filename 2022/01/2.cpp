#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

int main()
{
  long cals = 0;
  priority_queue<long> maxcals;
  char *buf = (char*) malloc(100);
  size_t bufsize = 100;
  while (0 < getline(&buf, &bufsize, stdin)) {
    if (buf[0] < '0' || buf[0] > '9') {
      maxcals.push(cals);
      cals = 0;
      continue;
    }
    cals += atol(buf);
  }
  maxcals.push(cals);
  free(buf);
  long total = 0;
  for (int i = 0; i < 3; ++i) {
    total += maxcals.top();
    maxcals.pop();
  }
  printf("%ld\n", total);
  return 0;
}
