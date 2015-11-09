#include "hand.h"
              
Hand::Hand()
{
     handSize = 5;
     myHand = new Card[handSize];
     for (int i = 0; i < handSize; i++)
     {
         Card c;
         myHand[i] = c;
     }
     
}

Hand::Hand(int s)
{
     handSize = s;   
     myHand = new Card[handSize];           
     for (int i = 0; i < handSize; i++)
     {
         Card c;
         myHand[i] = c;
     }
}
Hand::Hand(int s, Card myH[])
{
     handSize = s;
     myHand = new Card[handSize];
     for (int i = 0; i < handSize; i++)
     {
         myHand[i] = myH[i];
     }
}

int Hand::size()
{
    return handSize;
}

void Hand::dealCard(int loc, Card c)
{
     if (loc < handSize)
          myHand[loc] = c;
}

string Hand::toString()
{
       string s = "";
       for (int i = 0; i < handSize; i++)
       {
           s = s + myHand[i].toString()+ "\t";
       }
       s+= "\n";
       
       return s;
}
