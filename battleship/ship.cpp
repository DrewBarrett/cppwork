#include "ship.h"

ship::ship(int ss, int x, int y, int deg)
{
    ssize = ss;
    xPos = x;
    yPos = y;
    rotation = deg;
}

void ship::draw(){
    al_draw_filled_rectangle(xPos,yPos,xPos + (35 * ssize), yPos + 35, al_color_name("gray"));
}
