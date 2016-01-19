#include "ship.h"

ship::ship(int ss, int x, int y, int deg)
{
    ssize = ss;
    xPos = x;
    yPos = y;
    rotation = deg;
}

void ship::draw(ALLEGRO_MOUSE_STATE state){
    al_draw_filled_rectangle(xPos,yPos,xPos + (35 * ssize), yPos + 35, al_color_name("gray"));
    if(state.x > xPos && state.x < xPos + (35* ssize) && state.y > yPos && state.y < yPos + 35){
        al_draw_rectangle(xPos,yPos,xPos + (35 * ssize), yPos + 35, al_color_name("cyan"), 1);
    }
}
