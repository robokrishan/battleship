#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Battleship.h"

using namespace std;

int main() {

    cout << "Starting battleship..." << endl;

    Battleship game(2);

    game.play();

    return 0;
}