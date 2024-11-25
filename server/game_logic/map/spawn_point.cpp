#include "spawn_point.h"

#include "../player/weapons/projectiles/projectile_dropped_weapon.h"

void WeaponSpawnPoint::spawn_weapon() {
    // ya se que esto es horrible lo hice 2 horas antes de la primera entrega, its never been this
    // serious
    std::unique_ptr<Weapon> weapon;
    if (type_of_weapon == COWBOY_PISTOL) {
        weapon = std::make_unique<CowboyGun>(stage);
    } else if (type_of_weapon == MAGNUM) {
        weapon = std::make_unique<Magnum>(stage);
    } else if (type_of_weapon == DUEL_PISTOL) {
        weapon = std::make_unique<DuelPistol>(stage);
    } else if (type_of_weapon == AK_47) {
        weapon = std::make_unique<Ak47>(stage);
    } else if (type_of_weapon == SHOTGUN) {
        weapon = std::make_unique<Shotgun>(stage);
    } else if (type_of_weapon == SNIPER) {
        weapon = std::make_unique<Sniper>(stage);
    } else if (type_of_weapon == PEW_PEW_LASER) {
        weapon = std::make_unique<PewLaser>(stage);
    } else if (type_of_weapon == LASER_RIFLE) {
        weapon = std::make_unique<LaserRifle>(stage);
    }
    stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position, 4,
                                                                   599, type_of_weapon, this));
    // Para agregar mas opciones de armas agregarlas unicamente al switch
    std::unique_ptr<Weapon> weapon;
    switch (type_of_weapon) {
        case COWBOY_PISTOL:
            weapon = std::make_unique<CowboyGun>(stage);
            break;
        case MAGNUM:
            weapon = std::make_unique<Magnum>(stage);
            break;
        case HELMET:
        case HELMET2:
        case HELMET3:
            weapon = std::make_unique<Helmet>(stage, type_of_weapon);
            break;
        case CHEST:
            weapon = std::make_unique<Chest>(stage);
            break;
        default:
            weapon = std::make_unique<CowboyGun>(stage);
            break;
    }

    stage.add_projectile(std::make_unique<ProjectileDroppedWeapon>(std::move(weapon), position,
                                                                       4, 4, type_of_weapon, this));
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

