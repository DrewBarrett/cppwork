#include "grid.h"

grid::grid(bool iplayerOwned, int ix, int iy)
{
    playerOwned = iplayerOwned;
    x = ix;
    y = iy;
}

void grid::draw(ALLEGRO_MOUSE_STATE state){
    int ssize = squares[0][0].getSize();
    for (int i = 0; i < HEIGHT; i++){
        for(int k = 0; k < WIDTH; k++){
            squares[i][k].draw(k*ssize + x,i*ssize + y,state);
        }
    }
}
