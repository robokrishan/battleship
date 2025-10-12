/*
 * Project: Battleship
 * File:    Battlelog.h
 * Author:  robokrishan
 * Year:    2025
 * Repo:    https://github.com/robokrishan/Battleship
 */

#ifndef __BATTLELOG_H__
#define __BATTLELOG_H__

#include "Position.h"
#include "vector"

#include <fstream>

struct AttackEntry {
    std::string szPlayerName;
    Position sPos;
    bool isHit;
};

class Battlelog {
    private:
        std::vector<AttackEntry> vRegister;
        std::ofstream pLogFile;
        std::string szLogDir = "./logs/";

    public:
        Battlelog();
        ~Battlelog();

        void logEntry(const std::string, const Position&, bool);

        void showHistory(void) const;

        void printEntry(int) const;

        int getLogSize(void) const;
};

#endif /* __BATTLELOG_H__ */