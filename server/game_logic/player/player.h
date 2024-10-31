#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "../../../common/coordinate.h"
#include "../map/stage.h"

#include "air_state.h"
#include "player_position.h"
#include "weapon.h"

class Player {
private:
    int id;
    PlayerPosition position;
    bool is_alive;
    Stage& stage;
    std::unique_ptr<Weapon> weapon;
    std::set<std::string> current_actions;

public:
    int get_id();
    Coordinate get_position();
    std::vector<Coordinate> get_occupied();
    Player(Coordinate&, Stage&, int);
    void die();
    void occupy(Coordinate&);
    void add_action(std::string&);
    void remove_action(std::string&);
    void move(std::set<std::string>&);
    void execute(std::string&);
    void shoot();
    void update();
};

#endif
