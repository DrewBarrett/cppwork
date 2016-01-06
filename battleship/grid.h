#ifndef GRID_H
#define GRID_H
#include "gridSquare.h"

class grid
{
    public:
        /** Default constructor */
        grid(bool playerOwned);
        /** Access playerOwned
         * \return The current value of playerOwned
         */
        bool GetplayerOwned() { return playerOwned; }
        /** Set playerOwned
         * \param val New value to set
         */
        void SetplayerOwned(bool val) { playerOwned = val; }
        void draw();
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
        gridSquare squares[10][10]; //!< Member variable "squares[10][10]"
};

#endif // GRID_H
