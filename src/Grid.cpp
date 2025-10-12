/*
 * Project: Battleship
 * File:    Grid.cpp
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

#include "Grid.h"

// # define DEBUG

// constructors and destructors
Grid::Grid() {
#ifdef DEBUG
    std::cout << "Grid()\tConstructor" << std::endl;
#endif

    // Seed the random number generator once
    srand(static_cast<unsigned int>(time(NULL)));

    GameErr_t lRet = this->buildGrid(this->row, this->col);


    if(GAME_OK == lRet) {
#ifdef DEBUG
        std::cout << "Grid constructed successfully! (Code: " << lRet << ")" << std::endl;
#endif
    }
}

Grid::Grid(int newRow, int newCol) : row(newRow), col(newCol) {
#ifdef DEBUG
    std::cout << "Grid()\tParametrized Constructor" << std::endl;
#endif

    // Seed the random number generator once
    srand(static_cast<unsigned int>(time(NULL)));

    GameErr_t lRet = this->buildGrid(this->row, this->col);

    if(GAME_OK == lRet) {
#ifdef DEBUG
        std::cout << "Grid constructed successfully! (Code: " << lRet << ")" << std::endl;
#endif
    }
}

Grid::~Grid() {
    // Perform deallocation of bool grid
#ifdef DEBUG
    std::cout << "~Grid()\tDestructor" << std::endl;
#endif

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if(*this->grid[i][j] == 'O') {
                delete this->grid[i][j];            // delete each char
            }
        }
        delete[] this->grid[i];                     // delete row
    }
    delete[] this->grid;                            // delete grid pointer array
}


// setters and getters
GameErr_t Grid::setRow(int newRow) {
    if(newRow <= 0) {
        return GAME_VALUE_ERR;
    }

    this->row = newRow;

    return GAME_OK;
}

int Grid::getRow(void) {
    return this->row;
}

GameErr_t Grid::setCol(int newCol) {
    if(newCol <= 0) {
        return GAME_VALUE_ERR;
    }

    this->col = newCol;

    return GAME_OK;
}

int Grid::getCol(void) {
    return this->col;
}

GameErr_t Grid::buildGrid(int lRow, int lColumn) {
#ifdef DEBUG
    std::cout << "buildGrid()\tMember function" << std::endl;
#endif

    if(lRow <= 0 || lColumn <= 0) {
        return GAME_VALUE_ERR;
    }

    this->grid = new char**[lRow];

#ifdef DEBUG
    std::cout << "Initialized rows" << std::endl;
#endif

    for(int i = 0; i < lRow; i++) {
        this->grid[i] = new char*[lColumn];
    }

#ifdef DEBUG
    std::cout << "Initialized columns" << std::endl;
#endif

    for(int i = 0; i < lRow; i++) {
        for(int j = 0; j < lColumn; j++) {
            this->grid[i][j] = new char('O');
        }
    }

#ifdef DEBUG
    std::cout << "Initialized grid with Os" << std::endl;
#endif

    return GAME_OK;
}

char*** Grid::getGrid(void) {
    return this->grid;
}

void Grid::printGrid(void) {
    for(int i = 0; i < this->row; i++) {
        for(int j = 0; j < this->col; j++) {
            std::cout << " " << *this->grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;
}

GameErr_t Grid::placeShip(Ship* pShip, Position sPos) {
    GameErr_t lRet = GAME_ERROR;

    if(HORIZONTAL == sPos.o) {
        for(int i = 0; i < pShip->getSize(); i++) {
            delete this->grid[sPos.X + i][sPos.Y];
            this->grid[sPos.X + i][sPos.Y] = &pShip->getShipMap()[i];
        }

        lRet = GAME_OK;
    } else if (VERTICAL == sPos.o) {
        for(int i = 0; i < pShip->getSize(); i++) {
            delete this->grid[sPos.X][sPos.Y + i];
            this->grid[sPos.X][sPos.Y + i] = &pShip->getShipMap()[i];
        }

        lRet = GAME_OK;
    }

    return lRet;
}

GameErr_t Grid::randomPlaceShip(Ship* pShip) {
    Position sPos;

    sPos.X = rand() % (this->row-1);
    sPos.Y = rand() % (this->col-1);

#ifdef DEBUG
    std::cout << "Trying ( " << sPos.X << ", " << sPos.Y << " )" << std::endl;
#endif

    while(!this->isFit(pShip, &sPos)) {
        sPos.X = rand() % (this->row-1);
        sPos.Y = rand() % (this->col-1);
#ifdef DEBUG
        std::cout << "Trying ( " << sPos.X << ", " << sPos.Y << " )" << std::endl;
#endif
    }

#ifdef DEBUG
    std::cout << "Placing at ( " << sPos.X << ", " << sPos.Y << " )" << std::endl;
#endif

    return placeShip(pShip, sPos);
}

bool Grid::isFit(Ship* pShip, Position* pPos) {
#ifdef DEBUG
    std::cout << "Grid::isFit()\tMember function" << std::endl;
#endif
    if('O' != *this->grid[pPos->X][pPos->Y]) {
        return false;
    }

#ifdef DEBUG
    std::cout << "Checking horizontal fit..." << std::endl;
#endif
    // try horizontal fit
    if(pPos->X + pShip->getSize() >= this->getRow()) {

#ifdef DEBUG
        std::cout << "Checking vertical fit..." << std::endl;
#endif
        // try vertical fit
        if(pPos->Y + pShip->getSize() >= this->getCol()) {
            return false;
        } else {

            // Check if obstacle present
            for(int i = 0; i < pShip->getSize(); i++) {
                if(*this->grid[pPos->X][pPos->Y + i] != 'O') {
                    return false;
                }
            }
            pPos->o = VERTICAL;
            return true;
        }
    } else {

#ifdef DEBUG
        std::cout << "Checking horizontal obstacles..." << std::endl;
#endif
        // Check if obstacle present
        for(int i = 0; i < pShip->getSize(); i++) {
            if(*this->grid[pPos->X + i][pPos->Y] != 'O') {
                return false;
            }
        }

        pPos->o = HORIZONTAL;
        return true;
    }
}

