#include "lasers.h"

#include "../player.h"
PewLaser::PewLaser(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["pewpew"]["ammo"],
               WeaponConfig::get_instance()->weapons["pewpew"]["reach"], PEW_PEW_LASER) {}

void PewLaser::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    int deviation = WeaponConfig::get_instance()->weapons["pewpew"]["deviation"];

    stage.add_projectile(std::move(
            std::make_unique<PewLaserBullet>(gun_position, x_direction, -1, is_aiming_up, reach,
                                             reach + 1, 1)));  // reach + 1 para que no desvie
    stage.add_projectile(std::move(std::make_unique<PewLaserBullet>(
            gun_position, x_direction, -1, is_aiming_up, reach, deviation, 1)));
    stage.add_projectile(std::move(std::make_unique<PewLaserBullet>(
            gun_position, x_direction, -1, is_aiming_up, reach, deviation, -1)));

    ammo--;
    if (ammo == 0) {
        player->pick_weapon(std::make_unique<Unarmed>(stage));
    }
    stopped_holding_trigger = false;
}
void PewLaser::stop_shooting() { stopped_holding_trigger = true; }


LaserRifle::LaserRifle(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["laser_rifle"]["ammo"],
               WeaponConfig::get_instance()->weapons["laser_rifle"]["reach"], LASER_RIFLE),
        stopped_pressing_since_picked(false) {}

void LaserRifle::finish_throw(int x_direction, bool, std::shared_ptr<Weapon> weapon) {
    Weapon::finish_throw(x_direction, true, weapon);
    stopped_pressing_since_picked = false;
}
void LaserRifle::stop_shooting() { stopped_pressing_since_picked = true; }

void LaserRifle::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_pressing_since_picked || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<LaserBullet>(gun_position, x_direction, 1, is_aiming_up, reach)));
    ammo--;
    if (ammo == 0) {
        player->pick_weapon(std::make_unique<Unarmed>(stage));
    }
}
