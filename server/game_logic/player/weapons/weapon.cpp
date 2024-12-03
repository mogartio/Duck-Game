#include "weapon.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../player.h"
#include "projectiles/projectile.h"
#include "projectiles/projectile_dropped_weapon.h"
#define PLAYER_SIZE 6
void Weapon::start_throw() { throw_started = true; }
void Weapon::finish_throw(int x_direction, bool thrown_up, std::shared_ptr<Weapon> weapon) {
    Coordinate player_position = player->get_position();
    Coordinate gun_position(player_position.x - 3, player_position.y + 3);
    if (x_direction == 1) {
        gun_position.x = player_position.x + 6;
    }
    if (thrown_up) {
        gun_position.y = player_position.y - 1;
    }
    throw_started = false;
    int speed = Config::get_instance()->throw_speed;
    throw_reach = 0;
    stopped_holding_trigger = false;  // Esto es para que no dispare cuando se agarra
    stage.add_projectile(std::move(std::make_unique<ProjectileThrownWeapon>(
            std::move(weapon), gun_position, speed, x_direction, 80, id, thrown_up)));
}

// aim_direction en el eje x
Coordinate Weapon::get_gun_position(int facing_direction, bool aiming_up) {
    Coordinate gun_position = player->get_position();
    if (facing_direction == 1) {
        gun_position.x = gun_position.x + 7;
    } else {
        gun_position.x = gun_position.x - 3;
    }
    if (aiming_up) {
        gun_position.y--;
    } else {
        gun_position.y = gun_position.y + 3;
    }
    return gun_position;
}

Unarmed::Unarmed(Stage& stage): Weapon(stage, 0, 3, 0) {}

Coordinate Unarmed::get_gun_position(int facing_direction, bool aiming_up) {
    Coordinate gun_position = player->get_position();
    if (facing_direction == 1) {
        gun_position.x = gun_position.x + 6;
    } else {
        gun_position.x = gun_position.x - 2;
    }
    if (aiming_up) {
        gun_position.y--;
    } else {
        gun_position.y = gun_position.y + 2;
    }
    return gun_position;
}

void Unarmed::shoot(int x_direction, bool aiming_up) {
    // Se fija si existe un DroppedProjectile en la direccion en la que esta apuntando
    Coordinate init_position = get_gun_position(x_direction, aiming_up);
    int handle_direction = x_direction;
    for (int i = 0; i < reach; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate checking(init_position.x + i * handle_direction, init_position.y + j);
            if (stage.get(checking) > 0) {  // TODO: Definir bien cuales son los pickables
                std::shared_ptr<Weapon> weapon = stage.pick_weapon(checking);
                if (weapon != nullptr) {
                    player->pick_weapon(std::move(weapon));
                    return;
                }
                continue;
            }
        }
    }
}
