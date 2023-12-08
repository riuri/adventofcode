#include <iostream>
#include <set>
#include <string>
#include <compare>
#include <queue>

using namespace std;

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
        ret.comp += c - '1';
    }
  }
  return ret;
}

Cards classify_cards(const Cards &cards) {
  Cards ret;
  ret.comp = 0;
  multiset<char> counts;
  set<char> s;
  int jokers = 0;
  for (size_t i = 0; i < 5; ++i) {
    if (cards.cards[i] == 0) {
      jokers++;
    } else {
      s.insert(cards.cards[i]);
      counts.insert(cards.cards[i]);
    }
  }
  for (auto c : s) {
    ret.cards[counts.count(c)-1]++;
  }
  for (int i = 4; i >= 0; --i) {
    if (ret.cards[i]) {
      ret.cards[i]--;
      ret.cards[i + jokers]++;
      break;
    }
  }
  if (ret.comp == 0) {
    ret.cards[4] = 1;
  }
  return ret;
}

class Hand {
  Cards type;
  Cards cards;
public:
  long bidding;
  Hand(const string &s, long bid) : bidding(bid) {
    cards = from_string(s);
    type = classify_cards(cards);
  }

  strong_ordering operator<=>(const Hand &other) const {
    if (type.comp > other.type.comp) {
      return strong_ordering::greater;
    } else if (type.comp < other.type.comp) {
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
