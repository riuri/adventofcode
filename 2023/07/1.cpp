#include <iostream>
#include <set>
#include <string>
#include <compare>
#include <queue>

using namespace std;

typedef enum {
  high_card,
  one_pair,
  two_pair,
  three,
  full_house,
  four,
  five
} Type;

typedef union {
  long comp;
  char cards[5];
} Cards;

Cards from_string(const string &s) {
  Cards ret;
  ret.comp = 0;
  for (char c : s) {
    ret.comp <<= 8;
    switch (c) {
      case 'T':
        ret.comp += 10;
        break;
      case 'J':
        ret.comp += 11;
        break;
      case 'Q':
        ret.comp += 12;
        break;
      case 'K':
        ret.comp += 13;
        break;
      case 'A':
        ret.comp += 14;
        break;
      default:
        ret.comp += c - '2';
    }
  }
  return ret;
}

Type classify_cards(const Cards &cards) {
  multiset<char> s1;
  set<char> s0;
  for (size_t i = 0; i < 5; ++i) {
    s0.insert(cards.cards[i]);
    s1.insert(cards.cards[i]);
  }
  multiset<size_t> s2;
  for (auto c : s0) {
    s2.insert(s1.count(c));
  }
  if (s2.count(5))
    return five;
  else if (s2.count(4))
    return four;
  else if (s2.count(3)) {
    if (s2.count(2))
      return full_house;
    return three;
  } else if (s2.count(2) == 2)
    return two_pair;
  else if (s2.count(2) == 1)
    return one_pair;
  return high_card;
}

class Hand {
  Type type;
  Cards cards;
public:
  long bidding;
  Hand(const string &s, long bid) : bidding(bid) {
    cards = from_string(s);
    type = classify_cards(cards);
  }

  strong_ordering operator<=>(const Hand &other) const {
    if (type > other.type) {
      return strong_ordering::greater;
    } else if (type < other.type) {
      return strong_ordering::less;
    }
    return cards.comp <=> other.cards.comp;
  }
};

int main() {
  string cards;
  long bidding;
  priority_queue<Hand> hands;
  while (cin >> cards >> bidding) {
    hands.emplace(cards, bidding);
  }

  long winnings = 0;
  while (!hands.empty()) {
    winnings += hands.top().bidding * hands.size();
    hands.pop();
  }

  cout << winnings << endl;
  return 0;
}
