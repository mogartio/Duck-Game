
#include "throwables.h"

#include <cmath>
#include <memory>
#include <utility>

#include "../../../../common/messages/generic_msg.h"
#include "../player.h"
#include "projectiles/projectile.h"
#include "projectiles/projectile_dropped_weapon.h"
using namespace ProjectilesId;

Grenade::Grenade(Stage& stage): Weapon(stage, 1, 10, GRENADE), turned_on(false) {}

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

void Grenade::finish_throw(int x_direction, bool, std::shared_ptr<Weapon> weapon) {
    Coordinate gun_position = get_gun_position(x_direction);
    // TODO: deberia poder tirar la granada para arriba
    stage.add_projectile(std::move(std::make_unique<GrenadeProjectile>(
            std::move(weapon), gun_position, 3, x_direction, 40, counter, stage, GRENADE)));
}
