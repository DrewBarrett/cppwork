
#include "card.h"

Card::Card()
{
     mySuit = ' ';
     myRank = " ";
     myValue = 0;
     img = al_load_bitmap("b1fv.bmp");
	 backimg = img;
}
Card::Card(char suit, string rank, int value, string imgFile)
{
    mySuit = suit;
    myRank = rank;
    myValue = value;
    myBitmapDir = imgFile;
    img = al_load_bitmap(imgFile.c_str());
    backimg = al_load_bitmap("b1fv.bmp");
    flipped = false;
    inDeck = true;
}

char Card::getSuit()
{
     return mySuit;
}

string Card::getRank()
{
     return myRank;
}

int Card::getValue()
{
    return myValue;
}
int Card::flip()
{
    flipped = !flipped;
	return 0;
}
bool Card::isFlipped()
{
    return flipped;
}
int Card::leaveDeck()
{
    inDeck = false;
	return 0;
}
bool Card::isInDeck()
{
    return inDeck;
}
ALLEGRO_BITMAP *Card::getImg()
{
    if(flipped){
        return img;
    }else{
        return backimg;
    }
}
string Card::getFileDir()
{
 	   return myBitmapDir;
}
string Card::toString()
{
       string s = getRank();
       if (mySuit == 'c') s = s + char(5);
       else if (mySuit == 'd') s = s + char(4);
       else if (mySuit == 'h') s = s + char(3);
       else if (mySuit == 's') s = s + char(6);
       else s = "invalid suit";
       return s;
}


