#ifndef PLAYER_POSITION_H
#define PLAYER_POSITION_H

#include <set>
#include <vector>

#include "../../../common/coordinate.h"
#include "../map/stage.h"

#include "air_state.h"
class Player;
class PlayerPosition {
private:
    Coordinate position;
    std::vector<Coordinate> occupied;  // Las coordenadas que esta ocupando
    Player& player;
    std::unique_ptr<AirState> air_state;
    uint8_t state;
    Stage& stage;
    uint8_t facing_direction;  // para disparar
    void move_horizontally(int);
    void move_vertically(int);
    bool aiming_up;

public:
    PlayerPosition(Coordinate&, Player&, Stage&);
    void set_state(std::unique_ptr<AirState>, uint8_t);
    void move(std::set<int>&);
    Coordinate get_position();
    uint8_t get_state() { return state; }
    void occupy(Coordinate&);
    void free_occupied();
    std::vector<Coordinate> get_occupied();
    uint8_t get_facing_direction();
    void released_jump();
    void released_w();
    bool is_aiming_up();
    void stop_aiming_up();
};

#endif
