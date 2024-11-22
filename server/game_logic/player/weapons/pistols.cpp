#include "pistols.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "projectiles/projectile.h"
#include "../player.h"
using namespace ProjectilesId;

CowboyGun::CowboyGun(Stage& stage): Weapon(stage, 6, 20, COWBOY_PISTOL) {}

void CowboyGun::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<CowboyBullet>(gun_position, x_direction, is_aiming_up, reach)));
    ammo--;
    stopped_holding_trigger = false;
}

Magnum::Magnum(Stage& stage): Weapon(stage, 6, 20, MAGNUM) {}

void Magnum::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<MagnumBullet>(gun_position, x_direction, is_aiming_up, reach)));
    ammo--;
    stopped_holding_trigger = false;
}

Chest::Chest(Stage& stage): Weapon(stage, 1, 20, CHEST) {}

void Chest::shoot(int damage, bool) {
    // Recibe daño
    ammo -= damage;
    if (ammo == 0) {
        // Caso de que se quede sin daño posible, desaparece la armadura
        player->pick_chest(std::make_unique<Unarmed>(stage));
    }
}


Helmet::Helmet(Stage& stage): Weapon(stage, 1, 20, HELMET) {}

void Helmet::shoot(int damage, bool) {
    // Recibe daño
    ammo -= damage;
    if (ammo == 0) {
        // Caso de que se quede sin daño posible, desaparece el casco
        player->pick_helmet(std::make_unique<Unarmed>(stage));
    }
}
