#include "Battleship.h"
#include "BattleshipUtil.h"

#include <iomanip>

// #define DEBUG

Battleship::Battleship(int lNum) : lNumPlayers(lNum) {
#ifdef DEBUG
    std::cout << "Battleship::Battleship()\tParametrized Constructor" << std::endl;
#endif

    this->pPlayers = new Player[this->lNumPlayers];
}


Battleship::~Battleship() {
#ifdef DEBUG
    std::cout << "Battleship::~Battleship()\tDestructor" << std::endl;
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
#ifdef DEBUG
    std::cout << "Battleship::getNumPlayers()\tMember function" << std::endl;
#endif

    return this->lNumPlayers;
}


GameErr_t Battleship::play() {
#ifdef DEBUG
    std::cout << "Battleship::play()\tMember function" << std::endl;
#endif

    GameErr_t lErr = GAME_OK;

    // Set player names
    for(int i = 0; i < this->lNumPlayers; i++) {
        std::string szName;
        std::cout << "Enter P" << i+1 << " name: ";
        std::cin >> szName;

        int lMaxAttempts = 3;

        while(GAME_OK != this->pPlayers[i].setName(szName)) {

            std::cout << ". Enter P" << i+1 << " name: ";
            std::cin >> szName;
            std::cout << std::endl;

            lMaxAttempts--;

            if(lMaxAttempts == 0) {
                std::cout << "ERROR: Failed to enter valid name. Aborting game..." << std::endl << std::endl;
                return GAME_ERROR;
            }
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
            return GAME_VALUE_ERR;
        }
    }

    this->printGameBoardV2();

    int lPlayerTurn = 0;
    bool succ;
    Position sAttackPos;

    while(this->pPlayers[0].isAlive() && this->pPlayers[1].isAlive()) {
        
        lErr = this->takeAttackInput(sAttackPos, lPlayerTurn);
        if (GAME_VALUE_ERR == lErr) {
            lPlayerTurn ^= 1;
            continue;
        } else if (GAME_ABORT_ERR == lErr) {
            return lErr;
        }

        std::cout << this->pPlayers[lPlayerTurn].getName() << " attacking ";
        std::cout << this->pPlayers[lPlayerTurn^1].getName() << " at ( " << sAttackPos.X+1 << ", ";
        std::cout << sAttackPos.Y+1 << " )\t...";

        succ = this->pPlayers[lPlayerTurn].attack(&this->pPlayers[lPlayerTurn^1], sAttackPos);
        this->sLog.logEntry(this->pPlayers[lPlayerTurn].getName(), sAttackPos, succ);

        if(succ) {
            std::cout << "HIT" << std::endl;
        } else {
            std::cout << "miss" << std::endl;
        }

        this->printGameBoardV2();

        if(!succ) {
            lPlayerTurn ^= 1;
        }
    }

    std::string winner;

    if(!this->pPlayers[0].isAlive()) {
        winner = this->pPlayers[1].getName();
    } else {
        winner = this->pPlayers[0].getName();
    }

    std::cout << winner << " wins!" << std::endl;

    this->sLog.showHistory();

    return lErr;
}


