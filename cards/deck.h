#ifndef DECK_H
#define DECK_H

#include <vector>
#include <ctime>
#include <algorithm>
#include <string.h>
#include "card.h"


using namespace std;

class Deck
{
      public:
              Deck();
              Card deal();  //deals 1 card at a time
              int size();
              void clear();
              void insert(Card);
              bool empty();
              string toString();
              void shuffleDeck();  // shuffles all the cards in the deck

      private:
              vector<Card> myDeck;
};
#endif
