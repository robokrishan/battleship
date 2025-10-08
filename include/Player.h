#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "game_err.h"
#include "Grid.h"

class Player {
    private:
        std::string szName;
        Grid sGrid;
        Ship* pCarrier;
        Ship* pBattleship;
        Ship* pDestroyer;
        Ship* pSubmarine;
        Ship* pCruiser;

    public:
        Player();
        Player(std::string);
        ~Player();

        GameErr_t setName(std::string);
        std::string getName(void);

        Grid* getGrid(void);

        GameErr_t initializeShips(void);

        GameErr_t placeShipsAutomatically(void);

        bool attack(Player*, Position);

        int getPlayerHealth(void);

        bool isAlive(void);
};

#endif /* __PLAYER_H__ */