#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <iostream>

#include "ShipType.h"
#include "Player.h"
#include "game_err.h"
#include "Battlelog.h"

class Battleship {
    private:
        int lNumPlayers;
        Player* pPlayers;
        Battlelog sLog;

        GameErr_t takeAttackInput(Position&, int);

    public:
        Battleship(int);
        ~Battleship();

        GameErr_t setNumPlayers(int);
        int getNumPlayers(void);

        GameErr_t play(void);

        void printGameBoardV1(void);
        void printGameBoardV2(void);
};

#endif /* __BATTLESHIP_H__ */