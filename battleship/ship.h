#ifndef SHIP_H
#define SHIP_H
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_color.h>

class ship
{
    public:
        /** Default constructor */
        ship(int ss, int x, int y, int deg);
        void draw(ALLEGRO_MOUSE_STATE);
        /** Access ssize
         * \return The current value of ssize
         */
        int Getssize() { return ssize; }
        /** Set ssize
         * \param val New value to set
         */
        void Setssize(int val) { ssize = val; }
        /** Access xPos
         * \return The current value of xPos
         */
        int GetxPos() { return xPos; }
        /** Set xPos
         * \param val New value to set
         */
        void SetxPos(int val) { xPos = val; }
        /** Access yPos
         * \return The current value of yPos
         */
        int GetyPos() { return yPos; }
        /** Set yPos
         * \param val New value to set
         */
        void SetyPos(int val) { yPos = val; }
        /** Access rotation
         * \return The current value of rotation
         */
        int Getrotation() { return rotation; }
        /** Set rotation
         * \param val New value to set
         */
        void Setrotation(int val) { rotation = val; }
    protected:
    private:
        int ssize; //!< Member variable "ssize"
        int xPos; //!< Member variable "xPos"
        int yPos; //!< Member variable "yPos"
        int rotation; //!< Member variable "rotation"
};

#endif // SHIP_H
