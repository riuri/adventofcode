#include <stdio.h>
#include <stdlib.h>

int main()
{
  long cals = 0, maxcals = 0;
  char *buf = (char*) malloc(100);
  size_t bufsize = 100;
  while (0 < getline(&buf, &bufsize, stdin)) {
    if (buf[0] < '0' || buf[0] > '9') {
      if (cals > maxcals) {
        maxcals = cals;
      }
      cals = 0;
      continue;
    }
    cals += atol(buf);
  }
  if (cals > maxcals) {
    maxcals = cals;
  }
  free(buf);
  printf("%ld\n", maxcals);
  return 0;
}
