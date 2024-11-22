#include "heavy_weapons.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "../../config/weapon_config.h"
#include "projectiles/projectile.h"

Ak47::Ak47(Stage& stage):
        Weapon(stage,
               WeaponConfig::get_instance()->WeaponConfig::get_instance()->weapons["ak47"]["ammo"],
               WeaponConfig::get_instance()->weapons["ak47"]["reach"], AK_47) {}

void Ak47::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(std::make_unique<Ak47Bullet>(
            gun_position, x_direction, -1, is_aiming_up, reach, bullets_shot)));
    ammo--;
    bullets_shot++;
}

void Ak47::stop_shooting() { bullets_shot = 0; }
