#ifndef GRID_H
#define GRID_H
#define WIDTH 10
#define HEIGHT 10
#include "gridSquare.h"
#include <allegro5/allegro.h>

class grid
{
    public:
        /** Default constructor */
        grid(bool, int, int);
        /** Access playerOwned
         * \return The current value of playerOwned
         */
        bool GetplayerOwned() { return playerOwned; }
        /** Set playerOwned
         * \param val New value to set
         */
        void SetplayerOwned(bool val) { playerOwned = val; }
        void draw(ALLEGRO_MOUSE_STATE);
        /** Access squares[10][10]
         * \return The current value of squares[10][10]
         */
        //gridSquare Getsquares() { return squares; }
        /** Set squares[10][10]
         * \param val New value to set
         */
        //void Setsquares(gridSquare val) { squares = val; }
    protected:
    private:
        bool playerOwned; //!< Member variable "playerOwned"
        gridSquare squares[HEIGHT][WIDTH]; //!< Member variable "squares[10][10]"
        int x;
        int y;
};

#endif // GRID_H
