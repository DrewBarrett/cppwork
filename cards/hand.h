#ifndef HAND_H
#define HAND_H
#include <string>
#include "card.h"

using namespace std;

class Hand
{
      public: 
              Hand();
              Hand(int s);
              Hand(int s, Card myH[]);
              void dealCard(int loc, Card c);
              int size();
              string toString();
              
      private:
              int handSize;
              Card *myHand;
      
};
#endif
