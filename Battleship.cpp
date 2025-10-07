#include "Battleship.h"
#include "BattleshipUtil.h"

// #define DEBUG

Battleship::Battleship(int lNum) : lNumPlayers(lNum) {
#ifdef DEBUG
    std::cout << "Battleship()\tParametrized Constructor" << std::endl;
#endif

    this->pPlayers = new Player[this->lNumPlayers];
}

Battleship::~Battleship() {
#ifdef DEBUG
    std::cout << "~Battleship()\tDestructor" << std::endl;
#endif

    delete[] this->pPlayers;
}

GameErr_t Battleship::setNumPlayers(int lNum) {
#ifdef DEBUG
    std::cout << "Battleship::setNumPlayers()\tMember function" << std::endl;
#endif

    if(lNum <= 0) {
        return GAME_VALUE_ERR;
    }

    this->lNumPlayers = lNum;

    return GAME_OK;
}

int Battleship::getNumPlayers() {
    return this->lNumPlayers;
}

GameErr_t Battleship::play() {
    GameErr_t lErr = GAME_OK;

    // Set player names
    for(int i = 0; i < this->lNumPlayers; i++) {
        std::string szName;
        std::cout << "Enter P" << i+1 << " name: ";
        std::cin >> szName;

        int lMaxAttempts = 3;

        while(GAME_OK != this->pPlayers[i].setName(szName)) {
            if(lMaxAttempts == 0) {
                std::cout << "Aborting game..." << std::endl << std::endl;
                lErr = GAME_ERROR;
                goto end_play;
            }

            std::cout << ". Enter P" << i+1 << " name: ";
            std::cin >> szName;

            lMaxAttempts--;
        }
    }

    // Initialize player ships
    for(int i = 0; i < this->lNumPlayers; i++) {
        this->pPlayers[i].initializeShips();
    }

    // Initialize player grids
    for(int i = 0; i < this->lNumPlayers; i++) {
        char cResponse;
        std::cout << "Would P" << i+1 << " like to manually place ships? (y/n) ";
        std::cin >> cResponse;

        if('y' == cResponse || 'Y' == cResponse) {
            // Implement manual placement logic
        } else if ('n' == cResponse || 'N' == cResponse) {
            this->pPlayers[i].placeShipsAutomatically();
        } else {
            std::cout << "Invalid response! Response: " << cResponse << std::endl;
            std::cout << "Aborting..." << std::endl;
            lErr = GAME_VALUE_ERR;
            goto end_play;
        }
    }

    
end_play:

    return lErr;
}

void Battleship::printGameBoard() {
    for(int i = 0; i < 90; i++) {
        std::cout << "=";
    }

    std::cout << "\n##";
    for(int i = 0; i < 86; i++) {
        std::cout << " ";
    }
    std::cout << "##\n";

    for(int i = 0; i < this->pPlayers[0].getGrid()->getRow(); i++) {

        // Print for P1
        for(int j = 0; j < this->pPlayers[0].getGrid()->getRow(); j++) {
            if(j == 0) {
                std::cout << "##  ";
            }
            std::cout << " " << *this->pPlayers[0].getGrid()->getGrid()[i][j] << " ";
        }

        std::cout << "\t\t\t";

        // Print for P2
        for(int j = 0; j < this->pPlayers[1].getGrid()->getRow(); j++) {
            std::cout << " " << *this->pPlayers[1].getGrid()->getGrid()[i][j] << " ";
            if(j == this->pPlayers[1].getGrid()->getRow() - 1) {
                std::cout << "  ##";
            }
        }

        std::cout << "\n##";
        for(int i = 0; i < 86; i++) {
            std::cout << " ";
        }
        std::cout << "##\n";
    }

    for(int i = 0; i < 90; i++) {
        std::cout << "=";
    }

    std::cout << std::endl << std::endl;


}

// void printTopBar() {
//     for(int i = 0; i < 90; i++) {
//         std::cout << "=";
//     }

//     std::cout << "\n##";
//     for(int i = 0; i < 86; i++) {
//         std::cout << " ";
//     }
//     std::cout << "##\n";
// }

// void printBottomBar() {
//     for(int i = 0; i < 90; i++) {
//         std::cout << "=";
//     }
// }