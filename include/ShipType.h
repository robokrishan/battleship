/*
 * Project: Battleship
 * File:    ShipType.h
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

#ifndef __SHIP_TYPE_H__
#define __SHIP_TYPE_H__

#define SIZE_CARRIER 5
#define SIZE_BATTLESHIP 4
#define SIZE_CRUISER 3
#define SIZE_SUBMARINE 3
#define SIZE_DESTROYER 2


enum Ship_t {
    SHIP_CARRIER = 0,
    SHIP_BATTLESHIP = 1,
    SHIP_CRUISER = 2,
    SHIP_SUBMARINE = 3,
    SHIP_DESTROYER = 4,
};

#endif /* __SHIP_TYPE_H__ */