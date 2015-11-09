#ifndef CARD_H
#define CARD_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_color.h>
#include <cstdlib>
#include <conio.h>
#include <string>

using namespace std;

class Card
{
      public:
              Card();
              Card(char suit, string rank, int value, string imgFile);
              char getSuit();
              string getRank();
              int getValue();
              string toString();
              ALLEGRO_BITMAP *getImg();
              string getFileDir();

      private:
              char mySuit;
              string myRank;
              int myValue;
              string myBitmapDir;
              ALLEGRO_BITMAP *img;

};
#endif
