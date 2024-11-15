#ifndef SPAWN_POINT_H
#define SPAWN_POINT_H
#include <memory>
#include <utility>

#include "../../../common/coordinate.h"
#include "../../../common/messages/generic_msg.h"
#include "../player/weapons/pistols.h"
#include "../player/weapons/projectiles/projectile_dropped_weapon.h"
using namespace ProjectilesId;

#include "stage.h"
class WeaponSpawnPoint {
private:
    Coordinate position;
    Stage& stage;
    bool is_free;
    int counter;

public:
    WeaponSpawnPoint(Coordinate position, Stage& stage):
            position(position), stage(stage), is_free(false), counter(0) {
        spawn_weapon();
    }
    void spawn_weapon();
    void update();
    void free();
};

#endif
