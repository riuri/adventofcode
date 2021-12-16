#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int dfs(const map<string, set<string>> &graph, const string &node,
        set<string> &visited, bool twice) {
  int count = 0;
  for (const string &next : graph.at(node)) {
    if (next == "end") {
      count++;
    } else if (isupper(next[0])) {
      count += dfs(graph, next, visited, twice);
    } else if (visited.contains(next)) {
      if (!twice) {
        count += dfs(graph, next, visited, true);
      }
    } else {
      visited.insert(next);
      count += dfs(graph, next, visited, twice);
      visited.erase(next);
    }
  }
  return count;
}

int main() {
  string cur;
  map<string, set<string>> graph;
  while (true) {
    bool eof = !(cin >> cur);
    size_t separator = cur.find('-');
    if (separator == 0 || separator >= cur.size() - 1 || eof) {
      string start = "start";
      set<string> s = {"start"};
      cout << dfs(graph, start, s, false) << endl;
      graph.clear();
      if (eof) {
        break;
      }
    } else {
      string node1(cur, 0, separator), node2(cur, separator + 1);
      if (node2 != "start" && node1 != "end") {
        graph[node1].insert(node2);
      }
      if (node2 != "end" && node1 != "start") {
        graph[node2].insert(node1);
      }
    }
  }
  return 0;
}
