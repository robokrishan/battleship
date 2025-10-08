#ifndef __BATTLELOG_H__
#define __BATTLELOG_H__

#include "Position.h"
#include "vector"
#include "game_err.h"

struct AttackEntry {
    std::string szPlayerName;
    Position sPos;
    bool isHit;
};

class Battlelog {
    private:
        std::vector<AttackEntry> vRegister;

    public:
        Battlelog();
        ~Battlelog();

        void logEntry(std::string, Position, bool);

        void showHistory(void);

        void printEntry(int);

        int getLogSize(void);
};

#endif /* __BATTLELOG_H__ */