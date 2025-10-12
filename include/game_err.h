/*
 * Project: Battleship
 * File:    game_err.h
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

#ifndef __GAME_ERR_H__
#define __GAME_ERR_H__

enum GameErr_t {
    GAME_OK = 0,
    GAME_TYPE_ERR = -1,
    GAME_VALUE_ERR = -2,
    GAME_PLAYER_TIMEOUT_ERR = -3,
    GAME_ABORT_ERR = -4,
    GAME_ERROR = -100,
};

#endif /* __GAME_ERR_H__ */