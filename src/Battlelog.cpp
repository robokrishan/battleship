#include "Battlelog.h"

#include <iostream>
#include <filesystem>

Battlelog::Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::Battlelog()\tConstructor" << std::endl;
#endif

    int lCounter = 1;
    std::string szFilename;

    namespace fs = std::filesystem;

    do {
        this->pLogFile.close();

        szFilename = "log_" + std::to_string(lCounter) + ".txt";

        this->pLogFile.open(szFilename);
        lCounter++;

    } while(this->pLogFile.is_open());

    // this->pLogFile

}


Battlelog::~Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::~Battlelog()\tDestructor" << std::endl;
#endif


}


void Battlelog::logEntry(const std::string szPlayerName, const Position& sPos, bool isHit) {
#ifdef DEBUG
    std::cout << "Battlelog::logEntry()\tMember function" << std::endl;
#endif

    AttackEntry sEntry{szPlayerName, sPos, isHit};

    this->vRegister.push_back(sEntry);
}


void Battlelog::showHistory(void) const {
#ifdef DEBUG
    std::cout << "Battlelog::showHistory()\tMember function" << std::endl;
#endif

    if(this->getLogSize() <= 0) {
        std::cout << "No entries in battlelog!" << std::endl;
        return;
    }

    std::cout << "Attack History:" << std::endl;

    for(int i = 0; i < this->getLogSize(); i++) {
        this->printEntry(i);
    }
}


void Battlelog::printEntry(int lIndex) const {
#ifdef DEBUG
    std::cout << "Battlelog::printEntry()\tMember function" << std::endl;
#endif

    if(lIndex < 0 || lIndex >= this->vRegister.size()) {
        std::cout << "ERROR: Invalid log index: " << lIndex << std::endl;
        return;
    }

    AttackEntry sEntry = this->vRegister[lIndex];

    std::cout << lIndex+1 << ". " <<  sEntry.szPlayerName << "\t( " 
                <<  sEntry.sPos.X << ", " << sEntry.sPos.Y
                << " )\tHit: " << sEntry.isHit << std::endl;
}


int Battlelog::getLogSize(void) const {
#ifdef DEBUG
    std::cout << "Battlelog::getLogSize()\tMember function" << std::endl;
#endif

    return this->vRegister.size();
}
