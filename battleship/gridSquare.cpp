#include "gridSquare.h"
#include <iostream>

gridSquare::gridSquare()
{
    hit = false;
    miss = false;
    width = 35;
    color = al_color_name("white");
}

void gridSquare::draw(int x, int y, ALLEGRO_MOUSE_STATE state){
    if(state.x > x && state.x < x + width && state.y > y && state.y < y + width){
        color = al_color_name("cyan");
    }else{
        color = al_color_name("white");
    }
    al_draw_rectangle(x, y, x + width, y + width, color, 1);
    //std::cout << x << " " << y << " " << x+width << " " << y+height << std::endl;
    //al_draw_rectangle(100, 100, 200, 200, al_color_name("white"), 1);
}
