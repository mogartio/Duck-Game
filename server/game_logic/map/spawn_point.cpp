#include "spawn_point.h"

#include "../player/weapons/projectiles/projectile_dropped_weapon.h"
void WeaponSpawnPoint::spawn_weapon() {
    auto weapon = std::make_unique<CowboyGun>(stage);
    stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position, 4,
                                                                   4, COWBOY_PISTOL, this));
}

void WeaponSpawnPoint::update() {
    if (!is_free) {
        return;
    }
    counter++;
    if (counter == 300) {
        spawn_weapon();
        counter = 0;
        is_free = false;
    }
}

void WeaponSpawnPoint::free() { is_free = true; }
