#include "Battlelog.h"

#include <iostream>
#include <filesystem>
#include "BattleshipUtil.h"

Battlelog::Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::Battlelog()\tConstructor" << std::endl;
#endif

    int lCounter = 1;
    std::string szFilename;

    namespace fs = std::filesystem;
    
    if(!fs::exists(this->szLogDir)) {
        fs::create_directory(this->szLogDir);
    }

    while(true) {
        szFilename = this->szLogDir + "log_" + std::to_string(lCounter) + ".txt";
        if(!fs::exists(szFilename)) {
            break;
        }
        lCounter++;
    }

    this->pLogFile.open(szFilename);
    if(pLogFile.is_open()) {
        std::cout << "Log file created: " << szFilename << std::endl;
    } else {
        std::cout << "ERROR: Failed to create log file: " << szFilename << std::endl;
    }
 
}


Battlelog::~Battlelog() {
#ifdef DEBUG
    std::cout << "Battlelog::~Battlelog()\tDestructor" << std::endl;
#endif

    if(this->pLogFile.is_open()) {
        this->pLogFile.close();
    }

}


void Battlelog::logEntry(const std::string szPlayerName, const Position& sPos, bool isHit) {
#ifdef DEBUG
    std::cout << "Battlelog::logEntry()\tMember function" << std::endl;
#endif

    static int lIndex = 1;
    AttackEntry sEntry{szPlayerName, sPos, isHit};

    // Add to log register
    this->vRegister.push_back(sEntry);

    // Add to logfile
    this->pLogFile << std::setw(3) << lIndex << ". "
               << std::setw(MAX_NAME_LENGTH) << sEntry.szPlayerName
               << " | ("
               << indexToRowChar(sEntry.sPos.X)
               << sEntry.sPos.Y + 1 << ")"
               << " | " << (sEntry.isHit ? "HIT" : "MISS")
               << std::endl;
    
    lIndex++;
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
