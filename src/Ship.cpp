#include "Ship.h"

Ship::Ship(Ship_t eShip) : eType(eShip) {

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
    delete[] this->shipMap;
}

GameErr_t Ship::setSize(int newSize) {
    if(newSize <= 0) {
        return GAME_VALUE_ERR;
    }

    this->size = newSize;

    return GAME_OK;
}

int Ship::getSize() {
    return this->size;
}

GameErr_t Ship::buildShipMap(int newSize) {
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
    return this->shipMap;
}

Ship_t Ship::getShipType() {
    return this->eType;
}