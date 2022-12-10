#include <stack>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

void reverse(vector<stack<char>> &state) {
  for (size_t i = 0; i < state.size(); ++i) {
    stack<char> rev;
    while (!state[i].empty()) {
      rev.push(state[i].top());
      state[i].pop();
    }
    state[i] = rev;
  }
}

int main() {
  vector<stack<char>> state;
  char *line = (char*) malloc(100);
  size_t malloc_size = 100;
  ssize_t line_size;
  while (1 < (line_size = getline(&line, &malloc_size, stdin))) {
    if ((ssize_t)state.size() < line_size / 4) {
      state.resize(line_size / 4);
    }
    for (ssize_t i = 0; i < line_size / 4; ++i) {
      char current = line[4*i + 1];
      if (current != ' ') {
        state[i].push(current);
      }
    }
  }
  free(line);
  reverse(state);
  int move, from, to;
  while (EOF != scanf(" move %d from %d to %d\n", &move, &from, &to)) {
    for (int i = 0; i < move; ++i) {
      state[to - 1].push(state[from - 1].top());
      state[from - 1].pop();
    }
  }

  for (size_t i = 0; i < state.size(); ++i) {
    putchar(state[i].top());
  }
  putchar('\n');
  return 0;
}
