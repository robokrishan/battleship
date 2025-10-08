#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ShipType.h"
#include "Ship.h"
#include "Grid.h"
#include "Position.h"
#include "Battleship.h"

using namespace std;

int main() {

    cout << "Starting battleship..." << endl;

    Battleship game(2);

    game.play();

    game.printGameBoard();

    return 0;
}