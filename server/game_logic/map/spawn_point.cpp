#include "spawn_point.h"

#include "../player/weapons/projectiles/projectile_dropped_weapon.h"
void WeaponSpawnPoint::spawn_weapon() {
    // ya se que esto es horrible lo hice 2 horas antes de la primera entrega, its never been this
    // serious
    if (type_of_weapon == COWBOY_PISTOL) {
        auto weapon = std::make_unique<CowboyGun>(stage);
        stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(
                std::move(weapon), position, 4, 599, type_of_weapon, this));
    } else if (type_of_weapon == MAGNUM) {
        auto weapon = std::make_unique<Magnum>(stage);
        stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(
                std::move(weapon), position, 4, 599, type_of_weapon, this));
    } else if (type_of_weapon == DUEL_PISTOL) {
        auto weapon = std::make_unique<DuelPistol>(stage);
        stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(
                std::move(weapon), position, 4, 599, type_of_weapon, this));
    }
}
void WeaponSpawnPoint::set_weapon(int weapon_id) { type_of_weapon = weapon_id; }

void WeaponSpawnPoint::update() {
    if (!is_free) {
        return;
    }
    counter++;
    // el counter es despues de cuantas iteraciones va a tirar un arma de nuevo
    if (counter == 300) {
        spawn_weapon();
        counter = 0;
        is_free = false;
    }
}

void WeaponSpawnPoint::free() { is_free = true; }
