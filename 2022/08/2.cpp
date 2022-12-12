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
  int *scenic = (int*) malloc(size * sizeof(int));
  int *tmp = (int*) malloc(size * sizeof(int));

  ssize_t inc[4] = {1,    -cols,             -1,              cols};
  ssize_t ini[4] = {0,    (rows - 1) * cols, rows * cols - 1, cols - 1};
  ssize_t big[4] = {cols, 1,                 -cols,           -1};
  ssize_t iii[2] = {cols - 1, rows - 1};
  ssize_t jjj[2] = {rows - 1, cols - 1};
  for (int side = 0; side < 4; ++side) {
    memset(tmp, 0, size * sizeof(int));
    for (ssize_t i = 1; i < iii[side % 2]; ++i) {
      for (ssize_t j = 1; j < jjj[side % 2]; ++j) {
        ssize_t pos = ini[side] + i * big[side] + j * inc[side];
        tmp[pos] = 1;
        for (
          ssize_t cmp = pos - inc[side];
          cmp != ini[side] + i * big[side]
            && treemap[cmp] < treemap[pos];
          cmp -= inc[side],
            tmp[pos]++);
      }
    }

    if (side == 0) {
      memcpy(scenic, tmp, size * sizeof(int));
      continue;
    }

    for (ssize_t i = 0; i < size; ++i) {
      scenic[i] *= tmp[i];
    }
  }
  free(tmp);

  int max_scenic = 0;
  for (ssize_t i = 0; i < size; ++i) {
    if (scenic[i] > max_scenic) max_scenic = scenic[i];
  }
  free(scenic);
  free(treemap);

  printf("%d\n", max_scenic);
  return 0;
}
