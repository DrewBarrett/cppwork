
#include "deck.h"

Deck::Deck()
{
     //first sead the time of the deck
     srand(time(0));
     char s[] = {'c', 'd', 'h', 's'};
     string r[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack",
                     "Queen", "King"};
     string img_src = "";
     int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
     for (int i = 0; i < 4; i++)
     {
	  	 img_src = "";
         for (int j = 0; j < 13; j++)
         {
		  	 img_src = "";
             img_src.insert(0, 1, s[i]);
             if (j > 0)
             	img_src.insert(1, 1, r[j][0]);
     	     else
     	     	 img_src.insert(1, 1, '1');

             if (j == 9)
                  img_src.insert(2, 1, '0' );

             img_src = img_src + ".bmp";

             Card c(s[i], r[j], v[j], img_src);
             myDeck.push_back(c);
         }
     }
}
Card Deck::deal()  //deals 1 card at a time
{
 	 if (myDeck.size() > 0)
 	 {
	     Card c = myDeck[myDeck.size() - 1];
	     myDeck.pop_back();
	     return c;
	 }
	 Card c;
	 return c;
 }

int Deck::size()
{
    return myDeck.size();
}
void Deck::clear()
{
     myDeck.clear();
 }
void Deck::insert(Card c){
    if(c.isFlipped()){
        c.flip();
    }
    myDeck.insert(myDeck.begin(), c);
}
bool Deck::empty()
{
     return myDeck.empty();
}
string Deck::toString()
{
       string s = "";
       for (int i = 0; i < size(); i++)
       {
           s = s + myDeck[i].toString() + "  ";
           if ((i+1) % 13 == 0) s = s + "\n";
       }
       return s;
}
void Deck::shuffleDeck()  // shuffles all the cards in the deck
{
     random_shuffle(myDeck.begin(), myDeck.end());
}
