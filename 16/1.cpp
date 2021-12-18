#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Bit {
public:
  bool bit;
  static uint8_t which_bit;
  static uint8_t which_data;
  static void reset_hexa(istream &in) {
    which_bit = which_data = 0;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  operator bool() const { return bit; }
};
uint8_t Bit::which_bit = 0;
uint8_t Bit::which_data = 0;
istream &operator>>(istream &in, Bit &bit) {
  if (!Bit::which_bit) {
    char c;
    in >> c;
    if (c >= '0' && c <= '9') {
      Bit::which_data = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      Bit::which_data = c - 'A' + 0xA;
    } else if (c >= 'a' && c <= 'f') {
      Bit::which_data = c - 'a' + 0xa;
    }
    Bit::which_bit = 4;
  }
  bit.bit = !!(Bit::which_data & (1 << --Bit::which_bit));
  return in;
}

template <typename Base, uint8_t bits, typename Convert = Base>
class BitSequence {
public:
  Base v = 0;
  constexpr static uint8_t nbits = bits;
  operator Convert() const { return v; }
};
template <typename Base, uint8_t bits, typename Convert>
istream &operator>>(istream &in, BitSequence<Base, bits, Convert> &n) {
  Bit bit;
  n.v = 0;
  for (uint8_t i = 0; i < n.nbits; ++i) {
    in >> bit;
    n.v <<= 1;
    n.v += bit;
  }
  return in;
}

typedef BitSequence<uint8_t, 3, unsigned int> Version;
typedef BitSequence<uint8_t, 3, unsigned int> Type;
typedef BitSequence<uint8_t, 1, unsigned int> LengthType;
typedef BitSequence<uint16_t, 15> Length0Bits;
typedef BitSequence<uint16_t, 11> Length1Packets;
typedef BitSequence<uint8_t, 5, unsigned int> ValueItem;

class Packet {
public:
  Packet() {}
  bool root = true;
  Version version;
  Type type;
  vector<ValueItem> value;
  LengthType length_type;
  Length0Bits length_bits;
  Length1Packets length_packets;
  vector<Packet> sub_packets;

  size_t size() const {
    if (type == 4) {
      return 6 + 5 * value.size();
    } else if (length_type) {
      size_t sum = 18;
      for (const Packet &packet : sub_packets) {
        sum += packet.size();
      }
      return sum;
    }
    return 22 + length_bits;
  }

  unsigned int version_sum() const {
    unsigned int sum = version;
    for (const Packet &packet : sub_packets) {
      sum += packet.version_sum();
    }
    return sum;
  }
};
istream &operator>>(istream &in, Packet &packet) {
  packet.value.clear();
  packet.length_type.v = 0;
  packet.length_bits.v = 0;
  packet.length_packets.v = 0;
  packet.sub_packets.clear();

  cin >> packet.version >> packet.type;
  if (packet.type == 4) {
    ValueItem value;
    do {
      cin >> value;
      packet.value.push_back(value);
    } while (value & 0x10);
  } else {
    cin >> packet.length_type;
    if (packet.length_type) {
      cin >> packet.length_packets;
    } else {
      cin >> packet.length_bits;
    }
    Packet sub_packet;
    sub_packet.root = false;
    for (uint16_t i = 0; packet.length_type ? i < packet.length_packets
                                            : i < packet.length_bits;
         packet.length_type ? ++i : i += sub_packet.size()) {
      cin >> sub_packet;
      packet.sub_packets.push_back(sub_packet);
    }
  }
  if (packet.root) {
    Bit::reset_hexa(in);
  }
  return in;
}

int main() {
  Packet packet;
  while (cin >> packet) {
    cout << packet.version_sum() << endl;
  }
  return 0;
}
