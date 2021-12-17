#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef pair<int, int> Location;

bool valid(Location l, int size) {
  return l.first >= 0 && l.second >= 0 && l.first < size && l.second < size;
}

int astar(Location l, int size) { return 2 * size - l.first - l.second - 2; }

Location neighbour(Location l, int i) {
  int v[] = {1, 0, -1, 0};
  return {l.first + v[i], l.second + v[(i + 3) % 4]};
}

typedef tuple<int, int, Location> GraphState;

int main() {
  vector<vector<int>> risk;
  string cur;

  while (cin >> cur) {
    vector<int> row;
    for (size_t i = 0; i < cur.size(); ++i) {
      row.push_back(cur[i] - '0');
    }
    risk.push_back(row);
  }

  Location end(risk.size() - 1, risk.size() - 1);
  priority_queue<GraphState, vector<GraphState>, greater<GraphState>> pq;
  set<Location> visited;
  pq.emplace(risk.size() * 2 - 2, 0, Location{0, 0});
  while (!pq.empty()) {
    auto [_, cost, cur] = pq.top();
    pq.pop();
    if (visited.contains(cur)) {
      continue;
    }
    visited.insert(cur);
    if (cur == end) {
      cout << cost << endl;
      return 0;
    }
    for (int i = 0; i < 4; ++i) {
      Location neigh = neighbour(cur, i);
      if (!valid(neigh, risk.size())) {
        continue;
      }
      if (visited.contains(neigh)) {
        continue;
      }
      int next_cost = cost + risk[neigh.first][neigh.second];
      pq.emplace(astar(neigh, risk.size()) + next_cost, next_cost, neigh);
    }
  }
  return 1;
}
