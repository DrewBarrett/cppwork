#ifndef FLEET_H
#define FLEET_H
#include <vector>
#include "ship.h"

class fleet
{
    public:
        /** Default constructor */
        fleet(bool playerOwned);
        void draw(ALLEGRO_MOUSE_STATE);
        /** Default destructor */
        /** Access fleet
         * \return The current value of fleet
         */
        //std::vector<ship> Getfleet() { return fleet; }
        /** Set fleet
         * \param val New value to set
         */
       // void Setfleet(std::vector<ship> val) { fleet = val; }
    protected:
    private:
        std::vector<ship> fleetShips; //!< Member variable "fleet"
        bool playerOwned;
};

#endif // FLEET_H
