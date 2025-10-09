#ifndef __BATTLESHIPUTIL_H__
#define __BATTLESHIPUTIL_H__

#define SIZE_GRID_ROW 10
#define SIZE_GRID_COL 10

#define MAX_NAME_LENGTH 12
#define NUM_SHIPS 5
#define MAX_PLAYERS 2

const char INPUT_DELIM = ',';

inline int rowCharToIndex(char cRowChar) {
    cRowChar = std::toupper(cRowChar);

    if(cRowChar < 'A' || cRowChar > 'J'){
        std::cout << "ERROR: Out of range! Must be in [A - J]" << std::endl;
        return -1;
    }

    return cRowChar - 'A';
}

inline char indexToRowChar(int lIndex) {
    if(lIndex < 0 || lIndex > 9) {
        std::cout << "ERROR: Out of range! Must be in [0 - 9]" << std::endl;
    }

    return char('A' + lIndex);
}

#endif /* __BATTLESHIPUTIL_H__ */