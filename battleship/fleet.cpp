#include "fleet.h"

fleet::fleet(bool pOwned)
{
    playerOwned = pOwned;
    if(playerOwned){
        fleetShips.push_back(ship(2,100,550,0));
        fleetShips.push_back(ship(3,200,550,0));
        fleetShips.push_back(ship(3,350,550,0));
        fleetShips.push_back(ship(4,500,550,0));
        fleetShips.push_back(ship(5,700,550,0));
    }
}

void fleet::draw(ALLEGRO_MOUSE_STATE state){
    for (int i = 0; i < fleetShips.size(); i++){
        fleetShips[i].draw(state);
    }
}
