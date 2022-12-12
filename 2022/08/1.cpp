#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *line = (char*) malloc(100);
  char *treemap = NULL;
  size_t n = 100;
  ssize_t size;
  ssize_t rows = 0, cols = 0;
  while (1 < (size = getline(&line, &n, stdin))) {
    if (cols == 0) {
      cols = size - 1;
    }
    rows++;
    treemap = (char*) realloc(treemap, rows * cols);
    memcpy(treemap + cols * (rows - 1), line, cols);
  }
  free(line);

  size = rows * cols;
  char *minheight = (char*) malloc(size);
  memset(minheight, '9', size);
  char *tmp = (char*) malloc(size);

  ssize_t inc[4] = {1,    -cols,             -1,              cols};
  ssize_t ini[4] = {0,    (rows - 1) * cols, rows * cols - 1, cols - 1};
  ssize_t big[4] = {cols, 1,                 -cols,           -1};
  ssize_t iii[2] = {cols - 1, rows - 1};
  ssize_t jjj[2] = {rows - 2, cols - 2};
  for (int side = 0; side < 4; ++side) {
    memset(tmp, '/', size);
    for (ssize_t i = 1; i < iii[side % 2]; ++i) {
      for (ssize_t j = 0; j < jjj[side % 2]; ++j) {
        ssize_t pos = ini[side] + i * big[side] + j * inc[side];
        tmp[pos + inc[side]] = tmp[pos] > treemap[pos] ? tmp[pos] : treemap[pos];
      }
    }

    for (ssize_t i = 0; i < size; ++i) {
      if (minheight[i] > tmp[i]) {
        minheight[i] = tmp[i];
      }
    }
  }
  free(tmp);

  long total = 0;
  for (ssize_t i = 0; i < size; ++i) {
    if (treemap[i] > minheight[i]) total++;
  }
  free(minheight);
  free(treemap);

  printf("%ld\n", total);
  return 0;
}
