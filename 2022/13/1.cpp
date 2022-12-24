#include <stdio.h>
#include <stdlib.h>
#include <vector>

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

int main() {
  int index = 1, sum = 0;
  do {
    Packet left = read_packet(stdin);
    fgetc(stdin);
    Packet right = read_packet(stdin);
    fgetc(stdin);
    
    if (left < right) {
      sum += index;
    }
    index++;
  } while(fgetc(stdin) != EOF);
  printf("%d\n", sum);
  return 0;
}
