#ifndef __SHIP_H__
#define __SHIP_H__

#include <iostream>
#include "game_err.h"
#include "ShipType.h"

class Ship {
    private:
        int size;
        char *shipMap;
        Ship_t eType;
        char shipChar;

    public:
        Ship(Ship_t eShip);
        ~Ship();

        GameErr_t setSize(int newSize);
        int getSize(void);

        GameErr_t buildShipMap(int newSize);
        char* getShipMap(void);

        Ship_t getShipType(void);
};

#endif /* __SHIP_H__ */