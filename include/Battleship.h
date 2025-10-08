#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <iostream>
#include "ShipType.h"
#include "Player.h"
#include "game_err.h"

class Battleship {
    private:
        int lNumPlayers;
        Player* pPlayers;

        GameErr_t takeAttackInput(int*, int*, int);

    public:
        Battleship(int);
        ~Battleship();

        GameErr_t setNumPlayers(int);
        int getNumPlayers(void);

        GameErr_t play(void);

        void printGameBoard(void);
};

#endif /* __BATTLESHIP_H__ */