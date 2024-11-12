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

public:
    WeaponSpawnPoint(Coordinate position, Stage& stage): position(position), stage(stage) {}
    void spawn_weapon() {
        auto weapon = std::make_unique<CowboyGun>(stage);
        stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position,
                                                                       4, 4, COWBOY_PISTOL));
    }
};

#endif
