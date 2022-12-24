#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

enum type_t { List, Integer };
class Packet {
private:
  enum type_t type = List;
  vector<Packet> list;
  int integer;
public:
  Packet() {}
  Packet(int i) : type(Integer), integer(i) {}
  Packet& operator=(int value) {
    if (list.size() > 0) {
      exit(1);
    }
    type = Integer;
    integer = value;
    return *this;
  }
  Packet& operator<<(Packet &&other) {
    if (type == Integer) {
      exit(2);
    }
    type = List;
    list.push_back(std::move(other));
    return *this;
  }

  strong_ordering operator<=>(const Packet& right) const {
    if (type == Integer && right.type == Integer) {
      return integer <=> right.integer;
    }
    if (type == List && right.type == List) {
      for (size_t i = 0; i < list.size() && i < right.list.size(); ++i) {
        strong_ordering cmp = list[i] <=> right.list[i];
        if (cmp != strong_ordering::equal) {
          return cmp;
        }
      }
      return list.size() <=> right.list.size();
    }
    if (type == List && right.type == Integer) {
      Packet new_right, contained(right.integer);
      new_right << std::move(contained);
      return operator<=>(new_right);
    }
    if (type == Integer && right.type == List) {
      Packet new_left, contained(integer);
      new_left << std::move(contained);
      return new_left <=> right;
    }
    return strong_ordering::equivalent;
  }
  bool operator!=(const Packet &right) const {
    return (*this <=> right) != strong_ordering::equal;
  }
};

Packet read_packet(FILE *stream) {
  Packet output;
  int start = fgetc(stream);
  if (start == '[') {
    int separator = fgetc(stream);
    if (separator != ']') {
      ungetc(separator, stream);
      do {
        output << read_packet(stream);
        separator = fgetc(stream);
      } while (separator == ',');
    }
  } else {
    ungetc(start, stream);
    int value;
    fscanf(stream, "%d", &value);
    output = value;
  }
  return output;
}

Packet divider(int i) {
  Packet inside(i);
  Packet middle, outside;
  middle << std::move(inside);
  outside << std::move(middle);
  return outside;
}

int main() {
  priority_queue<Packet, vector<Packet>, greater<Packet>> pq;
  do {
    Packet tmp = read_packet(stdin);
    int eol;
    do {
      eol = fgetc(stdin);
    } while (eol == '\n');
    if (eol != EOF) {
      ungetc(eol, stdin);
    }
    pq.push(tmp);
  } while(!feof(stdin));

  Packet divider2 = divider(2), divider6 = divider(6);
  pq.push(divider2);
  pq.push(divider6);
  int index = 1;
  while (!pq.empty() && pq.top() != divider2) {
    pq.pop();
    ++index;
  }
  int index2 = index;
  while (!pq.empty() && pq.top() != divider6) {
    pq.pop();
    ++index;
  }
  printf("%d\n", index2 * index);
  return 0;
}
