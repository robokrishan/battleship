/*
 * Project: Battleship
 * File:    Player.h
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

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

        /*
            Get the vector containing the fleet of ships.

            Args: None
            Return: std::vector containing pointers to ships
        */
        std::vector<Ship*> getFleet(void);

        GameErr_t initializeShips(void);

        GameErr_t placeShipsAutomatically(void);

        bool attack(Player*, Position);

        int getPlayerHealth(void);

        bool isAlive(void);

        bool isAttacked(Position);

        void displayFleet(void);
};

#endif /* __PLAYER_H__ */