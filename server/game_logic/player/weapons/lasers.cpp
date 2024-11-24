#include "lasers.h"
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
    stopped_holding_trigger = false;
}
void PewLaser::stop_shooting() { stopped_holding_trigger = true; }
