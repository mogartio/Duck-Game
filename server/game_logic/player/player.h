#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/coordinate.h"
#include "../map/stage.h"

#include "air_state.h"
#include "observer.h"
#include "player_position.h"
#include "subject.h"
#include "weapon.h"

class Player: public PlayerSubject {
private:
    int id;
    PlayerPosition position;
    bool is_alive;
    Stage& stage;
    std::unique_ptr<Weapon> weapon;
    std::set<int> current_actions;
    std::string name;

public:
    int get_id();
    Coordinate get_position();
    std::vector<Coordinate> get_occupied();
    Player(Coordinate&, Stage&, int, std::string);
    void die();
    void occupy(Coordinate&);
    void add_action(int&);
    void remove_action(int&);
    void move(std::set<int>&);
    void execute(int&);
    void shoot();
    void update();
    void notify() override;
};

#endif
