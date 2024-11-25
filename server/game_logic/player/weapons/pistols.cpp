#include "pistols.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "../../config/weapon_config.h"
#include "projectiles/projectile.h"
using namespace ProjectilesId;

CowboyGun::CowboyGun(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["cowboy"]["ammo"],
               WeaponConfig::get_instance()->weapons["cowboy"]["reach"], COWBOY_PISTOL) {}

void CowboyGun::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<CowboyBullet>(gun_position, x_direction, -1, is_aiming_up, reach)));
    ammo--;
    stopped_holding_trigger = false;
}

Magnum::Magnum(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["magnum"]["ammo"],
               WeaponConfig::get_instance()->weapons["magnum"]["reach"], MAGNUM) {}

void Magnum::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<MagnumBullet>(gun_position, x_direction, -1, is_aiming_up, reach)));
    ammo--;
    stopped_holding_trigger = false;
}

DuelPistol::DuelPistol(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["magnum"]["ammo"],
               WeaponConfig::get_instance()->weapons["magnum"]["reach"], DUEL_PISTOL) {}

void DuelPistol::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<DuelBullet>(gun_position, x_direction, -1, is_aiming_up, reach)));
    ammo--;
    stopped_holding_trigger = false;
}

