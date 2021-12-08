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

#define TIME_LIMIT 5

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

void debug(const filesystem::path &executable, const string extension,
           const string input) {
  sleep(2);
  if (extension == ".cpp") {
    execlp("gdb", "gdb", executable.filename().c_str(), "--cd",
           executable.parent_path().c_str(), "-ex", "b main", "-ex",
           ("r < " + input).c_str(), "-ex", "n", "--tui", "--silent", nullptr);
  } else if (extension == ".rs") {
    execlp("rust-gdb", "rust-gdb", executable.filename().c_str(), "--cd",
           executable.parent_path().c_str(), "-ex", "b main", "-ex",
           ("r < " + input).c_str(), "-ex", "n", "--tui", "--silent", nullptr);
  } else if (extension == ".py") {
    execlp("python3", "python3", "-m", "pdb", executable.c_str(), nullptr);
  } else {
    throw runtime_error("Tried to debug, but don’t know " + extension + ".");
  }
}

string execute(const filesystem::path &executable,
               const string &extension,
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
    alarm(TIME_LIMIT);
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
  try {
    check_pid(pid, "Error on execution");
  } catch(runtime_error &e) {
    cerr << e.what() << endl;
    debug(executable, extension, input.filename().native());
  }
  return out;
}

filesystem::path get_executable(const filesystem::path &code,
                                bool compile = true) {
  if (code.extension() == ".cpp") {
    filesystem::path executable = code.parent_path() / "a.out";
    if (compile) {
      pid_t pid = fork();
      if (pid == 0) {
        execlp("g++", "g++", "-g", "-Wall", "-Werror", code.c_str(),
               "-std=c++20", "-o", executable.c_str(), nullptr);
      }
      check_pid(pid, "Error on C++ compilation");
    }
    return executable;
  } else if (code.extension() == ".rs") {
    filesystem::path executable = code.parent_path() / code.stem();
    if (compile) {
      pid_t pid = fork();
      if (pid == 0) {
        execlp("rustc", "rustc", "-g", code.c_str(), "-o", executable.c_str(),
               nullptr);
      }
      check_pid(pid, "Error on Rust compilation");
    }
    return executable;
  }
  return code;
}

string verify_and_execute(const filesystem::path &code) {
  const string UP = "\x1b[F", GREEN = "\x1b[32m", RESET = "\x1b[0m";
  cout << "On " << code.native() << endl;
  auto executable = get_executable(code);
  cout << UP << "On " << GREEN << code.c_str() << RESET << flush << ":";

  // Verify
  auto sample = code.parent_path() / "sample.txt";
  auto expect =
      code.parent_path() / ("expect_" + code.stem().native() + ".txt");
  if (filesystem::exists(sample) && filesystem::exists(expect)) {
    cout << " __\n";
    string actual = execute(executable, code.extension(), sample);
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
      debug(executable, code.extension(), sample.filename().native());
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
  return execute(executable, code.extension(), input);
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

  map<string, tuple<string, filesystem::path, string>> outputs;
  while (!pq.empty()) {
    const filesystem::path &code = pq.top().second;
    string output = verify_and_execute(pq.top().second);
    cout << output;
    auto it = outputs.find(code.stem());
    if (it == outputs.end()) {
      outputs[code.stem()] =
          make_tuple(output, get_executable(code, false), code.extension());
    } else {
      if (get<0>(it->second) != output) {
        cerr << "Output: " << output << endl;
        cerr << "Previous: " << get<0>(it->second) << endl;
        cerr << "Outputs don’t match, debugging latest changed." << endl;
        debug(get<1>(it->second), get<2>(it->second), "input.txt");
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
    for (const auto &file :
         filesystem::recursive_directory_iterator(day.path())) {
      if (!file.is_regular_file()) {
        continue;
      }
      if (file.path().filename().native()[0] == '.') {
        continue;
      }
      string extension = file.path().extension();
      if (extension == ".cpp" || extension == ".py" || extension == ".rs") {
        pq.push(make_pair(file.last_write_time(),
                          file.path().parent_path().lexically_normal()));
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
