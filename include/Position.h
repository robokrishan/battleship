#ifndef __POSITION_H__
#define __POSITION_H__

enum Orientation {
    HORIZONTAL = 0,
    VERTICAL = 1,
};

struct Position {
    int X;
    int Y;
    Orientation o = HORIZONTAL;
};

#endif /* __POSITION_H__ */