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
