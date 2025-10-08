#include "Ship.h"

Ship::Ship(Ship_t eShip) : eType(eShip) {
#ifdef DEBUG
    std::cout << "Ship::Ship()\tParametrized constructor" << std::endl;
#endif

    switch(eShip) {
        case SHIP_CARRIER: {        
            this->size = SIZE_CARRIER;
            this->shipChar = 'C';
            break;
        }

        case SHIP_BATTLESHIP: {
            this->size = SIZE_BATTLESHIP;
            this->shipChar = 'B';
            break;
        }   
            
        case SHIP_CRUISER: {        
            this->size = SIZE_CRUISER;
            this->shipChar = 'c';
            break;
        }
        
        case SHIP_DESTROYER: {
            this->size = SIZE_DESTROYER;
            this->shipChar = 'D';
            break;
        }   
            
        case SHIP_SUBMARINE: {   
            this->size = SIZE_SUBMARINE;
            this->shipChar = 'S';
            break;
        }

        default:                    
            this->size = 0;
            this->shipChar = '?';
            break;
    }

    this->buildShipMap(this->size);
}

Ship::~Ship() {
#ifdef DEBUG
    std::cout << "Ship::~Ship()\tDestructor" << std::endl;
#endif

    delete[] this->shipMap;
}

GameErr_t Ship::setSize(int newSize) {
#ifdef DEBUG
    std::cout << "Ship::setSize()\tMember function" << std::endl;
#endif

    if(newSize <= 0) {
        return GAME_VALUE_ERR;
    }

    this->size = newSize;

    return GAME_OK;
}

int Ship::getSize() {
#ifdef DEBUG
    std::cout << "Ship::getSize()\tMember function" << std::endl;
#endif

    return this->size;
}

GameErr_t Ship::buildShipMap(int newSize) {
#ifdef DEBUG
    std::cout << "Ship::buildShipMap()\tMember function" << std::endl;
#endif

    if (newSize <= 0) {
        return GAME_VALUE_ERR;
    }

    this->shipMap = new char[this->size];

    for(int i = 0; i < this->size; i++) {
        this->shipMap[i] = this->shipChar;
    }

    return GAME_OK;
}

char* Ship::getShipMap() {
#ifdef DEBUG
    std::cout << "Ship::getShipMap()\tMember function" << std::endl;
#endif

    return this->shipMap;
}

Ship_t Ship::getShipType() {
#ifdef DEBUG
    std::cout << "Ship::getShipType()\tMember function" << std::endl;
#endif

    return this->eType;
}

int Ship::getShipHealth() {
#ifdef DEBUG
    std::cout << "Ship::getShipHealth()\tMember function" << std::endl;
#endif

    int lHealth = 0;

    for(int i = 0; i < this->getSize(); i++) {
        if(this->getShipMap()[i] == this->getShipChar()) {
            lHealth++;
        }
    }

    return lHealth;
}

char Ship::getShipChar() {
#ifdef DEBUG
    std::cout << "Ship::getShipChar()\tMember function" << std::endl;
#endif

    return this->shipChar;
}