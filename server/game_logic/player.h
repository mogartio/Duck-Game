#ifndef PLAYER_H
#define PLAYER_H
#include "../../common/coordinate.h"
class Player{
private:
    Coordinate position;
public:
    int id;
    Coordinate get_position();
    Player(Coordinate&);
    void set_position(Coordinate);
};

#endif
