#include "weapon.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../player.h"
#include "projectiles/projectile.h"
#include "projectiles/projectile_dropped_weapon.h"
#define PLAYER_SIZE 3
void Weapon::start_throw() {
    throw_started = true;
    throw_reach += 3;
}
void Weapon::finish_throw(int x_direction, bool, std::shared_ptr<Weapon> weapon) {
    Coordinate gun_position = get_gun_position(x_direction);
    throw_started = false;
    /* double deviation_angle = M_PI / 2; */
    // TODO: deberia poder tirar la granada para arriba
    stage.add_projectile(std::move(std::make_unique<ProjectileThrownWeapon>(
            std::move(weapon), gun_position, throw_reach, x_direction, 80, id)));
}

// aim_direction en el eje x
Coordinate Weapon::get_gun_position(int facing_direction) {
    Coordinate player_position = player->get_position();
    if (facing_direction == 1) {
        return Coordinate(player_position.x + 3, player_position.y + 1);
    }
    return Coordinate(player_position.x - 1, player_position.y + 1);
}

Unarmed::Unarmed(Stage& stage): Weapon(stage, 0, 3, 0) {}

Coordinate Unarmed::get_gun_position(int facing_direction) {
    Coordinate player_position = Weapon::get_gun_position(facing_direction);
    player_position.y--;
    return player_position;
}
void Unarmed::shoot(int x_direction, bool) {
    Coordinate init_position = get_gun_position(x_direction);
    int handle_direction = x_direction;
    for (int i = 0; i < reach; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate checking(init_position.x + i * handle_direction, init_position.y + j);
            if (stage.get(checking) > 0 &&
                stage.get(checking) < 11) {  // TODO: Definir bien cuales son los pickables
                std::shared_ptr<Weapon> weapon = stage.pick_weapon(checking);
                if (weapon != nullptr) {
                    player->pick_weapon(std::move(weapon));
                }
                return;
            }
        }
    }
}
