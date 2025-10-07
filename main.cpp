#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ship_type.h"
#include "Ship/Ship.h"
#include "Grid/Grid.h"
#include "Position.h"

using namespace std;

bool isFit(Ship* ship, Grid* grid, Position *pos) {
    if(true == *grid->getGrid()[pos->X][pos->Y]) {
        return false;
    }

    // try horizontal fit
    if(pos->X + ship->getSize() >= grid->getRow()) {

        // try vertical fit
        if(pos->Y + ship->getSize() >= grid->getCol()) {
            return false;
        } else {

            // Check if obstacle present
            for(int i = 0; i < ship->getSize(); i++) {
                if(*grid->getGrid()[pos->X][pos->Y + i] != 'O') {
                    return false;
                }
            }
            pos->o = VERTICAL;
            return true;
        }
    } else {

        // Check if obstacle present
        for(int i = 0; i < ship->getSize(); i++) {
            if(*grid->getGrid()[pos->X + i][pos->Y] != 'O') {
                return false;
            }
        }

        pos->o = HORIZONTAL;
        return true;
    }
}

void placeShip(Ship* ship, Grid* grid, Position pos) {
    if(HORIZONTAL == pos.o) {
        for(int i = 0; i < ship->getSize(); i++) {
            grid->getGrid()[pos.X + i][pos.Y] = &ship->getShipMap()[i];
        }
    } else {
        for(int i = 0; i < ship->getSize(); i++) {
            grid->getGrid()[pos.X][pos.Y + i] = &ship->getShipMap()[i];
        }
    }
}

void randomPlace(Ship* ship, Grid* grid) {
    Position pos;

    // Seed the random number generator once
    srand(static_cast<unsigned int>(time(NULL)));
    pos.X = rand() % (grid->getRow()-1);
    pos.Y = rand() % (grid->getCol()-1);

    cout << "Trying ( " << pos.X << ", " << pos.Y << " )" << endl;

    while(!isFit(ship, grid, &pos)) {
        pos.X = rand() % grid->getRow()-1;
        pos.Y = rand() % grid->getCol()-1;

        cout << "Trying ( " << pos.X << ", " << pos.Y << " )" << endl;
    }

    cout << "Placing at ( " << pos.X << ", " << pos.Y << " )" << endl;

    placeShip(ship, grid, pos);
}


int main() {

    cout << "Starting battleship..." << endl;

    // Build game grid
    Grid gameGrid;

    gameGrid.printGrid();

    Ship carrier = Ship(SHIP_CARRIER);
    Ship battleship = Ship(SHIP_BATTLESHIP);
    Ship cruiser = Ship(SHIP_CRUISER);
    Ship submarine = Ship(SHIP_SUBMARINE);
    Ship destroyer = Ship(SHIP_DESTROYER);
    
    gameGrid.randomPlaceShip(&carrier);
    gameGrid.randomPlaceShip(&battleship);
    gameGrid.randomPlaceShip(&cruiser);
    gameGrid.randomPlaceShip(&submarine);
    gameGrid.randomPlaceShip(&destroyer);

    cout << "Randomly placed ships!" << endl << endl;

    gameGrid.printGrid();

    return 0;
}