#include "heavy_weapons.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "../../config/weapon_config.h"
#include "../player.h"
#include "projectiles/projectile.h"
#define SHOTGUN_KNOCKBACK 2
Ak47::Ak47(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["ak47"]["ammo"],
               WeaponConfig::get_instance()->weapons["ak47"]["reach"], AK_47) {}

void Ak47::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || throw_started) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(std::make_unique<Ak47Bullet>(
            gun_position, x_direction, -1, is_aiming_up, reach, bullets_shot)));
    ammo--;
    if (bullets_shot % 4 == 0) {
        player->move(-x_direction);  // tiene retroceso, se mueve al jugador para atras
    }
    bullets_shot++;
}

void Ak47::stop_shooting() { bullets_shot = 0; }

Shotgun::Shotgun(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["shotgun"]["ammo"],
               WeaponConfig::get_instance()->weapons["shotgun"]["reach"], SHOTGUN),
        is_loaded(true),
        bullets_per_shot(WeaponConfig::get_instance()->weapons["shotgun"]["bullets_per_shot"]),
        init_deviation(WeaponConfig::get_instance()->weapons["shotgun"]["deviation"]) {}

void Shotgun::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    if (!is_loaded) {
        is_loaded = true;
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    for (int i = 0; i < bullets_per_shot; i++) {
        srand(static_cast<unsigned int>(time(nullptr)));  // seed del rand()
        int bullet_reach = reach + rand() % 3;            // el reach es variable entre 3 numeros
        int deviation_direction = -1 + 2 * (i % 2);
        stage.add_projectile(std::move(std::make_unique<ShotgunBullet>(
                gun_position, x_direction, -1, is_aiming_up, bullet_reach, init_deviation + 2,
                deviation_direction)));
    }
    ammo--;
    for (int i = 0; i < SHOTGUN_KNOCKBACK; i++) {
        player->move(-x_direction);  // tiene retroceso, se mueve al jugador para atras
    }
    is_loaded = false;
    stopped_holding_trigger = false;
}
void Shotgun::stop_shooting() { stopped_holding_trigger = true; }


Sniper::Sniper(Stage& stage):
        Weapon(stage, WeaponConfig::get_instance()->weapons["sniper"]["ammo"],
               WeaponConfig::get_instance()->weapons["sniper"]["reach"], SNIPER),
        is_loaded(true) {}

void Sniper::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    if (!is_loaded) {
        is_loaded = true;
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<SniperBullet>(gun_position, x_direction, -1, is_aiming_up, reach)));
    ammo--;
    is_loaded = false;
    stopped_holding_trigger = false;
}

void Sniper::stop_shooting() { stopped_holding_trigger = true; }