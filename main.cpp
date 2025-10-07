#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ship_type.h"
#include "Ship/Ship.h"
#include "Grid/Grid.h"
#include "Position.h"
#include "Battleship.h"

using namespace std;

int main() {

    cout << "Starting battleship..." << endl;

    // // Build game grid
    // Grid gameGrid;

    // gameGrid.printGrid();

    // Ship carrier = Ship(SHIP_CARRIER);
    // Ship battleship = Ship(SHIP_BATTLESHIP);
    // Ship cruiser = Ship(SHIP_CRUISER);
    // Ship submarine = Ship(SHIP_SUBMARINE);
    // Ship destroyer = Ship(SHIP_DESTROYER);
    
    // gameGrid.randomPlaceShip(&carrier);
    // gameGrid.randomPlaceShip(&battleship);
    // gameGrid.randomPlaceShip(&cruiser);
    // gameGrid.randomPlaceShip(&submarine);
    // gameGrid.randomPlaceShip(&destroyer);

    // cout << "Randomly placed ships!" << endl << endl;

    // gameGrid.printGrid();

    Battleship game(2);

    game.play();

    game.printGameBoard();

    return 0;
}