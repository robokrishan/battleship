#ifndef __BATTLELOG_H__
#define __BATTLELOG_H__

#include "Position.h"
#include "vector"

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

        void logEntry(const std::string, const Position&, bool);

        void showHistory(void) const;

        void printEntry(int) const;

        int getLogSize(void) const;
};

#endif /* __BATTLELOG_H__ */