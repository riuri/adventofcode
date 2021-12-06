// Compile with g++ -lstdc++fs
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sys/wait.h>
#include <unistd.h>

#define TIME_LIMIT 15

using namespace std;

void check_pid(pid_t pid, const string &error) {
  int wstatus;
  waitpid(pid, &wstatus, 0);
  if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0) {
    if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGALRM) {
      cerr << "\nTime limit is " << TIME_LIMIT << " seconds.\n";
      throw runtime_error("Time limit exceeded");
    }
    if (!WIFEXITED(wstatus)) {
      cerr << "\nDid not exit normally.\n";
    } else {
      cerr << "\nExit status was " << int(WEXITSTATUS(wstatus)) << ".\n";
    }
    throw runtime_error(error);
  }
}

string execute(const filesystem::path &executable,
               const filesystem::path &input) {
  int fdout[2];
  pipe(fdout);
  pid_t pid = fork();
  if (pid == 0) {
    close(fdout[0]);
    dup2(fdout[1], 1);
    close(fdout[1]);
    int fd = open(input.c_str(), O_RDONLY);
    dup2(fd, 0);
    close(fd);
    alarm(15);
    execl(executable.c_str(), executable.filename().c_str(), nullptr);
  }
  close(fdout[1]);
  int c;
  char buf[4096];
  string out;
  while ((c = read(fdout[0], buf, sizeof(buf))) > 0) {
    out.append(buf, c);
  }
  close(fdout[0]);
  check_pid(pid, "Error on execution");
  return out;
}

filesystem::path compile(const filesystem::path &code) {
  if (code.extension() == ".cpp") {
    filesystem::path executable = code.parent_path() / "a.out";
    pid_t pid = fork();
    if (pid == 0) {
      execlp("g++", "g++", code.c_str(), "-std=c++20", "-o", executable.c_str(),
             nullptr);
    }
    check_pid(pid, "Error on C++ compilation");
    return executable;
  } else if (code.extension() == ".rs") {
    filesystem::path executable = code.parent_path() / code.stem();
    pid_t pid = fork();
    if (pid == 0) {
      execlp("rustc", "rustc", code.c_str(), "-o", executable.c_str(), nullptr);
    }
    check_pid(pid, "Error on Rust compilation");
    return executable;
  }
  return code;
}

string verify_and_execute(const filesystem::path &code) {
  const string UP = "\x1b[F", GREEN = "\x1b[32m", RESET = "\x1b[0m";
  cout << "On " << code.native() << endl;
  auto executable = compile(code);
  cout << UP << "On " << GREEN << code.c_str() << RESET << flush << ":";

  // Verify
  auto sample = code.parent_path() / "sample.txt";
  auto expect =
      code.parent_path() / ("expect_" + code.stem().native() + ".txt");
  if (filesystem::exists(sample) && filesystem::exists(expect)) {
    cout << " __\n";
    string actual = execute(executable, sample);
    ifstream f(expect);
    string expected(istreambuf_iterator<char>(f), {});
    f.close();
    if (expected == actual) {
      cout << UP << "On " << GREEN << code.native() << RESET << ": " << GREEN;
      cout << "OK" << RESET << endl;
    } else {
      cout << endl;
      cerr << "Sample expectation: " << expected << endl;
      cerr << "Actual: " << actual << endl;
      throw runtime_error("Sample expectation failed");
    }
  } else {
    cout << endl;
  }

  // Execute
  auto input = code.parent_path() / "input.txt";
  if (!filesystem::exists(input)) {
    cerr << "It’s time to use the actual input\n";
    throw runtime_error("Missing input.txt");
  }
  return execute(executable, input);
}
void verify_and_execute_day(const filesystem::path &day) {
  priority_queue<pair<filesystem::file_time_type, filesystem::path>> pq;
  for (const auto &file : filesystem::directory_iterator(day)) {
    if (!file.is_regular_file()) {
      continue;
    }
    if (file.path().filename().native()[0] == '.') {
      continue;
    }
    string extension = file.path().extension();
    if (extension == ".cpp" || extension == ".py" || extension == ".rs") {
      pq.push(
          make_pair(file.last_write_time(), file.path().lexically_normal()));
    }
  }

  map<string, string> outputs;
  while (!pq.empty()) {
    const filesystem::path &code = pq.top().second;
    string output = verify_and_execute(pq.top().second);
    cout << output;
    auto it = outputs.find(code.stem());
    if (it == outputs.end()) {
      outputs[code.stem()] = output;
    } else {
      if (it->second != output) {
        cerr << "Output: " << output << endl;
        cerr << "Previous: " << it->second << endl;
        throw runtime_error("Outputs don’t match");
      }
    }
    pq.pop();
  }
}

int main() {
  priority_queue<pair<filesystem::file_time_type, filesystem::path>> pq;
  for (const auto &day : filesystem::directory_iterator(".")) {
    if (!day.is_directory()) {
      continue;
    }
    if (day.path().filename().native()[0] == '.') {
      continue;
    }
    for (const auto &file : filesystem::directory_iterator(day.path())) {
      if (!file.is_regular_file()) {
        continue;
      }
      if (file.path().filename().native()[0] == '.') {
        continue;
      }
      string extension = file.path().extension();
      if (extension == ".cpp" || extension == ".py" || extension == ".rs") {
        pq.push(
            make_pair(file.last_write_time(), day.path().lexically_normal()));
      }
    }
  }

  set<filesystem::path> visited;
  while (!pq.empty()) {
    const filesystem::path &day = pq.top().second;
    if (!visited.count(day)) {
      verify_and_execute_day(pq.top().second);
      visited.insert(day);
    }
    pq.pop();
  }
}
