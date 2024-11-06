#ifndef SPAWN_POINT_H
#define SPAWN_POINT_H
#include <memory>
#include <utility>

#include "../../../common/coordinate.h"
#include "../player/projectile_dropped_weapon.h"

#include "stage.h"
class WeaponSpawnPoint {
private:
    Coordinate position;
    Stage& stage;

public:
    WeaponSpawnPoint(Coordinate position, Stage& stage): position(position), stage(stage) {}
    void spawn_weapon() {
        auto weapon = std::make_unique<CowboyGun>(stage);
        stage.add_projectile(
                std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position, 4, 4, 0));
    }
};

#endif
