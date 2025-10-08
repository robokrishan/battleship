#include "Battlelog.h"

#include <iostream>

Battlelog::Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::Battlelog()\tConstructor" << std::endl;
#endif


}

Battlelog::~Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::~Battlelog()\tDestructor" << std::endl;
#endif


}

void Battlelog::logEntry(std::string szPlayerName, Position sPos, bool isHit) {
#ifdef DEBUG
    std::cout << "Battlelog::logEntry()\tMember function" << std::endl;
#endif

    AttackEntry sEntry = {
        .szPlayerName = szPlayerName,
        .sPos = {
            .X = sPos.X,
            .Y = sPos.Y,
        },
        .isHit = isHit
    };

    this->vRegister.push_back(sEntry);
}

void Battlelog::showHistory(void) {
#ifdef DEBUG
    std::cout << "Battlelog::showHistory()\tMember function" << std::endl;
#endif

    if(this->getLogSize() <= 0) {
        std::cout << "No entries in battlelog!" << std::endl;
    }

    std::cout << "Attack History:" << std::endl;

    for(int i = 0; i < this->getLogSize(); i++) {
        this->printEntry(i);
    }
}

void Battlelog::printEntry(int lIndex) {
#ifdef DEBUG
    std::cout << "Battlelog::printEntry()\tMember function" << std::endl;
#endif

    AttackEntry sEntry = this->vRegister[lIndex];

    std::cout << lIndex+1 << ". " <<  sEntry.szPlayerName << "\t( " <<  sEntry.sPos.X << ", " << sEntry.sPos.Y;
    std::cout << " )\tHit: " << sEntry.isHit << std::endl;
}

int Battlelog::getLogSize(void) {
#ifdef DEBUG
    std::cout << "Battlelog::getLogSize()\tMember function" << std::endl;
#endif

    return this->vRegister.size();
}