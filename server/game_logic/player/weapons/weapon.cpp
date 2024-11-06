#include "weapon.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../player.h"
#include "projectiles/projectile.h"
#include "projectiles/projectile_dropped_weapon.h"
// ammo, reach
void Weapon::start_throw() {
    throw_started = true;
    throw_reach += 3;
}
void Weapon::finish_throw(int x_direction, bool, std::unique_ptr<Weapon> weapon) {
    Coordinate gun_position = get_gun_position(x_direction);
    /* double deviation_angle = M_PI / 2; */
    // TODO: deberia poder tirar la granada para arriba
    stage.add_projectile(std::move(std::make_unique<ProjectileThrownWeapon>(
            std::move(weapon), gun_position, throw_reach, x_direction, 80)));
}

// aim_direction en el eje x
Coordinate Weapon::get_gun_position(int facing_direction) {
    Coordinate player_position = player->get_position();
    if (facing_direction == 1) {
        return Coordinate(player_position.x + 2, player_position.y + 1);
    }
    return Coordinate(player_position.x, player_position.y + 1);
}
CowboyGun::CowboyGun(Stage& stage): Weapon(stage, 6, 20) {}

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

Magnum::Magnum(Stage& stage): Weapon(stage, 6, 20) {}

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


Grenade::Grenade(Stage& stage): Weapon(stage, 1, 10), turned_on(false) {}

void Grenade::shoot(int, bool) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    ammo--;
    stopped_holding_trigger = false;
    turned_on = true;
}

void Grenade::update() {
    if (turned_on) {
        counter++;
    }
    if (counter == Config::get_instance()->explosion_counter) {
        stage.set_explosion(
                get_gun_position(player->get_facing_direction()),
                Config::get_instance()->explosion_range);  // TODO: tambien borrar el arma
    }
}

void Grenade::finish_throw(int x_direction, bool, std::unique_ptr<Weapon> weapon) {
    Coordinate gun_position = get_gun_position(x_direction);
    // TODO: deberia poder tirar la granada para arriba
    stage.add_projectile(std::move(std::make_unique<GrenadeProjectile>(
            std::move(weapon), gun_position, throw_reach, x_direction, 1000, counter, stage)));
}
