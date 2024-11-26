
#include "throwables.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "../player.h"
#include "projectiles/projectile.h"
using namespace ProjectilesId;

Grenade::Grenade(Stage& stage): Weapon(stage, 1, 10, GRENADE), turned_on(false), dead(false) {}

void Grenade::shoot(int, bool) {
    if (ammo == 0 || !stopped_holding_trigger || throw_started) {
        return;
    }
    ammo--;
    stopped_holding_trigger = false;
    turned_on = true;
}

bool Grenade::exploded() { return dead; }

void Grenade::update() {
    if (turned_on) {
        counter++;
    }
    if (counter == Config::get_instance()->explosion_counter) {
        stage.set_explosion(
                get_gun_position(player->get_facing_direction()),
                Config::get_instance()->explosion_range);  // TODO: tambien borrar el arma
        player->unarm_self();
    }
}

void Grenade::update(Coordinate position) {
    if (!turned_on) {
        return;
    }
    counter++;
    if (counter == Config::get_instance()->explosion_counter) {
        stage.set_explosion(position, Config::get_instance()->explosion_range);
        turned_on = false;
        dead = true;
    }
}

// void Grenade::finish_throw(int x_direction, bool, std::shared_ptr<Weapon> weapon) {
//     Coordinate gun_position = get_gun_position(x_direction);
//     throw_started = false;
//     int speed = throw_reach / 10;
//     throw_reach = 30;
//     stopped_holding_trigger = false;  // Esto es para que no dispare cuando se agarra
//     stage.add_projectile(std::move(std::make_unique<Projecti>(
//             std::move(weapon), gun_position, speed, x_direction, throw_reach, stage, GRENADE)));
// }