GameErr_t Battleship::takeAttackInput(Position& pPosition, int lPlayerTurn) {
#ifdef DEBUG
    std::cout << "Battleship::takeAttackInput()\tMember function" << std::endl;
#endif

    GameErr_t lErr = GAME_OK;
    int lOpponent = lPlayerTurn ^ 1;

    int lOppRow = this->pPlayers[lOpponent].getGrid()->getRow();
    int lOppCol = this->pPlayers[lOpponent].getGrid()->getCol();
    int lAttempts = 3;
    char cDelim = 0;

    do {
        std::cout << this->pPlayers[lPlayerTurn].getName() << ". Enter coordinates to attack (x,y): ";
        std::cin >> pPosition.X >> cDelim >> pPosition.Y;
        std::cout << std::endl;

        bool rangeErr =  (pPosition.X <= 0 || pPosition.X > lOppRow || pPosition.Y <= 0 || pPosition.Y > lOppCol);
        if(rangeErr) {
            std::cout << "ERROR: Invalid value. Enter coordinates in range ( [1, ";
            std::cout << lOppRow << "], [1, ";
            std::cout << lOppCol << "] )" << std::endl;
            lErr = GAME_VALUE_ERR;
        }

        bool delimErr = (cDelim != ',');
        if(delimErr) {
            std::cout << "ERROR: Invalid delimiter. Please use comma ','" << std::endl;
            lErr = GAME_VALUE_ERR;
        }

        bool alreadyAttacked = false;
        if(!rangeErr && !delimErr) {
            Position realPosition = {
                .X = pPosition.X-1,
                .Y = pPosition.Y-1,
            };

            alreadyAttacked = this->pPlayers[lOpponent].isAttacked(realPosition);

            if(alreadyAttacked) {
                std::cout << "ERROR: Already attacked here!" << std::endl;
            }
        }
        
        if(!delimErr && !rangeErr && !alreadyAttacked) {
            pPosition.X--;
            pPosition.Y--;
            return GAME_OK;
        }

        lAttempts--;

    } while(lAttempts > 0);

    std::cout << "Failed to provide valid input. Next player's turn!" << std::endl;

    return lErr;
}


void Battleship::printGameBoardV1() {
#ifdef DEBUG
    std::cout << "Battleship::printGameBoardV1()\tMember function" << std::endl;
#endif

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


void Battleship::printGameBoardV2() {
#ifdef DEBUG
    std::cout << "Battleship::printGameBoardV2()\tMember function" << std::endl;
#endif

    int rows = this->pPlayers[0].getGrid()->getRow();
    int cols = this->pPlayers[0].getGrid()->getCol();

    int boardWidth = cols * 3;          // Each cell = 3 chars
    int spacing = 5;                    // Space between grids
    int totalWidth = boardWidth * 2 + spacing + 10;


    // ===== Top Border =====
    for (int i = 0; i < totalWidth; i++) std::cout << "=";
    std::cout << "\n##" << std::setw(totalWidth - 4) << std::setfill(' ') << "  " << "##\n";

    // Centered title
    std::string title = "Battleship Board";
    int innerWidth = totalWidth - 4;
    int pad = (innerWidth - static_cast<int>(title.size())) / 2;
    int padRight = innerWidth - pad - static_cast<int>(title.size());

    std::cout << "##"
            << std::string(pad, ' ')
            << title
            << std::string(padRight, ' ')
            << "##\n";

    std::cout << "##" << std::setw(totalWidth - 4) << std::setfill(' ') << " " << "##\n";
    for (int i = 0; i < totalWidth; i++) std::cout << "=";
    std::cout << std::setfill(' ') << std::endl << std::endl;


    // ===== Column Headers =====
    std::cout << "   "; // margin for row labels
    for (int j = 1; j <= cols; j++) {
        std::cout << std::setw(3) << j; // 3-char width
    }

    std::cout  << "        "; // spacing between grids

    for (int j = 1; j <= cols; j++) {
        std::cout << std::setw(3) << j;
    }
    std::cout << "\n";

    // ===== Separator =====
    std::cout << "   " << std::string(boardWidth, '-') 
              << std::setw(spacing + 3) << " " 
              << std::string(boardWidth, '-') << "\n";

    // ===== Rows =====
    for (int i = 0; i < rows; i++) {
        // Left row number
        std::cout << std::setw(2) << i + 1 << " |";

        // P1 grid
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(2) << *this->pPlayers[0].getGrid()->getGrid()[i][j] << " ";
        }

        // Spacing between grids
        std::cout << std::setw(spacing - 1) << " ";

        // Right row number
        std::cout << std::setw(2) << i + 1 << " |";

        // P2 grid
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(2) << *this->pPlayers[1].getGrid()->getGrid()[i][j] << " ";
        }

        std::cout << "\n";
    }

    // ===== Bottom Border =====
    std::cout << std::endl;
    for (int i = 0; i < totalWidth; i++) std::cout << "=";
    std::cout << "\n\n";
}
