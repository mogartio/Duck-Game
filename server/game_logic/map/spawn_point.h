#ifndef SPAWN_POINT_H
#define SPAWN_POINT_H
#include <memory>
#include <utility>

#include "../../../common/coordinate.h"
#include "../../../common/messages/generic_msg.h"
#include "../player/weapons/pistols.h"
using namespace ProjectilesId;

#include "stage.h"
class WeaponSpawnPoint {
private:
    Coordinate position;
    Stage& stage;
    bool is_free;
    int counter;
    int type_of_weapon;

public:
    WeaponSpawnPoint(Coordinate position, Stage& stage, int type_of_weapon):
            position(position),
            stage(stage),
            is_free(false),
            counter(0),
            type_of_weapon(type_of_weapon) {
        spawn_weapon();
    }
    void spawn_weapon();
    void update();
    void free();
    void set_weapon(int weapon_id);
};

class ArmorSpawnPoint {
private:
    Coordinate position;
    Stage& stage;
    bool is_free;
    int counter;
    int type_of_armor;

public:
    ArmorSpawnPoint(Coordinate position, Stage& stage, int type_of_armor):
            position(position),
            stage(stage),
            is_free(false),
            counter(0),
            type_of_armor(type_of_armor) {
        spawn_armor();
    }
    void spawn_armor();
    void update();
    void free();
};


#endif
