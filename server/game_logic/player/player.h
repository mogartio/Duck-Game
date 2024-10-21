#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>
#include "../../../common/coordinate.h"
#include "air_state.h"
#include "player_position.h"
#include "weapon.h"
#include "../map/stage.h"

class Player{
private:
    int id;
    PlayerPosition position;
    bool is_alive;
    Stage& stage;
    std::unique_ptr<Weapon> weapon;
public:
    int get_id();
    Coordinate get_position();
    std::vector<Coordinate> get_occupied();
    Player(Coordinate&, Stage&);
    void die();
    void occupy(Coordinate&);
    void take_action(std::string& );
    void move(std::string&);
    void shoot();

};

#endif


