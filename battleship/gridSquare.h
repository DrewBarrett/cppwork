#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H


class gridSquare
{
    public:
        /** Default constructor */
        gridSquare();
        /** Access hit
         * \return The current value of hit
         */
        bool Gethit() { return hit; }
        /** Set hit
         * \param val New value to set
         */
        void Sethit(bool val) { hit = val; }
        /** Access miss
         * \return The current value of miss
         */
        bool Getmiss() { return miss; }
        /** Set miss
         * \param val New value to set
         */
        void Setmiss(bool val) { miss = val; }
        /** Access occupied
         * \return The current value of occupied
         */
        bool Getoccupied() { return occupied; }
        /** Set occupied
         * \param val New value to set
         */
        void Setoccupied(bool val) { occupied = val; }
        /** Access playerOwned
         * \return The current value of playerOwned
         */
        bool GetplayerOwned() { return playerOwned; }
        /** Set playerOwned
         * \param val New value to set
         */
        void SetplayerOwned(bool val) { playerOwned = val; }
    protected:
    private:
        bool hit; //!< Member variable "hit"
        bool miss; //!< Member variable "miss"
        bool occupied; //!< Member variable "occupied"
        bool playerOwned; //!< Member variable "playerOwned"
};

#endif // GRIDSQUARE_H
