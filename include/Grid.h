/*
 * Project: Battleship
 * File:    Grid.h
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include "game_err.h"
#include "ShipType.h"
#include "Position.h"
#include "Ship.h"
#include "BattleshipUtil.h"

class Grid {
    private:
        int row = SIZE_GRID_ROW, col = SIZE_GRID_COL;
        char*** grid;

    public:
        Grid();
        Grid(int, int);
        ~Grid();

        GameErr_t setRow(int);
        int getRow(void);

        GameErr_t setCol(int);
        int getCol(void);

        GameErr_t buildGrid(int, int);
        char*** getGrid(void);

        GameErr_t placeShip(Ship*, Position);
        GameErr_t randomPlaceShip(Ship*);

        bool isFit(Ship*, Position*);

        void printGrid(void);
};

#endif /* __GRID_H__ */