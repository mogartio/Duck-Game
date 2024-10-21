#ifndef PLAYER_POSITION_H
#define PLAYER_POSITION_H

#include <vector>
#include "../../../common/coordinate.h"
#include "air_state.h"
#include "../map/stage.h"
class Player;
class PlayerPosition{
private:
    Coordinate position;
    std::vector<Coordinate> occupied; //Las coordenadas que esta ocupando
    Player& player;
    std::unique_ptr<AirState> air_state;
    Stage& stage;
    int facing_direction; //para disparar
    void move_horizontally(int);
    void move_vertically(int);
public:
    PlayerPosition(Coordinate&, Player&, Stage&);
    void set_state(std::unique_ptr<AirState>);
    void move(std::string&);
    Coordinate get_position();
    void occupy(Coordinate&);
    void free_occupied();
    std::vector<Coordinate> get_occupied();
    int get_facing_direction();
};

#endif

