#include "Player.h"
#include "BattleshipUtil.h"

// #define DEBUG

Player::Player() {
#ifdef DEBUG
    std::cout << "Player::Player()\tDefault Constructor" << std::endl;
#endif
}


Player::Player(std::string szNewName) : szName(szNewName) {
#ifdef DEBUG
    std::cout << "Player::Player()\tParametrized Constructor" << std::endl;
#endif

}


Player::~Player() {
#ifdef DEBUG
    std::cout << "Player::~Player()\tDestructor" << std::endl;
#endif

    delete pCarrier;
    delete pBattleship;
    delete pDestroyer;
    delete pSubmarine;
    delete pCruiser;
}


GameErr_t Player::setName(std::string szNewName) {
#ifdef DEBUG
    std::cout << "Player::setName()\tMember function" << std::endl;
#endif

    if(szNewName.length() > MAX_NAME_LENGTH || szNewName.length() == 0) {
        std::cout << "Invalid name length " << szNewName.length() << "!" << std::endl;
        std::cout << "Must be [2, " << MAX_NAME_LENGTH << "]. Cannot be 'PC'." << std::endl;

        return GAME_VALUE_ERR;
    }

    this->szName = szNewName;

    return GAME_OK;
}


std::string Player::getName(void) {
#ifdef DEBUG
    std::cout << "Player::getName()\tMember function" << std::endl;
#endif

    return this->szName;
}


Grid* Player::getGrid(void) {
#ifdef DEBUG
    std::cout << "Player::getGrid()\tMember function" << std::endl;
#endif

    return &sGrid;
}


GameErr_t Player::initializeShips(void) {
#ifdef DEBUG
    std::cout << "Player::initializeShips()\tMember function" << std::endl;
#endif

    this->pCarrier = new Ship(SHIP_CARRIER);
    this->pBattleship = new Ship(SHIP_BATTLESHIP);
    this->pDestroyer = new Ship(SHIP_DESTROYER);
    this->pSubmarine = new Ship(SHIP_SUBMARINE);
    this->pCruiser = new Ship(SHIP_CRUISER);

    return GAME_OK;
}


GameErr_t Player::placeShipsAutomatically(void) {
#ifdef DEBUG
    std::cout << "Player::placeShipsAutomatically()\tMember function" << std::endl;
#endif
    
    GameErr_t lErr = GAME_OK;

    lErr = this->sGrid.randomPlaceShip(this->pCarrier);
    if(GAME_OK != lErr) {
#ifdef DEBUG
        std::cout << "Failed to auto place carrier! Aborting..." << std::endl;
#endif
        goto end_auto_place;
    }

    lErr = this->sGrid.randomPlaceShip(this->pBattleship);
    if(GAME_OK != lErr) {
#ifdef DEBUG
        std::cout << "Failed to auto place battleship! Aborting..." << std::endl;
#endif
        goto end_auto_place;
    }

    lErr = this->sGrid.randomPlaceShip(this->pDestroyer);
    if(GAME_OK != lErr) {
#ifdef DEBUG
        std::cout << "Failed to auto place destroyer! Aborting..." << std::endl;
#endif
        goto end_auto_place;
    }

    lErr = this->sGrid.randomPlaceShip(this->pSubmarine);
    if(GAME_OK != lErr) {
#ifdef DEBUG
        std::cout << "Failed to auto place submarine! Aborting..." << std::endl;
#endif
        goto end_auto_place;
    }

    lErr = this->sGrid.randomPlaceShip(this->pCruiser);
    if(GAME_OK != lErr) {
#ifdef DEBUG
        std::cout << "Failed to auto place cruiser! Aborting..." << std::endl;
#endif
        goto end_auto_place;
    }

end_auto_place:

    return lErr;
}


bool Player::attack(Player* pOpponent, Position sPos) {
#ifdef DEBUG
    std::cout << "Player::attack()\tMember function" << std::endl;
#endif

    if(*pOpponent->getGrid()->getGrid()[sPos.X][sPos.Y] == 'O') {
        *pOpponent->getGrid()->getGrid()[sPos.X][sPos.Y] = '~';
        return false;
    } else {
        *pOpponent->getGrid()->getGrid()[sPos.X][sPos.Y] = 'X';
        return true;
    }
}


bool Player::isAttacked(Position sPos) {
#ifdef DEBUG
    std::cout << "Player::isAttacked()\tMember function" << std::endl;
#endif
    bool alreadyHit = (*this->sGrid.getGrid()[sPos.X][sPos.Y] == 'X') || 
        (*this->sGrid.getGrid()[sPos.X][sPos.Y] == '~');

    return alreadyHit;
}


int Player::getPlayerHealth(void) {
#ifdef DEBUG
    std::cout << "Player::getPlayerHealth()\tMember function" << std::endl;
#endif

    int lHealth = 0;

    lHealth += pCarrier->getShipHealth();
    lHealth += pBattleship->getShipHealth();
    lHealth += pDestroyer->getShipHealth();
    lHealth += pSubmarine->getShipHealth();
    lHealth += pCruiser->getShipHealth();

    return lHealth;
}


bool Player::isAlive(void) {
#ifdef DEBUG
    std::cout << "Player::isAlive()\tMember function" << std::endl;
#endif

    return this->getPlayerHealth() > 0;
}


std::vector<Ship*> Player::getFleet(void) {
#ifdef DEBUG
    std::cout << "Player::getFleet()\tMember function" << std::endl;
#endif

    return {
        this->pCarrier,
        this->pBattleship,
        this->pCruiser,
        this->pSubmarine,
        this->pDestroyer
    };
}


void Player::displayFleet(void) {
#ifdef DEBUG
    std::cout << "Player::displayFleet()\tMember function" << std::endl;
#endif

    std::vector<Ship*> vFleet = this->getFleet();

    // Print top bar
    for(int i = 0; i < 25; i++)     std::cout << "=";
    std::cout << std::endl;

    for(int i = 0; i < NUM_SHIPS; i++) {

        std::cout << i+1 << ". " << vFleet[i]->getShipStr() << "\t[";
        
        for(int j = 0; j < vFleet[i]->getSize(); j++) {
            if(j < vFleet[i]->getShipHealth()) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }

        std::cout << "]" << std::endl;
    }
    
    for(int i = 0; i < 25; i++)     std::cout << "=";
    std::cout << std::endl;
}