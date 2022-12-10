#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
  map<string, long> sizes;
  vector<string> paths = { "" };
  string next;
  cin >> next; // $
  while (cin >> next) {
    if (next == "cd") {
      string dir;
      cin >> dir;
      if (dir == "/") {
        paths.resize(1);
      } else if (dir == "..") {
        paths.resize(paths.size() - 1);
      } else {
        paths.push_back(paths[paths.size() - 1] + '/' + dir);
      }
      if (paths.size() == 0) {
        paths.push_back("");
      }
      cin >> next;
    } else if (next == "ls") {
      string size_or_prompt;
      while (cin >> size_or_prompt) {
        string filename;
        if (size_or_prompt == "$") {
          break;
        } else if (size_or_prompt == "dir") {
          cin >> filename;
          continue;
        }
        long size = stol(size_or_prompt);
        for (const string &path : paths) {
          sizes[path] += size;
        }
        cin >> filename;
      }
    } else {
      return 1;
    }
  }

  long total = 0;
  for (const auto& [path, size] : sizes) {
    if (size <= 100000) {
      total += size;
    }
  }
  cout << total << endl;
  return 0;
}
