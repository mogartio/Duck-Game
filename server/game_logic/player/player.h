#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/coordinate.h"
#include "../map/stage.h"
#include "position/player_position.h"
#include "weapons/weapon.h"

#include "observer.h"
#include "subject.h"

class Player: public PlayerSubject {
private:
    int id;
    std::unique_ptr<PlayerPosition> position;
    bool is_alive;
    Stage* stage;
    std::unique_ptr<Weapon> weapon;
    std::set<int> current_actions;
    std::string name;
    bool should_notify;
    Coordinate initial_position;

public:
    int get_id();
    Coordinate get_position();
    std::vector<Coordinate> get_occupied();
    int get_facing_direction();
    Player(Coordinate&, int, std::string, PlayerObserver*);
    void die();
    void occupy(Coordinate&);
    void add_action(int&);
    void remove_action(int&);
    void move(std::set<int>&);
    void execute(int&);
    void shoot();
    void update();
    void Notify() { should_notify = true; }
    void notify() override;
    void init_for_stage(Stage*);
    bool lives() { return is_alive; }
};

#endif
