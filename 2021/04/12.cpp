#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>

#define SIZE 5
#define INFTY std::numeric_limits<int>::max()

using namespace std;

class Board {
public:
  int matrix[5][5];
  int sum;
  int winning;
  int get_score(const vector<int> &seq) const {
    int score = sum;
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        int order = matrix[i][j];
        // Check if the number is marked
        if (order <= winning) {
          score -= seq[order];
        }
      }
    }
    return score * seq[winning];
  }
  bool operator<(const Board &o) const { return winning < o.winning; }
};

bool read_board(istream &in, Board &b, const unordered_map<int, int> &seq) {
  b.sum = 0;
  b.winning = INFTY;
  for (int i = 0; i < SIZE; ++i) {
    int row_max = 0;
    for (int j = 0; j < SIZE; ++j) {
      int cur;
      if (!(in >> cur)) {
        return false;
      }
      b.sum += cur;
      auto iterator = seq.find(cur);
      b.matrix[i][j] = iterator == seq.end() ? INFTY : iterator->second;
      row_max = max(row_max, b.matrix[i][j]);
    }
    b.winning = min(b.winning, row_max);
  }

  for (int i = 0; i < SIZE; ++i) {
    int col_max = 0;
    for (int j = 0; j < SIZE; ++j) {
      col_max = max(col_max, b.matrix[j][i]);
    }
    b.winning = min(b.winning, col_max);
  }
  return true;
}

int main() {
  unordered_map<int, int> sequence_map;
  vector<int> sequence;
  int draw;
  char separator;
  Board cur, winner, loser;

  do {
    cin >> draw >> separator;
    sequence_map[draw] = sequence_map.size();
    sequence.push_back(draw);
  } while (separator == ',');

  read_board(cin, winner, sequence_map);
  loser = winner;
  while (read_board(cin, cur, sequence_map)) {
    winner = min(winner, cur);
    loser = max(loser, cur);
  }

  cout << "Winner: " << winner.get_score(sequence) << endl;
  cout << "Loser: " << loser.get_score(sequence) << endl;
  return 0;
}
